/* ============================================================
 *  maze.c  迷宫逃脱（控制台版 · 单键操作）
 *  ------------------------------------------------------------
 *  @  人（你）        G 鬼             E 出口
 *  #  墙              ~ 河             B 箱子
 *  H  心（+2 HP）     F 定（冻结鬼）    . 路线提示
 *
 *  机制：
 *    · 鬼平时巡逻，靠近后追击；碰到你会扣 1 HP
 *    · 把 B 推到 ~ 上，河变成桥（可以走过去）
 *    · 吃到 H 回血，吃到 F 冻结鬼 6 回合
 *
 *  数据结构：图（邻接表）+ 栈（DFS 回溯栈）+ 队列（BFS）
 *  算法：    DFS 回溯生成迷宫 / DFS 回溯枚举路线 / BFS 求距离
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#endif

/* ---------- 配置 ---------- */
#define MAXN        20
#define MAXV        (MAXN * MAXN)
#define MAX_MON     6
#define MAX_ROUTES  50
#define CHASE_R     4          /* 距玩家 <= CHASE_R 时转为追击 */

#define CELL_FLOOR  0
#define CELL_WATER  1

#define ITEM_NONE   0
#define ITEM_HEART  1
#define ITEM_FREEZE 2

#define MAX_HP       6
#define HEART_HEAL   2
#define FREEZE_TURNS 6
#define MON_DAMAGE   1

/* ---------- 类型 ---------- */
typedef struct Edge  { int to; struct Edge *next; } Edge;
typedef struct       { int data[MAXV]; int top; } Stack;
typedef struct       { int len; int *cells; } Route;
typedef struct       { int pos, prev; } Monster;

/* ---------- 全局状态 ---------- */
static int   N;
static Edge *adj[MAXV];
static int   cell[MAXV];       /* CELL_FLOOR / CELL_WATER */
static int   box_at[MAXV];
static int   item_at[MAXV];    /* ITEM_* */
static int   hp;
static int   freeze_turns;

/* ============================================================
 *  基础工具
 * ============================================================ */
static void *xmalloc(size_t n) {
    void *p = malloc(n);
    if (!p) { fputs("out of memory\n", stderr); exit(1); }
    return p;
}

static void clear_screen(void) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD size, written;
    COORD home = { 0, 0 };
    if (h != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(h, &info)) {
        size = (DWORD)info.dwSize.X * (DWORD)info.dwSize.Y;
        FillConsoleOutputCharacterA(h, ' ', size, home, &written);
        FillConsoleOutputAttribute(h, info.wAttributes, size, home, &written);
        SetConsoleCursorPosition(h, home);
        return;
    }
#endif
    fputs("\033[2J\033[H", stdout);
}

static int read_key(void) {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        switch (_getch()) {
            case 72: return 'w';
            case 80: return 's';
            case 75: return 'a';
            case 77: return 'd';
            default: return 0;
        }
    }
    if (ch == EOF) return -1;
    return tolower(ch);
}

/* ---------- 栈 ---------- */
static void st_init(Stack *s) { s->top = 0; }
static void st_push(Stack *s, int v) {
    if (s->top >= MAXV) { fputs("stack overflow\n", stderr); exit(1); }
    s->data[s->top++] = v;
}
static int  st_pop(Stack *s)  { return s->data[--s->top]; }

/* ---------- 图 ---------- */
static void push_edge(int from, int to) {
    Edge *e = xmalloc(sizeof *e);
    e->to = to; e->next = adj[from]; adj[from] = e;
}
static void link_cells(int a, int b) { push_edge(a, b); push_edge(b, a); }

static int has_edge(int a, int b) {
    for (Edge *e = adj[a]; e; e = e->next) if (e->to == b) return 1;
    return 0;
}

static int grid_nbrs(int i, int out[4]) {
    int r = i / N, c = i % N, k = 0;
    if (r > 0)     out[k++] = i - N;
    if (r < N - 1) out[k++] = i + N;
    if (c > 0)     out[k++] = i - 1;
    if (c < N - 1) out[k++] = i + 1;
    return k;
}

static void free_graph(void) {
    for (int i = 0; i < N * N; i++) {
        Edge *e = adj[i];
        while (e) { Edge *n = e->next; free(e); e = n; }
        adj[i] = NULL;
    }
}

/* ============================================================
 *  ① DFS 回溯生成迷宫（生成树：起点到任意格有唯一通路）
 * ============================================================ */
static void gen_maze(int extra) {
    int vis[MAXV] = {0};
    Stack st; st_init(&st);
    vis[0] = 1; st_push(&st, 0);

    while (st.top > 0) {
        int cur = st.data[st.top - 1], nb[4], cand[4], nc = 0;
        int k = grid_nbrs(cur, nb);
        for (int i = 0; i < k; i++) if (!vis[nb[i]]) cand[nc++] = nb[i];

        if (nc) {
            int n = cand[rand() % nc];
            link_cells(cur, n);
            vis[n] = 1;
            st_push(&st, n);                 /* 前进 */
        } else {
            st_pop(&st);                     /* 回溯 */
        }
    }

    /* 再打通几面墙，产生环路 → 路线不唯一，排序才有意义 */
    for (int t = 0; extra > 0 && t < 1000; t++) {
        int a = rand() % (N * N), nb[4];
        int k = grid_nbrs(a, nb), b = nb[rand() % k];
        if (!has_edge(a, b)) { link_cells(a, b); extra--; }
    }
}

/* ============================================================
 *  ② 河流与箱子
 *     规则：每个水格旁边放一个箱子，玩家站在箱子另一侧把它推进河里
 * ============================================================ */
static int reachable(int s, int t) {
    int vis[MAXV] = {0}, q[MAXV], h = 0, tl = 0;
    vis[s] = 1; q[tl++] = s;
    while (h < tl) {
        int u = q[h++];
        if (u == t) return 1;
        for (Edge *e = adj[u]; e; e = e->next) {
            int v = e->to;
            if (vis[v] || cell[v] == CELL_WATER || box_at[v]) continue;
            vis[v] = 1; q[tl++] = v;
        }
    }
    return 0;
}

static void place_water_and_boxes(void) {
    int total = N * N;
    int want  = (N < 8) ? 1 : (N < 12) ? 2 : (N >= 16) ? 4 : 3;

    /* --- 放水格 --- */
    int water_cells[MAXV], nwater = 0;
    for (int tries = 0; nwater < want && tries < 500; tries++) {
        int c = rand() % total;
        if (c == 0 || c == total - 1 || cell[c] == CELL_WATER) continue;

        cell[c] = CELL_WATER;
        if (!reachable(0, total - 1)) { cell[c] = CELL_FLOOR; continue; }
        water_cells[nwater++] = c;
    }

    /* --- 给每个水格旁放一个箱子 --- */
    for (int i = 0; i < nwater; i++) {
        int c = water_cells[i], nb[4], k = grid_nbrs(c, nb);
        for (int j = 0; j < k; j++) {
            int b = nb[j];
            if (cell[b] == CELL_WATER || box_at[b] || !has_edge(b, c)) continue;
            if (!reachable(0, b)) continue;

            /* 玩家需要站在 b 的另一侧推 → 找一个可达的邻居 a != c */
            int nb2[4], k2 = grid_nbrs(b, nb2), ok = 0;
            for (int m = 0; m < k2; m++) {
                int a = nb2[m];
                if (a == c || cell[a] == CELL_WATER || box_at[a]) continue;
                if (!has_edge(a, b) || !reachable(0, a)) continue;
                ok = 1; break;
            }
            if (ok) { box_at[b] = 1; break; }
        }
    }
}

/* ============================================================
 *  ③ 道具（心 / 定）
 * ============================================================ */
static void place_items(void) {
    int total = N * N;
    int kinds[2] = { ITEM_HEART, ITEM_FREEZE };
    int counts[2] = { 2, 2 };

    for (int t = 0; t < 2; t++) {
        int placed = 0;
        for (int tries = 0; placed < counts[t] && tries < 300; tries++) {
            int c = rand() % total;
            if (c == 0 || c == total - 1) continue;
            if (cell[c] != CELL_FLOOR || box_at[c] || item_at[c] != ITEM_NONE) continue;
            item_at[c] = kinds[t];
            placed++;
        }
    }
}

/* ============================================================
 *  ④ BFS 求通路距离（鬼追击用；跳过水与箱子）
 * ============================================================ */
static void bfs(int s, int dist[]) {
    int q[MAXV], h = 0, t = 0;
    for (int i = 0; i < N * N; i++) dist[i] = -1;
    dist[s] = 0; q[t++] = s;
    while (h < t) {
        int u = q[h++];
        for (Edge *e = adj[u]; e; e = e->next) {
            int v = e->to;
            if (dist[v] >= 0) continue;
            if (cell[v] == CELL_WATER || box_at[v]) continue;
            dist[v] = dist[u] + 1;
            q[t++] = v;
        }
    }
}

/* ============================================================
 *  ⑤ DFS 回溯枚举 s→t 的全部路线（跳过水与箱子）
 * ============================================================ */
static Route routes[MAX_ROUTES];
static int   nroutes = 0;
static int   onpath[MAXV];
static Stack path;

static void dfs_routes(int u, int t) {
    if (nroutes >= MAX_ROUTES) return;
    if (u == t) {
        Route *r = &routes[nroutes++];
        r->len   = path.top;
        r->cells = xmalloc((size_t)path.top * sizeof(int));
        memcpy(r->cells, path.data, (size_t)path.top * sizeof(int));
        return;
    }
    for (Edge *e = adj[u]; e; e = e->next) {
        int v = e->to;
        if (cell[v] == CELL_WATER || box_at[v]) continue;
        if (onpath[v]) continue;
        onpath[v] = 1; st_push(&path, v);
        dfs_routes(v, t);
        st_pop(&path); onpath[v] = 0;
    }
}

static int cmp_route(const void *a, const void *b) {
    return ((const Route *)a)->len - ((const Route *)b)->len;
}

static void free_routes(void) {
    for (int i = 0; i < nroutes; i++) free(routes[i].cells);
    nroutes = 0;
}

static void find_routes(int s, int t) {
    free_routes();
    memset(onpath, 0, sizeof onpath);
    st_init(&path); st_push(&path, s); onpath[s] = 1;
    dfs_routes(s, t);
    qsort(routes, (size_t)nroutes, sizeof(Route), cmp_route);
}

/* ============================================================
 *  ⑥ 鬼：巡逻 / 追击 / 攻击
 *     返回 1 表示攻击了玩家（本身不移动）
 * ============================================================ */
static int monster_act(Monster *m, const int distp[], int player_pos) {
    int nb[4], n = 0;
    for (Edge *e = adj[m->pos]; e; e = e->next) {
        int v = e->to;
        if (cell[v] == CELL_WATER || box_at[v]) continue;
        nb[n++] = v;
    }
    if (n == 0) return 0;

    int next = -1;
    int d = distp[m->pos];

    if (d >= 0 && d <= CHASE_R) {
        /* 追击：优先选到玩家距离最小的格子；能直接踩到玩家就攻击 */
        int best = 999999;
        for (int i = 0; i < n; i++) {
            if (nb[i] == player_pos) { next = player_pos; break; }
            if (distp[nb[i]] >= 0 && distp[nb[i]] < best) {
                best = distp[nb[i]];
                next = nb[i];
            }
        }
    }
    if (next < 0) {
        /* 巡逻：不回头 */
        int cand[4], k = 0;
        for (int i = 0; i < n; i++) if (nb[i] != m->prev) cand[k++] = nb[i];
        next = (k > 0) ? cand[rand() % k] : m->prev;
    }

    if (next == player_pos) return 1;        /* 攻击，原地不动 */
    m->prev = m->pos;
    m->pos  = next;
    return 0;
}

/* ============================================================
 *  ⑦ 渲染
 * ============================================================ */
static void draw(const Monster *mon, int nm, int player, int show_route) {
    int H = 2 * N + 1;
    char g[2 * MAXN + 1][2 * MAXN + 2];
    int ex = N * N - 1;

    for (int r = 0; r < H; r++) { memset(g[r], '#', (size_t)H); g[r][H] = '\0'; }

    /* 格子中心先挖空 */
    for (int i = 0; i < N * N; i++)
        g[2 * (i / N) + 1][2 * (i % N) + 1] = ' ';

    /* 通路（水格两侧不打通，视觉上像被围住的河） */
    for (int i = 0; i < N * N; i++) {
        int r = i / N, c = i % N;
        for (Edge *e = adj[i]; e; e = e->next) {
            if (e->to <= i) continue;
            if (cell[i] == CELL_WATER || cell[e->to] == CELL_WATER) continue;
            g[r + e->to / N + 1][c + e->to % N + 1] = ' ';
        }
    }

    /* 水 */
    for (int i = 0; i < N * N; i++)
        if (cell[i] == CELL_WATER)
            g[2 * (i / N) + 1][2 * (i % N) + 1] = '~';

    /* 箱子 */
    for (int i = 0; i < N * N; i++)
        if (box_at[i])
            g[2 * (i / N) + 1][2 * (i % N) + 1] = 'B';

    /* 道具 */
    for (int i = 0; i < N * N; i++) {
        if (item_at[i] == ITEM_HEART)
            g[2 * (i / N) + 1][2 * (i % N) + 1] = 'H';
        else if (item_at[i] == ITEM_FREEZE)
            g[2 * (i / N) + 1][2 * (i % N) + 1] = 'F';
    }

    /* 出口 */
    g[2 * (ex / N) + 1][2 * (ex % N) + 1] = 'E';

    /* 路线提示（用 '.' 标出最短路线） */
    if (show_route && nroutes > 0) {
        const Route *R = &routes[0];
        for (int k = 0; k < R->len; k++) {
            int a = R->cells[k];
            if (a != player && a != ex && !box_at[a] && item_at[a] == ITEM_NONE)
                g[2 * (a / N) + 1][2 * (a % N) + 1] = '.';
            if (k + 1 < R->len) {
                int b = R->cells[k + 1];
                if (cell[a] != CELL_WATER && cell[b] != CELL_WATER)
                    g[a / N + b / N + 1][a % N + b % N + 1] = '.';
            }
        }
        g[2 * (ex / N) + 1][2 * (ex % N) + 1] = 'E';
    }

    /* 鬼、玩家放最上层 */
    for (int i = 0; i < nm; i++)
        g[2 * (mon[i].pos / N) + 1][2 * (mon[i].pos % N) + 1] = 'G';
    g[2 * (player / N) + 1][2 * (player % N) + 1] = '@';

    putchar('\n');
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            if (g[r][c] == '#') fputs("##", stdout);
            else { putchar(g[r][c]); putchar(' '); }
        }
        putchar('\n');
    }
}

/* ============================================================
 *  ⑧ 主流程
 * ============================================================ */
int main(int argc, char **argv) {
    /* --- 参数 --- */
    N = 15;
    int extra = 2;
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) extra = atoi(argv[2]);
    if (N < 6 || N > MAXN) { fprintf(stderr, "N must be 6..%d\n", MAXN); return 1; }
    if (extra < 0 || extra > 20) extra = 0;

    srand((unsigned)time(NULL));

    /* --- 生成地图 --- */
    gen_maze(extra);
    memset(cell, 0, sizeof cell);
    memset(box_at, 0, sizeof box_at);
    memset(item_at, 0, sizeof item_at);

    int exitc = N * N - 1;
    hp = MAX_HP;
    freeze_turns = 0;

    place_water_and_boxes();
    place_items();

    /* --- 玩家与鬼 --- */
    int player = 0;
    int nmax = (N < 10) ? 2 : (N < 14) ? 3 : 4;
    Monster mon[MAX_MON];
    int made = 0;
    for (int t = 0; made < nmax && t < 5000; t++) {
        int i = rand() % (N * N);
        if (i == 0 || i == exitc) continue;
        if (cell[i] == CELL_WATER || box_at[i] || item_at[i] != ITEM_NONE) continue;
        /* 别太靠近起点 */
        if (i / N + i % N < N - 1) continue;
        int dup = 0;
        for (int j = 0; j < made; j++) if (mon[j].pos == i) dup = 1;
        if (dup) continue;
        mon[made].pos = i; mon[made].prev = -1; made++;
    }
    if (made == 0) { mon[0].pos = exitc; mon[0].prev = -1; made = 1; }
    int nm = made;

    int distp[MAXV];
    bfs(player, distp);

    /* --- 游戏循环 --- */
    int steps = 0, over = 0;
    char msg[200];
    snprintf(msg, sizeof msg,
             "W/A/S/D 移动  R 查看路线  Q 退出");
    int show = 0;

    for (;;) {
        clear_screen();
        printf("迷宫逃脱    HP: %d/%d    步数: %d", hp, MAX_HP, steps);
        if (freeze_turns > 0) printf("    鬼冻结: %d 回合", freeze_turns);
        printf("\n");
        draw(mon, nm, player, show);
        show = 0;
        printf("%s\n", msg);

        if (over) break;

        printf("> ");
        fflush(stdout);

        int ch = read_key();
        if (ch < 0 || ch == 'q') break;

        if (ch == 'r') {
            find_routes(player, exitc);
            if (nroutes > 0)
                snprintf(msg, sizeof msg, "找到 %d 条路线，最短 %d 步（用 . 标出）",
                         nroutes, routes[0].len - 1);
            else
                snprintf(msg, sizeof msg, "当前位置到出口没有通路");
            show = 1;
            continue;
        }

        int dr = 0, dc = 0;
        switch (ch) {
            case 'w': dr = -1; break;
            case 's': dr =  1; break;
            case 'a': dc = -1; break;
            case 'd': dc =  1; break;
            default: continue;
        }

        int nr = player / N + dr, nc = player % N + dc;
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
            snprintf(msg, sizeof msg, "走到地图外了。");
            continue;
        }
        int nxt = nr * N + nc;
        if (!has_edge(player, nxt)) {
            snprintf(msg, sizeof msg, "前面是墙。");
            continue;
        }

        /* 撞到鬼 */
        int mon_idx = -1;
        for (int i = 0; i < nm; i++) if (mon[i].pos == nxt) mon_idx = i;
        if (mon_idx >= 0) {
            hp -= MON_DAMAGE;
            snprintf(msg, sizeof msg, "撞上鬼了！-%d HP", MON_DAMAGE);
            if (hp <= 0) { over = 1; snprintf(msg, sizeof msg, "你被鬼抓走了……GAME OVER"); }
            continue;
        }

        /* 推箱子 */
        if (box_at[nxt]) {
            int bx = nxt + (nxt - player);
            if (bx < 0 || bx >= N * N || !has_edge(nxt, bx)
                || box_at[bx] || bx == player) {
                snprintf(msg, sizeof msg, "箱子推不动。");
                continue;
            }
            if (cell[bx] == CELL_WATER) {
                cell[bx]  = CELL_FLOOR;          /* 河 → 桥 */
                box_at[nxt] = 0;
                snprintf(msg, sizeof msg, "箱子推进河里，变成了一座桥！");
            } else {
                box_at[bx]  = 1;
                box_at[nxt] = 0;
                snprintf(msg, sizeof msg, "推动了箱子。");
            }
        }

        /* 河挡路 */
        if (cell[nxt] == CELL_WATER) {
            snprintf(msg, sizeof msg, "河水挡路，需要把箱子推过来架桥。");
            continue;
        }

        /* 移动成功 */
        player = nxt;
        steps++;

        /* 到出口？ */
        if (player == exitc) {
            clear_screen();
            printf("迷宫逃脱    HP: %d/%d    步数: %d\n", hp, MAX_HP, steps);
            draw(mon, nm, player, 0);
            printf("\n★ 你成功逃出迷宫！用了 %d 步。\n", steps);
            printf("按任意键退出...");
            fflush(stdout);
            (void)_getch();
            break;
        }

        /* 拾取道具 */
        msg[0] = '\0';
        if (item_at[player] == ITEM_HEART) {
            hp += HEART_HEAL;
            if (hp > MAX_HP) hp = MAX_HP;
            item_at[player] = ITEM_NONE;
            snprintf(msg, sizeof msg, "拾取到心，回复 %d HP！", HEART_HEAL);
        } else if (item_at[player] == ITEM_FREEZE) {
            freeze_turns = FREEZE_TURNS;
            item_at[player] = ITEM_NONE;
            snprintf(msg, sizeof msg, "拾取到定，鬼被冻结 %d 回合！", FREEZE_TURNS);
        }

        /* 鬼的回合（冻结期间跳过） */
        int turn_damage = 0;
        if (freeze_turns > 0) {
            freeze_turns--;
        } else {
            bfs(player, distp);
            for (int i = 0; i < nm; i++) {
                if (monster_act(&mon[i], distp, player) && !turn_damage) {
                    hp -= MON_DAMAGE;
                    turn_damage = 1;
                }
            }
            if (turn_damage) {
                if (msg[0]) strcat(msg, "  ");
                strncat(msg, "被鬼攻击！", sizeof(msg) - strlen(msg) - 1);
            }
        }

        /* HP 检查 */
        if (hp <= 0) {
            clear_screen();
            printf("迷宫逃脱    HP: 0/%d    步数: %d\n", MAX_HP, steps);
            draw(mon, nm, player, 0);
            printf("\n✖ HP 归零，你被鬼抓住了……GAME OVER\n");
            printf("按任意键退出...");
            fflush(stdout);
            (void)_getch();
            break;
        }
    }

    free_routes();
    free_graph();
    return 0;
}
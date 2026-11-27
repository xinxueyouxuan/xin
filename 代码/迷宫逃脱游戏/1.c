/*
 * maze.c  迷宫逃脱（控制台版 · 单键操作）
 * 编译: gcc -std=c99 -Wall -Wextra -o maze maze.c
 * 运行: ./maze [边长N=10] [额外打通的墙数=0]
 *
 * 操作: W/A/S/D 或方向键移动（按一下就动，不用回车）
 *       R 枚举从当前位置到出口的所有路线   Q 退出
 *
 * 数据结构: 图(邻接表) + 栈(DFS 回溯栈) + 队列(BFS)
 * 算法:     DFS 回溯生成迷宫 / DFS 回溯枚举全部逃脱路线 / qsort 按长度排序
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>              /* _getch: 单键读取, 不等待回车 */
#ifdef _WIN32
#include <windows.h>            /* 清屏用控制台 API, 避免 system("cls") 闪烁 */
#endif

#define MAXN 15
#define MAXV (MAXN * MAXN)
#define MAX_MON 6
#define MAX_ROUTES 200
#define CHASE_R 4              /* 怪物与玩家的通路距离 <= 4 时转为追击 */

typedef struct Edge { int to; struct Edge *next; } Edge;   /* 邻接表结点 */
typedef struct { int data[MAXV]; int top; } Stack;         /* 顺序栈 */
typedef struct { int len; int *cells; } Route;             /* 一条候选路线 */
typedef struct { int pos, prev; } Monster;

static int N;                 /* 迷宫边长(格) */
static Edge *adj[MAXV];       /* 图: 每个格子一条边链表, 有边 = 之间没有墙 */

/* ---------- 工具 ---------- */
static void *xmalloc(size_t n) {
    void *p = malloc(n);
    if (!p) { fputs("out of memory\n", stderr); exit(1); }
    return p;
}

/* 清屏并把光标归位（用控制台 API，比 system("cls") 快且不闪烁） */
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
    fputs("\033[2J\033[H", stdout);   /* 兜底：ANSI 转义序列 */
}

/*
 * 读一个按键, 立刻返回, 不需要回车。
 * 方向键会先发一个前缀(0 或 224), 再跟一个键码, 这里翻译成 w/a/s/d。
 * 返回 0 表示按了不认识的键, 返回 -1 表示输入流结束。
 */
static int read_key(void) {
    int ch = _getch();
    if (ch == 0 || ch == 224) {          /* 功能键 / 方向键 */
        switch (_getch()) {
            case 72: return 'w';         /* ↑ */
            case 80: return 's';         /* ↓ */
            case 75: return 'a';         /* ← */
            case 77: return 'd';         /* → */
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
static int st_pop(Stack *s) { return s->data[--s->top]; }

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
static int grid_nbrs(int i, int out[4]) {      /* 网格上下左右相邻格 */
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

/* ① DFS 回溯生成迷宫: 生成树 => 起点到任意格有唯一通路 */
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
            link_cells(cur, n); vis[n] = 1; st_push(&st, n);   /* 前进 */
        } else {
            st_pop(&st);                                       /* 回溯 */
        }
    }
    /* 可选: 再打通几面墙, 让路线不唯一, 路线排序才有意义 */
    for (int t = 0; extra > 0 && t < 1000; t++) {
        int a = rand() % (N * N), nb[4];
        int k = grid_nbrs(a, nb), b = nb[rand() % k];
        if (!has_edge(a, b)) { link_cells(a, b); extra--; }
    }
}

/* BFS: 求每个格子到 s 的通路距离 (怪物追击用) */
static void bfs(int s, int dist[]) {
    int q[MAXV], h = 0, t = 0;
    for (int i = 0; i < N * N; i++) dist[i] = -1;
    dist[s] = 0; q[t++] = s;
    while (h < t) {
        int u = q[h++];
        for (Edge *e = adj[u]; e; e = e->next)
            if (dist[e->to] < 0) { dist[e->to] = dist[u] + 1; q[t++] = e->to; }
    }
}

/* ② DFS 回溯枚举 s -> t 的全部简单路径 */
static Route routes[MAX_ROUTES];
static int nroutes = 0;
static int onpath[MAXV];
static Stack path;

static void dfs_routes(int u, int t) {
    if (nroutes >= MAX_ROUTES) return;
    if (u == t) {
        Route *r = &routes[nroutes++];
        r->len = path.top;
        r->cells = xmalloc((size_t)path.top * sizeof(int));
        memcpy(r->cells, path.data, (size_t)path.top * sizeof(int));
        return;
    }
    for (Edge *e = adj[u]; e; e = e->next) {
        int v = e->to;
        if (!onpath[v]) {
            onpath[v] = 1; st_push(&path, v);       /* 进栈 */
            dfs_routes(v, t);
            st_pop(&path); onpath[v] = 0;           /* 回溯 */
        }
    }
}
static void free_routes(void) {
    for (int i = 0; i < nroutes; i++) free(routes[i].cells);
    nroutes = 0;
}
static int cmp_route(const void *a, const void *b) {
    return ((const Route *)a)->len - ((const Route *)b)->len;
}
/* ③ 枚举后按路径长度升序排序 */
static void find_routes(int s, int t) {
    free_routes();
    memset(onpath, 0, sizeof onpath);
    st_init(&path); st_push(&path, s); onpath[s] = 1;
    dfs_routes(s, t);
    qsort(routes, (size_t)nroutes, sizeof(Route), cmp_route);
}

/* ---------- 怪物: 平时巡逻(不回头), 靠近后沿最短通路追击 ---------- */
static void monster_move(Monster *m, const int distp[]) {
    int nb[4], n = 0, next;
    for (Edge *e = adj[m->pos]; e; e = e->next) nb[n++] = e->to;
    int d = distp[m->pos];
    if (d >= 0 && d <= CHASE_R) {
        int best = distp[nb[0]], cnt = 1; next = nb[0];
        for (int i = 1; i < n; i++) {
            if (distp[nb[i]] < best) { best = distp[nb[i]]; next = nb[i]; cnt = 1; }
            else if (distp[nb[i]] == best && rand() % (++cnt) == 0) next = nb[i];
        }
    } else {
        int cand[4], k = 0;
        for (int i = 0; i < n; i++) if (nb[i] != m->prev) cand[k++] = nb[i];
        next = k ? cand[rand() % k] : m->prev;
    }
    m->prev = m->pos; m->pos = next;
}

/* ---------- 显示 ---------- */
static void draw(const Monster *mon, int nm, int player, int show_route) {
    int H = 2 * N + 1;
    char g[2 * MAXN + 1][2 * MAXN + 2];
    for (int r = 0; r < H; r++) { memset(g[r], '#', (size_t)H); g[r][H] = '\0'; }
    for (int i = 0; i < N * N; i++) {
        int r = i / N, c = i % N;
        g[2 * r + 1][2 * c + 1] = ' ';
        for (Edge *e = adj[i]; e; e = e->next)
            if (e->to > i) g[r + e->to / N + 1][c + e->to % N + 1] = ' ';  /* 打通的墙 */
    }
    if (show_route && nroutes > 0) {                 /* 标出最短路线 */
        const Route *R = &routes[0];
        for (int k = 0; k < R->len; k++) {
            int a = R->cells[k];
            g[2 * (a / N) + 1][2 * (a % N) + 1] = '.';
            if (k + 1 < R->len) {
                int b = R->cells[k + 1];
                g[a / N + b / N + 1][a % N + b % N + 1] = '.';
            }
        }
    }
    int ex = N * N - 1;
    g[2 * (ex / N) + 1][2 * (ex % N) + 1] = 'E';
    for (int i = 0; i < nm; i++) g[2 * (mon[i].pos / N) + 1][2 * (mon[i].pos % N) + 1] = 'M';
    g[2 * (player / N) + 1][2 * (player % N) + 1] = 'P';
    putchar('\n');
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            char ch = g[r][c];
            if (ch == '#') fputs("##", stdout); else { putchar(ch); putchar(' '); }
        }
        putchar('\n');
    }
}

static int caught(const Monster *mon, int nm, int player) {
    for (int i = 0; i < nm; i++) if (mon[i].pos == player) return 1;
    return 0;
}

int main(int argc, char **argv) {
    int extra = 0;
    N = 10;
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) extra = atoi(argv[2]);
    if (N < 4 || N > MAXN) { fprintf(stderr, "N must be 4..%d\n", MAXN); return 1; }
    if (extra < 0 || extra > 20) extra = 0;

    srand((unsigned)time(NULL));
    gen_maze(extra);

    int exitc = N * N - 1, player = 0, nm = 3;
    Monster mon[MAX_MON];
    int made = 0;
    for (int t = 0; made < nm && t < 5000; t++) {          /* 怪物出生在远离起点处 */
        int i = rand() % (N * N), dup = 0;
        for (int j = 0; j < made; j++) if (mon[j].pos == i) dup = 1;
        if (!dup && i != exitc && i / N + i % N >= N - 1) { mon[made].pos = i; mon[made].prev = -1; made++; }
    }
    nm = made;

    int distp[MAXV], show = 0, steps = 0, over = 0;
    char msg[160];

    bfs(player, distp);
    snprintf(msg, sizeof msg, "W/A/S/D or arrow keys to move   R = routes   Q = quit");

    for (;;) {
        clear_screen();
        printf("Escape the maze!   P=you  M=monster  E=exit     steps: %d\n", steps);
        draw(mon, nm, player, show);
        show = 0;
        printf("%s\n", msg);

        if (over) break;                 /* 最后一屏留着, 让玩家看清结果 */

        printf("> ");
        fflush(stdout);

        int ch = read_key();             /* 按一下就走, 不用回车 */
        if (ch < 0 || ch == 'q') break;

        if (ch == 'r') {
            find_routes(player, exitc);
            if (nroutes > 0)
                snprintf(msg, sizeof msg, "%d route(s) to the exit, shortest %d step(s) - marked with '.'",
                         nroutes, routes[0].len - 1);
            else
                snprintf(msg, sizeof msg, "No path from here to the exit.");
            show = 1;
            continue;
        }

        int dr = 0, dc = 0;
        switch (ch) {
            case 'w': dr = -1; break;
            case 's': dr = 1;  break;
            case 'a': dc = -1; break;
            case 'd': dc = 1;  break;
            default: continue;           /* 不认识的键不消耗回合 */
        }

        int r = player / N + dr, c = player % N + dc;
        if (r < 0 || r >= N || c < 0 || c >= N || !has_edge(player, r * N + c)) {
            snprintf(msg, sizeof msg, "A wall blocks the way. (no turn wasted)");
            continue;
        }

        player = r * N + c;
        steps++;

        if (caught(mon, nm, player)) { snprintf(msg, sizeof msg, "A monster got you. GAME OVER."); over = 1; continue; }
        if (player == exitc)         { snprintf(msg, sizeof msg, "You escaped in %d steps! YOU WIN.", steps); over = 1; continue; }

        bfs(player, distp);
        for (int i = 0; i < nm; i++) monster_move(&mon[i], distp);
        if (caught(mon, nm, player)) { snprintf(msg, sizeof msg, "A monster got you. GAME OVER."); over = 1; continue; }

        snprintf(msg, sizeof msg, "W/A/S/D or arrow keys to move   R = routes   Q = quit");
    }

    if (over) {
        printf("\nPress any key to exit...");
        fflush(stdout);
        (void)_getch();
    }

    free_routes();
    free_graph();
    return 0;
}
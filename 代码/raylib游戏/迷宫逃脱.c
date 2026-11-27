/*
 * 迷宫逃脱（控制台版 · 单键操作）
 *
 * 符号: 人=你   鬼=鬼   墙=墙   河=河流(不能走)   箱=箱子   桥=箱子推下河后变的桥
 *       心=回血道具   定=定身道具(鬼停止行动)   门=出口
 *
 * 操作: W/A/S/D 或方向键移动（按一下就动，不用回车）
 *       R 枚举到出口的路线   Q 退出
 *
 * 关卡: 走到门即过关，关卡+1，下一关迷宫更大、鬼更多、道具更少；
 *       生命跨关保留，过关奖励回血。
 * 定身: 定身符生效期间鬼既不会移动，也伤不到你（撞上也不掉血）。
 *
 * 数据结构: 图(邻接表) + 栈(DFS 回溯栈) + 队列(BFS)
 * 算法:     DFS 回溯生成迷宫 / BFS 求最短距离 / DFS 回溯枚举路线 / qsort 排序
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>   /* _getch: 单键读取, 不等待回车 */
#ifdef _WIN32        /* Windows 下用控制台 API 清屏 + 输出转 UTF-8 */
#include <windows.h> /* 清屏 + 输出转 UTF-8 */
#endif

#define MAXN 16                /* 最大迷宫边长 */
#define MAXV (MAXN * MAXN)     /* 最大格子数 */
#define MAX_GHOST 6            /* 最大鬼的数量 */
#define GHOST_COUNT 2          /* 场上鬼的数量, 想更难就调大 */
#define MAX_BOX 4              /* 最大箱子数 */
#define MAX_ROUTES 200         /* 枚举路线的上限, 太多了就不枚举了 */
#define CHASE_R 5              /* 鬼与玩家的通路距离 <= 5 时转为追击 */

#define HP_MAX 10
#define DMG 2                  /* 每次被抓扣多少血 */
#define INV_TURNS 4            /* 被抓后的无敌回合数 */
#define FREEZE_TURNS 8         /* 定身道具让鬼停多少回合 */
#define HEAL 3                 /* 心回多少血 */
#define HEAL_ON_CLEAR 3        /* 过关奖励回血 */

/* 每一关的难度参数：关卡越高，迷宫越大、鬼越多、道具越少、通路越绕 */
/*定义一个关卡配置结构体*/
typedef struct {
    int n;         /* 迷宫边长 */
    int ghosts;    /* 鬼的数量 */
    int hearts;    /* 心的数量 */
    int freezes;   /* 定的数量 */
    int extra;     /* 额外打通的墙（越多岔路越多） */
} LevelCfg;

//定义一个函数来根据关卡数计算关卡配置
static void level_cfg(int level, int baseN, int baseExtra, LevelCfg *c) {
    //根据关卡数计算迷宫边长、鬼的数量、心的数量、定的数量和额外打通的墙数
    c->n = baseN + (level - 1);
    //限制迷宫边长不超过最大值
    if (c->n > MAXN) c->n = MAXN;

    c->ghosts = GHOST_COUNT + (level - 1) / 2;      /* 每两关多一只鬼 */
    if (c->ghosts > MAX_GHOST) c->ghosts = MAX_GHOST;

    c->hearts = 3 - (level - 1) / 3;                /* 每三关少一颗心 */
    if (c->hearts < 1) c->hearts = 1;

    c->freezes = 2 - (level - 1) / 4;               /* 每四关少一张定身符 */
    if (c->freezes < 1) c->freezes = 1;

    c->extra = baseExtra + (level - 1) * 2;
    if (c->extra > 20) c->extra = 20;
}

/*
 * 显示符号。每个符号都是"两列宽"（汉字/全角空格），
 * 所以网格排版天然对齐，不用再补空格。
 */
//定义一些静态常量字符串来表示迷宫中的各种元素
//static意为该变量的作用域仅限于当前文件，不能被其他文件访问
static const char *S_WALL   = "墙";
static const char *S_FLOOR  = "　";   /* 全角空格 U+3000 */
static const char *S_PLAYER = "人";
static const char *S_GHOST  = "鬼";
static const char *S_RIVER  = "河";
static const char *S_BOX    = "箱";
static const char *S_BRIDGE = "桥";
static const char *S_HEART  = "心";
static const char *S_FREEZE = "定";
static const char *S_EXIT   = "门";
static const char *S_ROUTE  = "．";   /* 全角句点，标路线用 */

//定义一个枚举类型来表示迷宫中的道具
//枚举类型是一种用户自定义的类型，它可以包含一组命名的整数常量
//就像是给道具起了名字，方便在代码中使用
enum { ITEM_NONE = 0, ITEM_HEART, ITEM_FREEZE };

//定义一个结构体来表示迷宫中的边
typedef struct Edge { int to; struct Edge *next; } Edge;
//定义一个结构体来表示栈
typedef struct { int data[MAXV]; int top; } Stack;
//定义一个结构体来表示迷宫中的路线
typedef struct { int len; int *cells; } Route;

static int N;                 /* 迷宫边长(格) */
static Edge *adj[MAXV];       /* 图: 每个格子一条边链表, 有边 = 之间没有墙 */
static bool river[MAXV];      /* 河水: 不能走 */
static bool bridge[MAXV];     /* 桥: 箱子沉下去后变成可走的格子 */
static int  boxPos[MAX_BOX];  /* 箱子的位置 */
static int  nbox = 0;
static int  item[MAXV];       /* 格子上的道具 */

/* ---------- 工具 ---------- */
//定义一个函数来分配内存，如果分配失败则打印错误信息并退出程序
static void *xmalloc(size_t n) {
    //定义一个空类型的指针p，并使用malloc函数分配n字节的内存
    void *p = malloc(n);
    //判断指针p是否为空，如果为空则说明内存分配失败，打印错误信息并退出程序
    //意思是如果分配内存失败，就输出"out of memory"到标准错误流，并退出程序，返回值为1
    if (!p) { fputs("out of memory\n", stderr); exit(1); }
    return p;
}

/* 清屏并把光标归位（用控制台 API，比 system("cls") 快且不闪烁） */
//函数clear_screen用于清空控制台屏幕并将光标移动到左上角。它根据操作系统的不同使用不同的方法来实现清屏功能。在Windows系统中，它使用控制台API函数来清屏，而在其他系统中，它使用ANSI转义序列来清屏。
static void clear_screen(void) {
//在Windows系统中，使用控制台API函数来清屏
//#ifdef _WIN32表示如果当前操作系统是Windows，则执行下面的代码块
#ifdef _WIN32
    //获取标准输出句柄
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //定义一个结构体info来存储控制台屏幕缓冲区的信息
    CONSOLE_SCREEN_BUFFER_INFO info;
    //定义两个DWORD类型的变量size和written，分别表示缓冲区的大小和写入的字符数
    DWORD size, written;
    //定义一个COORD类型的变量home，表示光标的位置，初始值为(0,0)
    COORD home = { 0, 0 };
    //判断句柄是否有效，并获取控制台屏幕缓冲区的信息
    if (h != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(h, &info)) {
        //计算缓冲区的大小，即宽度乘以高度
        size = (DWORD)info.dwSize.X * (DWORD)info.dwSize.Y;
        //用空格填充缓冲区
        FillConsoleOutputCharacterA(h, ' ', size, home, &written);
        //用当前的属性填充缓冲区
        FillConsoleOutputAttribute(h, info.wAttributes, size, home, &written);
        //将光标移动到左上角
        SetConsoleCursorPosition(h, home);
        return;
    }
//如果不是Windows系统，则使用ANSI转义序列来清屏
//#endif意为如果当前操作系统不是Windows，则执行下面的代码块
#endif
    //使用ANSI转义序列清屏并将光标移动到左上角
    fputs("\033[2J\033[H", stdout);   /* 兜底：ANSI 转义序列 */
}

/*
 * 读一个按键, 立刻返回, 不需要回车。
 * 方向键会先发一个前缀(0 或 224), 再跟一个键码, 这里翻译成 w/a/s/d。
 * 返回 0 表示按了不认识的键, 返回 -1 表示输入流结束。
 */
//定义一个函数来读取用户输入的按键，并返回对应的字符
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
    //如果按下的键是回车键，则返回'w'，表示向上移动
    if (ch == EOF) return -1;
    return tolower(ch);
}

/* ---------- 栈 ---------- */
// 定义一个函数来初始化栈，将栈顶指针设置为0
static void st_init(Stack *s) { s->top = 0; }

// 定义一个函数来将一个整数压入栈中，如果栈满则打印错误信息并退出程序
static void st_push(Stack *s, int v) {
    // 判断栈是否已满，如果已满则打印错误信息并退出程序
    if (s->top >= MAXV) { fputs("stack overflow\n", stderr); exit(1); }
    // 将整数v压入栈中，并将栈顶指针加1
    s->data[s->top++] = v;
}
// 定义一个函数来将栈顶的整数弹出栈中，并返回该整数
static int st_pop(Stack *s) { return s->data[--s->top]; }

/* ---------- 格子查询 ---------- */
//定义一个函数来检查指定的格子上是否有箱子，如果有则返回箱子的下标，否则返回-1
static int box_at(int i) {                 /* 该格子上有没有箱子, 返回下标或 -1 */
    // 遍历所有箱子的位置，如果找到与指定格子相同的位置，则返回该箱子的下标
    for (int k = 0; k < nbox; k++) if (boxPos[k] == i) return k;
    return -1;
}
//定义一个函数来检查指定的格子是否可以走，如果是河则返回0，否则返回1
static int cell_walkable(int i) { return !river[i]; }   /* 河不能走, 其余都能走 */

/* ---------- 图 ---------- */
// 定义一个函数来在图中添加一条从格子from到格子to的边
static void push_edge(int from, int to) {
    // 分配一个新的边结构体，并将其插入到from格子的邻接表中
    Edge *e = xmalloc(sizeof *e);
    // 将新边的目标格子设置为to，并将其插入到from格子的邻接表头部
    e->to = to; e->next = adj[from]; adj[from] = e;
}
// 定义一个函数来在图中添加一条从格子a到格子b的双向边
static void link_cells(int a, int b) { push_edge(a, b); push_edge(b, a); }
// 定义一个函数来检查图中是否存在从格子a到格子b的边，如果存在则返回1，否则返回0
static int has_edge(int a, int b) {
    // 遍历a格子的邻接表，如果找到目标格子为b的边，则返回1
    for (Edge *e = adj[a]; e; e = e->next) if (e->to == b) return 1;
    return 0;
}
// 定义一个函数来获取指定格子i的上下左右相邻格子，并将它们存储在out数组中，返回相邻格子的数量
static int grid_nbrs(int i, int out[4]) {      /* 网格上下左右相邻格 */
    // 计算格子i的行号r和列号c，以及相邻格子的数量k
    int r = i / N, c = i % N, k = 0;

    // 如果格子i的上方有相邻格子，则将其索引存储在out数组中，并将k加1
    if (r > 0)     out[k++] = i - N;
    if (r < N - 1) out[k++] = i + N;
    if (c > 0)     out[k++] = i - 1;
    if (c < N - 1) out[k++] = i + 1;
    return k;
}
// 定义一个函数来释放图中所有边的内存，并将邻接表指针设置为NULL
static void free_graph(void) {
    // 遍历所有格子，释放每个格子的邻接表中的所有边，并将邻接表指针设置为NULL
    for (int i = 0; i < N * N; i++) {
        Edge *e = adj[i];
        // 遍历邻接表中的所有边，释放每条边的内存
        while (e) { Edge *n = e->next; free(e); e = n; }
        adj[i] = NULL;
    }
}

/* ① DFS 回溯生成迷宫: 生成树 => 起点到任意格有唯一通路 */
// extra: 额外打通的墙数, 让路线不唯一, 路线排序才有意义
// 生成树: 每个格子有且只有一条通路到起点, 迷宫的本质就是一棵树
// DFS 回溯: 先随机选一个邻居前进, 没路了就回溯
// 生成树的边就是迷宫中没有墙的地方
// 生成树的边数 = 格子数 - 1, 所以迷宫中有墙的地方 = 格子数 - 1
// 额外打通的墙数 = extra, 所以迷宫中有墙的地方 = 格子数 - 1 - extra
// 迷宫中有墙的地方越少, 路线就越多, 难度就越低
//定义一个函数来生成迷宫，使用深度优先搜索算法，并可以选择额外打通的墙数
static void gen_maze(int extra) {
    int vis[MAXV] = {0};
    Stack st; st_init(&st);
    //从起点格子0开始，将其标记为已访问，并将其压入栈中
    vis[0] = 1; st_push(&st, 0);
    //使用深度优先搜索算法生成迷宫，直到栈为空为止
    while (st.top > 0) {
        int cur = st.data[st.top - 1], nb[4], cand[4], nc = 0;
        int k = grid_nbrs(cur, nb);
        // 遍历当前格子的所有相邻格子，如果相邻格子未被访问，则将其加入候选列表中
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

/* BFS: 求每个格子到 s 的通路距离 (鬼追击用), 绕开河水和箱子 */
// dist[i] = -1 表示走不到
//定义一个函数来使用广度优先搜索算法计算从起点格子s到每个格子的最短距离，并将结果存储在dist数组中
static void bfs(int s, int dist[]) {
    int q[MAXV], h = 0, t = 0;
    // 初始化dist数组，将所有格子的距离设置为-1，表示不可达
    for (int i = 0; i < N * N; i++) dist[i] = -1;
    if (!cell_walkable(s)) return;
    dist[s] = 0; q[t++] = s;
    // 使用广度优先搜索算法遍历图中的所有格子，直到队列为空为止
    while (h < t) {
        int u = q[h++];
        for (Edge *e = adj[u]; e; e = e->next) {
            int v = e->to;
            if (!cell_walkable(v) || box_at(v) >= 0) continue;
            if (dist[v] < 0) { dist[v] = dist[u] + 1; q[t++] = v; }
        }
    }
}

/* BFS + 前驱: 用来找出起点到出口的那条路, 好把河放在必经之路上 */
//定义一个函数来使用广度优先搜索算法计算从起点格子s到终点格子t的路径，并将路径的前驱存储在prev数组中
static int bfs_path(int s, int t, int prev[]) {
    int q[MAXV], h = 0, tail = 0;
    // 初始化prev数组，将所有格子的前驱设置为-1，表示未访问
    for (int i = 0; i < N * N; i++) prev[i] = -1;
    prev[s] = s; q[tail++] = s;
    // 使用广度优先搜索算法遍历图中的所有格子，直到队列为空为止
    while (h < tail) {
        int u = q[h++];
        if (u == t) return 1;
        // 遍历当前格子的所有相邻格子，如果相邻格子未被访问，则将其加入队列中，并将其前驱设置为当前格子
        for (Edge *e = adj[u]; e; e = e->next)
            if (prev[e->to] < 0) { prev[e->to] = u; q[tail++] = e->to; }
    }
    return prev[t] >= 0;
}

/*
 * 在起点到出口的必经之路上挑一段"直道"，正中间放河、靠起点那侧放箱子。
 *
 * 关键约束：箱子背后那一格必须是**路**，否则玩家站不上去（被箱子堵死）。
 * 所以要找连续的四个格子共线： 推位 → 箱子 → 河 → 对岸，
 * 这样四格都在路上，玩家从起点走过来自然就站在推位上了。
 */
//定义一个函数来在起点到出口的路径上选择一个合适的位置放置河流和箱子，并返回是否成功
static int pick_river_spot(const int *path, int plen, int *center_out, int *box_out, int *push_out) {
    int mid = plen / 2;
    // 遍历路径的每个格子，尝试在其附近放置河流和箱子
    for (int d = 0; d < plen; d++) {
        //尝试在路径的中间位置向前或向后偏移d个格子，检查是否可以放置河流和箱子
        for (int s = -1; s <= 1; s += 2) {
            int i = mid + s * d;
            if (i < 2 || i > plen - 3) continue;     /* 前后都要留出格子 */

            int c     = path[i];        /* 河 */
            int box   = path[i + 1];    /* 箱子, 在河靠起点这一侧 */
            int push  = path[i + 2];    /* 箱子背后, 玩家要站的地方 */
            int opp   = path[i - 1];    /* 河对岸 */

            // 检查这四个格子是否在同一行或同一列，如果不是则跳过
            int same_row = (opp / N == c / N) && (c / N == box / N) && (box / N == push / N);
            int same_col = (opp % N == c % N) && (c % N == box % N) && (box % N == push % N);
            if (!same_row && !same_col) continue;    /* 不是直道, 跳过 */

            if (box == 0) continue;                  /* 箱子不能压在起点上 */

            // 检查这四个格子是否都是可走的，如果有任何一个格子不可走则跳过
            *center_out = c;
            *box_out    = box;
            *push_out   = push;
            return 1;
        }
    }
    return 0;
}

//定义一个函数来在迷宫中建立河流和箱子
//static表示该函数的作用域仅限于当前文件，不能被其他文件访问
//定义了一个函数来在迷宫中建立河流和箱子，返回是否成功
static int build_river_and_box(void) {
    int prev[MAXV];
    int ex = N * N - 1;
    if (!bfs_path(0, ex, prev)) return 0;

    int path[MAXV], plen = 0;
    //从出口格子ex开始，沿着前驱数组prev回溯到起点格子0，将路径上的格子存储在path数组中，并计算路径长度plen
    for (int v = ex; v != -1 && plen < MAXV; v = prev[v]) {
        path[plen++] = v;
        if (v == 0) break;
    }
    if (plen < 6) return 0;                    /* 路太短, 不折腾 */

    int center, box, push;
    if (!pick_river_spot(path, plen, &center, &box, &push)) return 0;

    boxPos[nbox++] = box;
    river[center] = true;
    return 1;
}

/* 在随机空地上放道具, 返回放下的数量。只放在玩家走得到的地方, 免得放了拿不到 */
//定义一个函数来在迷宫中随机放置道具，返回实际放置的道具数量
static int place_items(int count_heart, int count_freeze, int player, const int distp[]) {
    int total = count_heart + count_freeze;
    int placed = 0;
    //尝试最多4000次随机选择一个格子，如果该格子满足条件则放置道具
    for (int t = 0; t < 4000 && placed < total; t++) {
        int i = rand() % (N * N);
        if (i == player || i == N * N - 1) continue;
        if (!cell_walkable(i) || box_at(i) >= 0) continue;
        if (item[i] != ITEM_NONE) continue;
        if (distp[i] < 4) continue;                       /* 走不到(-1)或离起点太近 */
        //根据已放置的道具数量决定放置心还是定身符
        item[i] = (placed < count_heart) ? ITEM_HEART : ITEM_FREEZE;
        placed++;
    }
    //返回实际放置的道具数量
    return placed;
}

/* ② DFS 回溯枚举 s -> t 的全部简单路径（只能走能走的格子） */
//定义一些静态变量来存储枚举路径的结果和状态
static Route routes[MAX_ROUTES];
static int nroutes = 0;
static int onpath[MAXV];
static Stack path;
static long dfs_calls = 0;

//定义一个递归函数来使用深度优先搜索算法枚举从格子u到格子t的所有简单路径，并将结果存储在routes数组中
static void dfs_routes(int u, int t) {
    if (nroutes >= MAX_ROUTES) return;
    if (++dfs_calls > 400000) return;        /* 防止地图开太多口时枚举爆炸 */
    if (u == t) {
        Route *r = &routes[nroutes++];
        r->len = path.top;
        r->cells = xmalloc((size_t)path.top * sizeof(int));
        memcpy(r->cells, path.data, (size_t)path.top * sizeof(int));
        return;
    }
    //遍历当前格子u的所有相邻格子，如果相邻格子可走且未被访问，则将其压入栈中并递归调用dfs_routes函数
    for (Edge *e = adj[u]; e; e = e->next) {
        int v = e->to;
        if (!cell_walkable(v) || box_at(v) >= 0) continue;
        if (!onpath[v]) {
            onpath[v] = 1; st_push(&path, v);       /* 进栈 */
            dfs_routes(v, t);
            st_pop(&path); onpath[v] = 0;           /* 回溯 */
        }
    }
}
//定义一个函数来释放枚举路径的内存，并将nroutes重置为0
static void free_routes(void) {
    //遍历所有枚举路径，释放每条路径的格子数组的内存
    for (int i = 0; i < nroutes; i++) free(routes[i].cells);
    nroutes = 0;
}
//定义一个比较函数来按路径长度升序排序枚举路径，用于qsort函数
static int cmp_route(const void *a, const void *b) {
    //将两个指针a和b分别转换为Route类型的指针，并比较它们的路径长度len
    return ((const Route *)a)->len - ((const Route *)b)->len;
}
/* ③ 枚举后按路径长度升序排序 */
//定义一个函数来枚举从格子s到格子t的所有简单路径，并按路径长度升序排序
static void find_routes(int s, int t) {
    //释放之前枚举的路径内存，并将onpath数组清零，dfs_calls重置为0
    free_routes();
    //将onpath数组清零，表示所有格子都未被访问
    memset(onpath, 0, sizeof onpath);
    dfs_calls = 0;
    st_init(&path); st_push(&path, s); onpath[s] = 1;
    dfs_routes(s, t);
    qsort(routes, (size_t)nroutes, sizeof(Route), cmp_route);
}

/* ---------- 鬼: 平时巡逻(不回头), 靠近后沿最短通路追击 ---------- */
// 定义一个函数来移动鬼的位置，根据玩家的位置和距离决定鬼的行为
static void ghost_move(int *gp, int *gpv, int ng, const int distp[]) {
    //遍历每个鬼，根据其与玩家的距离决定是否追击或随机巡逻
    for (int i = 0; i < ng; i++) {
        int nb[4], n = 0;
        // 遍历鬼当前位置的所有相邻格子，如果相邻格子可走且没有箱子，则将其加入候选列表中
        for (Edge *e = adj[gp[i]]; e; e = e->next)
            if (cell_walkable(e->to) && box_at(e->to) < 0) nb[n++] = e->to;
        if (n == 0) continue;

        int d = distp[gp[i]], next;
        //如果鬼与玩家的距离在追击范围内，则选择最短路径的相邻格子作为下一步位置，否则随机选择一个相邻格子作为下一步位置
        if (d >= 0 && d <= CHASE_R) {
            int best = -1, cnt = 0;
            next = nb[0];
            //遍历鬼当前位置的所有相邻格子，找到距离玩家最近的格子作为下一步位置，如果有多个格子距离相同，则随机选择一个
            for (int j = 0; j < n; j++) {
                int dd = distp[nb[j]];
                if (dd < 0) continue;
                if (best < 0 || dd < best) { best = dd; next = nb[j]; cnt = 1; }
                else if (dd == best && rand() % (++cnt) == 0) next = nb[j];
            }
        } else {
            int cand[4], k = 0;
            // 遍历鬼当前位置的所有相邻格子，如果相邻格子不是鬼上一步的位置，则将其加入候选列表中
            for (int j = 0; j < n; j++) if (nb[j] != gpv[i]) cand[k++] = nb[j];
            next = k ? cand[rand() % k] : gpv[i];
        }
        //更新鬼的上一步位置和当前位置
        gpv[i] = gp[i];
        gp[i] = next;
    }
}

//定义一个函数来检查玩家是否被鬼抓住，如果被抓住则返回1，否则返回0
static int ghost_catches(const int *gp, int ng, int player) {
    //遍历每个鬼的位置，如果有任何一个鬼的位置与玩家的位置相同，则返回1，表示玩家被抓住
    for (int i = 0; i < ng; i++) if (gp[i] == player) return 1;
    return 0;
}

/* ---------- 显示 ---------- */
//定义一个函数来绘制游戏的HUD（头上显示信息），包括关卡数、生命值、步数、无敌时间和定身时间
static void draw_hud(int level, int hp, int inv, int frozen, int steps) {
    char bar[11];
    int filled = (hp > 0 ? hp : 0) * 10 / HP_MAX;
    //根据当前生命值计算生命条的填充长度，并将生命条的字符数组bar填充为'#'表示已填充部分，'-'表示未填充部分
    for (int i = 0; i < 10; i++) bar[i] = (i < filled) ? '#' : '-';
    bar[10] = '\0';

    printf("迷宫逃脱   第 %d 关   生命[%s] %2d/%d   步数 %3d",
           level, bar, hp > 0 ? hp : 0, HP_MAX, steps);
    if (inv > 0)    printf("   无敌 %d", inv);
    if (frozen > 0) printf("   定身 %d（鬼伤不到你）", frozen);
    putchar('\n');
}

//定义一个函数来绘制迷宫的当前状态，包括墙、地面、玩家、鬼、河流、箱子、桥、道具、出口和路线提示
static void draw(int player, const int *gp, int ng, int show_route) {
    int H = 2 * N + 1;
    static const char *g[2 * MAXN + 1][2 * MAXN + 1];

    //初始化迷宫的每个格子为墙
    for (int r = 0; r < H; r++)
        for (int c = 0; c < H; c++) g[r][c] = S_WALL;

    /* 先铺地面：每个格子本身 + 它右边/下边被打通的墙 */
    for (int i = 0; i < N * N; i++) {
        int r = i / N, c = i % N;
        g[2 * r + 1][2 * c + 1] = S_FLOOR;
        // 遍历当前格子i的所有相邻格子，如果相邻格子的索引大于当前格子的索引，则将它们之间的墙打通，表示可以走
        for (Edge *e = adj[i]; e; e = e->next)
            if (e->to > i) g[r + e->to / N + 1][c + e->to % N + 1] = S_FLOOR;
    }

    /* 河和桥 */
    //遍历迷宫的每个格子，如果该格子是河流，则将其对应的显示字符设置为S_RIVER，如果该格子是桥，则将其对应的显示字符设置为S_BRIDGE
    for (int i = 0; i < N * N; i++) {
        if (river[i])        g[2 * (i / N) + 1][2 * (i % N) + 1] = S_RIVER;
        else if (bridge[i])  g[2 * (i / N) + 1][2 * (i % N) + 1] = S_BRIDGE;
    }

    /* 箱子 */
    //遍历所有箱子的位置，将每个箱子所在的格子对应的显示字符设置为S_BOX
    for (int k = 0; k < nbox; k++) {
        int i = boxPos[k];
        g[2 * (i / N) + 1][2 * (i % N) + 1] = S_BOX;
    }

    /* 道具 */
    //遍历迷宫的每个格子，如果该格子上有道具，则根据道具类型将其对应的显示字符设置为S_HEART或S_FREEZE
    for (int i = 0; i < N * N; i++) {
        if (item[i] == ITEM_HEART)       g[2 * (i / N) + 1][2 * (i % N) + 1] = S_HEART;
        else if (item[i] == ITEM_FREEZE) g[2 * (i / N) + 1][2 * (i % N) + 1] = S_FREEZE;
    }

    /* 路线提示：把最短那条路的格子标出来 */
    //如果show_route为真且nroutes大于0，则将最短路径的格子标记为S_ROUTE，并将相邻格子之间的墙也标记为S_ROUTE
    if (show_route && nroutes > 0) {
        const Route *R = &routes[0];
        //遍历最短路径的每个格子，将其对应的显示字符设置为S_ROUTE，并将相邻格子之间的墙也标记为S_ROUTE
        for (int k = 0; k < R->len; k++) {
            int a = R->cells[k];
            g[2 * (a / N) + 1][2 * (a % N) + 1] = S_ROUTE;
            if (k + 1 < R->len) {
                int b = R->cells[k + 1];
                g[a / N + b / N + 1][a % N + b % N + 1] = S_ROUTE;
            }
        }
    }

    /* 出口 */
    //将出口格子对应的显示字符设置为S_EXIT
    int ex = N * N - 1;
    g[2 * (ex / N) + 1][2 * (ex % N) + 1] = S_EXIT;

    /* 鬼，最后是玩家 */
    //遍历所有鬼的位置，将每个鬼所在的格子对应的显示字符设置为S_GHOST，并将玩家所在的格子对应的显示字符设置为S_PLAYER
    for (int i = 0; i < ng; i++)
        g[2 * (gp[i] / N) + 1][2 * (gp[i] % N) + 1] = S_GHOST;
    g[2 * (player / N) + 1][2 * (player % N) + 1] = S_PLAYER;

    //将迷宫的每一行输出到标准输出中，每行之间用换行符分隔
    putchar('\n');
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) fputs(g[r][c], stdout);
        putchar('\n');
    }
}

/* ---------- 主函数 ---------- */
int main(int argc, char **argv) {
//ifdef _WIN32是一个条件编译指令，用于在Windows平台上设置控制台的输出编码为UTF-8，以便正确显示中文字符
#ifdef _WIN32
//SetConsoleOutputCP(CP_UTF8)是Windows API函数，用于设置控制台的输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);        /* 让控制台按 UTF-8 解释中文 */

//endif是条件编译指令的结束标志，表示在Windows平台上设置控制台输出编码的代码块结束
#endif
    //定义一些变量来存储游戏的基本参数，包括迷宫的边长baseN和额外打通的墙数baseExtra
    int baseExtra = 0;
    int baseN = 12;                     /* 第一关 12x12 */
    //根据命令行参数设置迷宫的边长和额外打通的墙数，如果参数不合法则打印错误信息并退出程序
    if (argc > 1) baseN = atoi(argv[1]);
    if (argc > 2) baseExtra = atoi(argv[2]);
    if (baseN < 6 || baseN > MAXN) { fprintf(stderr, "N must be 6..%d\n", MAXN); return 1; }
    if (baseExtra < 0 || baseExtra > 20) baseExtra = 0;

    //使用当前时间作为随机数生成器的种子，以便每次运行程序时生成不同的迷宫
    srand((unsigned)time(NULL));

    //定义一些变量来存储游戏的状态，包括当前关卡数level、玩家的生命值hp、累计步数total_steps和退出标志quit
    int level = 1;                      /* 第几关 */
    int hp = HP_MAX;                    /* 生命跨关保留 */
    int total_steps = 0;                /* 累计步数 */
    int quit = 0;

    /* ============ 关卡循环：过关后难度加大，接着玩下一关 ============ */
    //循环直到玩家选择退出游戏，每次循环表示一关游戏的开始
    while (!quit) {
        //根据当前关卡数level和基本参数baseN、baseExtra生成当前关卡的配置cfg，包括迷宫的边长、额外打通的墙数、心和定身符的数量以及鬼的数量
        LevelCfg cfg;
        //调用level_cfg函数生成当前关卡的配置
        level_cfg(level, baseN, baseExtra, &cfg);

        /* 清掉上一关的图和路线（此时 N 还是上一关的边长，不能先改） */
        free_graph();
        free_routes();

        //根据当前关卡的配置cfg设置迷宫的边长N
        N = cfg.n;
        nbox = 0;
        //使用memset函数将河流、桥和道具的状态数组river、bridge和item清零，表示没有河流、桥和道具
        memset(river, 0, sizeof river);
        memset(bridge, 0, sizeof bridge);
        memset(item, 0, sizeof item);

        //调用gen_maze函数生成迷宫，并根据当前关卡的配置cfg设置额外打通的墙数
        gen_maze(cfg.extra);
        build_river_and_box();

        //定义一些变量来存储游戏的状态，包括出口格子exitc、玩家位置player、无敌时间inv、定身时间frozen、步数steps、玩家到每个格子的距离distp、是否显示路线show、关卡是否结束level_over和是否获胜won
        int exitc = N * N - 1, player = 0;
        int inv = 0, frozen = 0, steps = 0;
        int distp[MAXV], show = 0;
        int level_over = 0, won = 0;

        //调用bfs函数计算玩家到每个格子的最短距离，并将结果存储在distp数组中
        bfs(player, distp);
        place_items(cfg.hearts, cfg.freezes, player, distp);

        /*
         * 鬼出生在离玩家较远的地方。
         * 河会把可达区域切小, 未必总有足够远的格子, 所以分四档放宽:
         * 先找远处可达格, 再逐步放宽, 最后允许放到河对岸(过桥后才碰得到),
         * 免得鬼贴脸出生或者一只都放不出来。
         */
        int gp[MAX_GHOST], gpv[MAX_GHOST], ng = 0;
        //循环四次，每次尝试放置鬼的位置，如果当前放置的鬼数量小于配置中的鬼数量，则继续尝试放置
        for (int pass = 0; pass < 4 && ng < cfg.ghosts; pass++) {
            int minDist = (pass == 0) ? N : (pass == 1 ? 6 : (pass == 2 ? 3 : 0));
            //尝试最多3000次随机选择一个格子，如果该格子满足条件则放置鬼
            for (int t = 0; t < 3000 && ng < cfg.ghosts; t++) {
                int i = rand() % (N * N);
                if (!cell_walkable(i) || box_at(i) >= 0) continue;
                if (i == player || i == exitc) continue;
                if (distp[i] >= 0) {
                    if (distp[i] < minDist) continue;
                } else if (pass < 3) {
                    continue;                  /* 前几轮只放在玩家这一侧 */
                }
                int dup = 0;
                //检查当前格子是否已经被放置过鬼，如果是则跳过
                for (int j = 0; j < ng; j++) if (gp[j] == i) dup = 1;
                if (dup) continue;
                gp[ng] = i; gpv[ng] = -1; ng++;
            }
        }

        //定义一个字符数组msg来存储游戏的提示信息，并使用snprintf函数将提示信息格式化为字符串
        char msg[200];
        snprintf(msg, sizeof msg, "W/A/S/D 或方向键移动   R 看路线   Q 退出");

        /* ---- 本关的回合循环 ---- */
        //循环直到当前关卡结束，每次循环表示玩家的一回合操作
        for (;;) {
            //清屏并绘制游戏的HUD和迷宫的当前状态，然后根据玩家的输入进行相应的操作
            clear_screen();
            //绘制游戏的HUD，包括关卡数、生命值、步数、无敌时间和定身时间
            draw_hud(level, hp, inv, frozen, steps);
            //绘制迷宫的当前状态，包括墙、地面、玩家、鬼、河流、箱子、桥、道具、出口和路线提示
            draw(player, gp, ng, show);
            //定义一个变量show并将其设置为0，表示不显示路线提示
            show = 0;
            printf("%s\n", msg);

            if (level_over) break;           /* 最后一屏留着, 让玩家看清结果 */

            int used_freeze = 0;             /* 本回合是否刚用了定身符 */

            printf("> ");
            fflush(stdout);

            int ch = read_key();             /* 按一下就走, 不用回车 */
            if (ch < 0 || ch == 'q') { quit = 1; break; }

            if (ch == 'r') {
                find_routes(player, exitc);
                if (nroutes > 0)
                    snprintf(msg, sizeof msg, "到出口共 %d 条路线，最短 %d 步（图上用 ． 标出）",
                             nroutes, routes[0].len - 1);
                else
                    snprintf(msg, sizeof msg, "现在走不到出口——河挡着，得先想办法搭桥");
                show = 1;
                continue;
            }

            int dr = 0, dc = 0;
            //判断人往哪里走
            switch (ch) {
                case 'w': dr = -1; break;
                case 's': dr = 1;  break;
                case 'a': dc = -1; break;
                case 'd': dc = 1;  break;
                default: continue;           /* 不认识的键不消耗回合 */
            }

            int r = player / N + dr, c = player % N + dc;
            if (r < 0 || r >= N || c < 0 || c >= N) { snprintf(msg, sizeof msg, "到头了，换个方向"); continue; }
            int nb = r * N + c;

            if (!has_edge(player, nb)) { snprintf(msg, sizeof msg, "前面是墙（撞墙不消耗回合）"); continue; }

            if (river[nb]) { snprintf(msg, sizeof msg, "前面是河，过不去——试试把箱子推下去搭桥"); continue; }

            int bk = box_at(nb);
            if (bk >= 0) {
                /* 推箱子：只能往河里推，箱子落水就变成桥 */
                int br = r + dr, bc = c + dc;
                if (br < 0 || br >= N || bc < 0 || bc >= N) { snprintf(msg, sizeof msg, "箱子后面到头了，推不动"); continue; }
                int dest = br * N + bc;
                if (!has_edge(nb, dest)) { snprintf(msg, sizeof msg, "箱子后面是墙，推不动"); continue; }
                if (!river[dest])        { snprintf(msg, sizeof msg, "箱子只能推进河里"); continue; }

                river[dest] = false;
                bridge[dest] = true;
                boxPos[bk] = boxPos[--nbox];      /* 箱子沉底, 从列表里移除 */
                steps++;
                snprintf(msg, sizeof msg, "箱子推进河里，沉下去变成了桥！");
            } else {
                player = nb;
                steps++;

                if (item[player] == ITEM_HEART) {
                    hp += HEAL; if (hp > HP_MAX) hp = HP_MAX;
                    item[player] = ITEM_NONE;
                    snprintf(msg, sizeof msg, "捡到一颗心，生命 +%d", HEAL);
                } else if (item[player] == ITEM_FREEZE) {
                    frozen = FREEZE_TURNS;
                    used_freeze = 1;
                    item[player] = ITEM_NONE;
                    snprintf(msg, sizeof msg, "定身符生效：%d 回合内鬼动不了，也伤不到你", FREEZE_TURNS);
                } else {
                    snprintf(msg, sizeof msg, "W/A/S/D 或方向键移动   R 看路线   Q 退出");
                }

                if (player == exitc) {
                    won = 1; level_over = 1;
                    snprintf(msg, sizeof msg, "逃出去了！第 %d 关完成，用了 %d 步，剩 %d 点生命",
                             level, steps, hp);
                    continue;
                }
            }

            /* 玩家撞到鬼 */
            int hit = 0;
            if (ghost_catches(gp, ng, player)) {
                if (frozen > 0) {
                    /* 定身符生效期间：鬼被定住，撞上也不掉血 */
                    snprintf(msg, sizeof msg, "定身符护体：鬼动不了，撞上也不掉血");
                } else if (inv > 0) {
                    snprintf(msg, sizeof msg, "撞上鬼了，但无敌状态挡住了这次伤害");
                } else {
                    hp -= DMG; inv = INV_TURNS; hit = 1;
                    snprintf(msg, sizeof msg, "被鬼抓到了！生命 -%d，进入 %d 回合无敌", DMG, INV_TURNS);
                    if (hp <= 0) { level_over = 1; snprintf(msg, sizeof msg, "第 %d 关：被鬼抓住了……GAME OVER", level); }
                }
            }

            if (!level_over) {
                bfs(player, distp);
                if (frozen == 0) ghost_move(gp, gpv, ng, distp);

                /* 鬼追上你时同样受定身保护 */
                if (frozen <= 0 && ghost_catches(gp, ng, player) && !hit && inv <= 0) {
                    hp -= DMG; inv = INV_TURNS;
                    snprintf(msg, sizeof msg, "被鬼追上！生命 -%d，进入 %d 回合无敌", DMG, INV_TURNS);
                    if (hp <= 0) { level_over = 1; snprintf(msg, sizeof msg, "第 %d 关：被鬼抓住了……GAME OVER", level); }
                }
            }

            /* 回合结束：无敌和定身计时（本回合刚触发的不扣） */
            if (!hit && inv > 0) inv--;
            if (!used_freeze && frozen > 0) frozen--;
        }

        if (quit) break;
        if (!won) break;                 /* 生命耗尽，游戏结束 */

        /* ---- 过关：回血 + 进入难度更高的下一关 ---- */
        total_steps += steps;
        int hp_before = hp;
        hp += HEAL_ON_CLEAR;
        if (hp > HP_MAX) hp = HP_MAX;
        int cleared = level;
        level++;

        LevelCfg nx;
        level_cfg(level, baseN, baseExtra, &nx);
        printf("\n第 %d 关通过！本关 %d 步，累计 %d 步，生命 %d -> %d/%d\n",
               cleared, steps, total_steps, hp_before, hp, HP_MAX);
        printf("下一关：%dx%d 迷宫，鬼 %d 只，心 %d 个，定 %d 个\n",
               nx.n, nx.n, nx.ghosts, nx.hearts, nx.freezes);
        printf("按任意键进入第 %d 关...", level);
        fflush(stdout);
        (void)_getch();
    }

    if (!quit) {
        printf("\n按任意键退出...");
        fflush(stdout);
        (void)_getch();
    }

    free_routes();
    free_graph();
    return 0;
}
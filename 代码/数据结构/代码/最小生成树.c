#include <stdio.h>
#include <stdlib.h>
#define MAX_VEX 100
#define INF 99999  
// 代表“无限大”，表示这两个村之间没路

// ---------- 带权重的邻接矩阵（网） ----------
typedef struct {
    int arcs[MAX_VEX][MAX_VEX]; 
	// 存的是权重（造价）
    int vexNum;
} WGraph;

// 初始化：默认全部断网（INF）
void initWGraph(WGraph *G, int n) {
    G->vexNum = n;
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            G->arcs[i][j] = INF;
        }
    }
}
// 修一条双向路（无向网）
void addWeightedEdge(WGraph *G, int u, int v, int w) {
    G->arcs[u][v] = w;
    G->arcs[v][u] = w;
}

// ----------Prim算法（求最小生成树）----------
void prim(WGraph *G, int start) {
    int visited[MAX_VEX] = {0};  
// 记录哪些村已经通网了
    int lowcost[MAX_VEX];        
// 记录“当前已通网区域”到“每个未通网村子”的最短距离
    int adjvex[MAX_VEX];         
// 记录这个最短距离是跟哪个已通网村子连的

// 1. 初始化：从 start 村开始动工
    visited[start] = 1;
    int i,j; 
    for (i = 0; i < G->vexNum; i++) {
        lowcost[i] = G->arcs[start][i];
        adjvex[i] = start;
    }

    int totalWeight = 0;
    printf("【最小生成树修建步骤】\n");
    
// 2. 还需要再连通 (n-1) 个村子
    for (i = 1; i < G->vexNum; i++) {
        int min = INF;
        int minIndex = -1;

// 2.1 从“未通网的村子”里，挑一个距离当前网最近的
        for (j = 0; j < G->vexNum; j++) {
            if (!visited[j] && lowcost[j] < min) {
                min = lowcost[j];
                minIndex = j;
            }
        }

// 2.2 把这个最近的村拉入网（修路）
        if (minIndex != -1) {
            visited[minIndex] = 1;
            totalWeight += min;
            printf("   修 %c --- %c ，造价: %d\n", 'A' + adjvex[minIndex], 'A' + minIndex, min);

// 2.3 新村子入网了，更新“到其他未入网村子”的最短距离
            for (j = 0; j < G->vexNum; j++) {
                if (!visited[j] && G->arcs[minIndex][j] < lowcost[j]) {
                    lowcost[j] = G->arcs[minIndex][j];
                    adjvex[j] = minIndex;
                }
            }
        }
    }
    printf("   总造价（最小生成树权重和）: %d\n",totalWeight);
}

// ---------- 主函数测试 ----------
int main() {
    WGraph G;
    initWGraph(&G, 4); 
	// A=0, B=1, C=2, D=3

// 修路数据:A-B造价6,A-C造价1,A-D造价5,B-C造价5,C-D造价4
    addWeightedEdge(&G, 0, 1, 6);
    addWeightedEdge(&G, 0, 2, 1);
    addWeightedEdge(&G, 0, 3, 5);
    addWeightedEdge(&G, 1, 2, 5);
    addWeightedEdge(&G, 2, 3, 4);

    // 从 A (下标0) 开始修网
    prim(&G, 0);
    return 0;
}

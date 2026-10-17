#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

// ---------- 邻接表结构 ----------
//结构体定义（邻接表：墙上挂名单 + 每人兜里的小纸条）
//定义“小纸条”的结构（边表结点）
typedef struct EdgeNode {
    int adjvex;            
	// 这张纸条上写的是“谁”的编号（比如 2 代表 C）
    struct EdgeNode *next; 
	// 指向下一个小纸条（兜里可能揣着好几张）
} EdgeNode;

// 定义“墙上名单”的结构（顶点表结点）
typedef struct VertexNode {
    char data;             
	// 这个人的名字（比如 'A'）
    EdgeNode *firstEdge;   
	// 指向这个人兜里的“第一张小纸条”
} VertexNode;

// 定义整个朋友圈（图）
typedef struct {
    VertexNode vexList[MAX_VEX]; 
	// 墙上的名单数组（最多100个人）
    int vexNum;                  
	// 当前实际有多少个人
} ALGraph;

// 初始化：给每个人起名字，先把兜里清空（指针指向 NULL）
void initALGraph(ALGraph *G, int n) {
    G->vexNum = n;
    int i; 
    for (i = 0; i < n; i++) {
        G->vexList[i].data = 'A' + i; 
		// 'A'+0='A', 'A'+1='B'……
        G->vexList[i].firstEdge = NULL; 
		// 刚开始谁都不认识，兜里没纸条
    }
}

// 添加无向边：A加B，B也要加A（互相在对方兜里塞纸条）
void addEdge(ALGraph *G, int start, int end) {
//第一步：在 start 的兜里塞一张纸条，写上 end 的编号
    EdgeNode *e1 = (EdgeNode *)malloc(sizeof(EdgeNode));
    e1->adjvex = end;
    e1->next = G->vexList[start].firstEdge; 
	// 新纸条指向原来的第一张（头插法）
    G->vexList[start].firstEdge = e1;       
	// 新纸条成为新的第一张

//第二步:因为是双向好友,在end的兜里也塞一张纸条,
//		 写上start的编号
    EdgeNode *e2 = (EdgeNode *)malloc(sizeof(EdgeNode));
    e2->adjvex = start;
    e2->next = G->vexList[end].firstEdge;
    G->vexList[end].firstEdge = e2;
}

// ----------广度优先搜索（BFS）核心代码----------
void BFS(ALGraph *G, int start) {
    int visited[MAX_VEX] = {0};
    int queue[MAX_VEX];          
	// 用数组模拟一个排队队列
    int front = 0, rear = 0;     
	// 队头队尾指针

// 1. 起点先入队，并标记
    visited[start] = 1;
    queue[rear++] = start;

// 2. 只要队伍不空，就一直处理
    while (front < rear) {
// 2.1 从队头“弹”出一个节点（当前层的节点）
        int v = queue[front++];
        printf("%c ", G->vexList[v].data);

// 2.2 把这个节点的所有"还没入队"的邻居,
//	统统塞进队尾（下一层）
        EdgeNode *p = G->vexList[v].firstEdge;
        while (p != NULL) {
            int neighbor = p->adjvex;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor; 
				// 入队
            }
            p = p->next;
        }
    }
}

// ---------- 主函数测试 ----------
int main() {
    ALGraph G;
    int n = 5; 
    initALGraph(&G, n); 
    
    addEdge(&G, 0, 1); // A-B
    addEdge(&G, 1, 2); // B-C
    addEdge(&G, 2, 3); // C-D
    addEdge(&G, 3, 4);
    
    printf("【BFS广度优先遍历】从 A 出发: ");
    BFS(&G, 0);
    return 0;
}

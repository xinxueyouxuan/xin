/*邻接表 —— “每个人兜里揣个小纸条”
做法：在墙上贴一张“所有人名单”（顶点表）。
	每个人名字旁边，挂一个小纸条（链表），纸条上只写你亲自认识的人的名字。
打个比方：就像你手机里的微信好友列表。
	你只存了你认识的那几十个人，没必要把全中国 14 亿人都存进手机里。
优点：极其省空间。我只存真实存在的好友关系。
缺点：想知道“张三认不认识李四”？你得先找到张三，
	然后在他那一长串纸条里挨个翻（遍历），比查表格慢一点。
结论：这个办法适合“关系比较稀疏”的情况（稀疏图），
	比如现实中的社交网络。
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

// 1. 定义“小纸条”结点（边表结点）
typedef struct EdgeNode {
    int adjvex; 
	// 这个纸条上写的是“谁”的编号（邻接点）
    struct EdgeNode *next;
	// 指向下一个小纸条
} EdgeNode;

// 2. 定义“墙上贴的名单”（顶点表结点）
typedef struct {
    char data;                 
	// 这个人的名字（随便存个字母）
    EdgeNode *firstEdge;       
	// 指向他兜里的第一个小纸条
} VertexNode;

// 3. 定义整个图结构
typedef struct {
    VertexNode vexList[MAX_VEX]; 
	// 墙上的名单列表
    int vexNum;                  
	// 总人数
} ALGraph;

// 4.初始化：把每个人的名字写上，
	//并且让他们兜里先空着（指针指向NULL）
void initALGraph(ALGraph *G, int n) {
    G->vexNum = n;
    int i;
    for (i = 0; i < n; i++) {
        G->vexList[i].data = 'A' + i; 
		// 取名 A, B, C, D ...
        G->vexList[i].firstEdge = NULL; 
		// 兜里暂时没纸条
    }
}

// 5. 添加好友（头插法：新纸条直接塞到兜里最上面）
void addEdgeAL(ALGraph *G, int start, int end) {
    // 因为是无向图，需要互相存
    // 第一步：在 start 的兜里塞一张纸条，写上 end
    EdgeNode *e1 = (EdgeNode *)malloc(sizeof(EdgeNode));
    e1->adjvex = end;
    e1->next = G->vexList[start].firstEdge;
    G->vexList[start].firstEdge = e1;

    // 第二步：在 end 的兜里塞一张纸条，写上 start
    EdgeNode *e2 = (EdgeNode *)malloc(sizeof(EdgeNode));
    e2->adjvex = start;
    e2->next = G->vexList[end].firstEdge;
    G->vexList[end].firstEdge = e2;
}

// 6. 打印每个人的“好友小纸条”
void printALGraph(ALGraph *G) {
    printf("\n【邻接表 - 每人兜里的小纸条】\n");
    int i;
	for (i = 0; i < G->vexNum; i++) {
        printf("  %c 的好友有: ", G->vexList[i].data);
        EdgeNode *p = G->vexList[i].firstEdge;
        while (p != NULL) {
            printf(" -> %c ", G->vexList[p->adjvex].data); // 通过编号找到名字
            p = p->next;
        }
        printf(" (纸条翻完了)\n");
    }
}

// ---------- 主函数测试 ----------
int main() {
    ALGraph G;
    initALGraph(&G, 4); // A, B, C, D 四个人

    // 建立同样的关系：A-B, B-C, C-D
    addEdgeAL(&G, 0, 1); // A 和 B 互加
    addEdgeAL(&G, 1, 2); // B 和 C 互加
    addEdgeAL(&G, 2, 3); // C 和 D 互加

    printALGraph(&G);
    return 0;
}

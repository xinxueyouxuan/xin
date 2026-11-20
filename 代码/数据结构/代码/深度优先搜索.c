//深度优先搜索（DFS）——“不撞南墙不回头”

#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

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

// ----------深度优先搜索（DFS）核心函数----------
//参数解释：
//G: 指向朋友圈的指针
//v: 当前正在“串门”的人的下标（比如 0 代表 A）
//visited[]: 一个"签到表",0代表还没去拜访过,1代表已经拜访过了
void DFS(ALGraph *G, int v, int visited[]) {
    
    // 第1步：【拜访当前这个人】
    visited[v] = 1;                 
	// 在签到表上打个勾，表示“我来过了”
    printf("%c ", G->vexList[v].data); 
	// 打印这个人的名字，表示我拜访了他

    // 第2步：【查他兜里的小纸条，决定下一步去哪】
    // 掏出他兜里的第一张纸条，顺着纸条链表往下翻
    EdgeNode *p = G->vexList[v].firstEdge; 
    
    while (p != NULL) { 
	// 只要兜里还有纸条（还有没翻完的邻居）
        
        int neighbor = p->adjvex; 
	// 这张纸条上写着的“邻居编号”
        
    // 第3步：【核心递归逻辑——“不撞南墙不回头”】
    // 如果这个邻居在签到表上是 0（说明从来没拜访过）
        if (!visited[neighbor]) {
    //那就立马放下手头的事,递归调用自己,去深度拜访这个邻居！
    //注意：这里没有 for 循环回去,
	//	而是顺着邻居一直往下挖，直到挖不动了才回退
            DFS(G, neighbor, visited);
        }
        
//如果这个邻居已经拜访过了,就不理他,翻看兜里下一张纸条
        p = p->next; // 指针后移，翻下一张纸条
    }

//当while循环结束(兜里纸条翻完了),这个函数就结束了
//此时程序会"回溯"到上一个调用它的地方
//继续翻上一个人的下一张纸条
//这就是所谓的"一条路走到黑,走不通再退回来"
}

// ---------- 主函数 ----------
int main() {
    ALGraph G;
    int n = 5;
    initALGraph(&G, n); 
	// 初始化 4 个人：A, B, C, D
    
    // 建立好友关系：A-B, B-C, C-D （形成一条链）
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);
    addEdge(&G, 3, 4);
    
    int visited[MAX_VEX] = {0}; 
	// 一开始所有人都是 0（都没拜访过）
    printf("【DFS深度优先遍历】从 A 出发: ");
    DFS(&G, 0, visited); 
	// 从下标 0（即 A）开始“串门”
    
    return 0;
}

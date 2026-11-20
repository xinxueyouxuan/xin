/*邻接矩阵——“Excel大表格”
做法：画一个方方正正的表格。横着写所有人的名字，竖着也写所有人的名字。
如果A行B列打了√（1），就说明A和B是好友。
如果打了×（0），就不是好友。
打个比方：就像班级里的座位表，横竖都是同学，交叉点画圈代表认识。
优点：特别简单粗暴。想知道俩人认不认识？一眼扫过去，O(1)时间贼快！
缺点：太费纸（费内存)！假如全校有1万人，你得画一个1亿个格子的表，哪怕你只认识隔壁 3 个人，这 1亿 个格子里绝大多数都是空的（×），白白浪费空间。
结论：这个办法适合“关系特别密集”的情况（稠密图），比如一个几百人的封闭小团体。
*/

//适用场景：关系密集、总爱问“这俩人是不是好友”
#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100  
// 假设最多100个人

// 1. 定义“大表格”结构体
typedef struct {
    int arcs[MAX_VEX][MAX_VEX];
	// 二维数组，就是那个方方正正的表格
    int vexNum;
	// 当前有多少个人（顶点数）
} MatrixGraph;

// 2. 初始化：把表格里所有的格子都清零
	//（表示大家互相都不认识）
void initMatrix(MatrixGraph *G, int n) {
    G->vexNum = n;
    int i,j; 
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            G->arcs[i][j] = 0;  
			// 0 代表不认识
        }
    }
}

// 3. 添加好友关系（无向图：你加我，我加你，双向的）
void addEdge(MatrixGraph *G, int start, int end) {
    // 因为是无向图，要在表格里对称打两个√
    G->arcs[start][end] = 1;
    G->arcs[end][start] = 1;
}

// 4. 打印这个“大表格”，看看谁认识谁
void printMatrix(MatrixGraph *G) {
    printf("\n【邻接矩阵大表格】 (行代表起点, 列代表终点, 1代表有连线)\n");
    printf("   ");
    int i,j;
    for (i = 0; i < G->vexNum; i++) {
        printf("  v%d", i);  // 打印列头
    }
    printf("\n");
    for (i = 0; i < G->vexNum; i++) {
        printf(" v%d", i);   // 打印行头
        for (j = 0; j < G->vexNum; j++) {
            printf("  %d ", G->arcs[i][j]);
        }
        printf("\n");
    }
}

// ---------- 主函数测试 ----------
int main() {
    MatrixGraph G;
    initMatrix(&G, 4);  
	// 假设有 4 个人：v0, v1, v2, v3

    // 建立关系：v0 认识 v1；v1 认识 v2；v2 认识 v3
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 2, 3);

    printMatrix(&G);
    return 0;
}

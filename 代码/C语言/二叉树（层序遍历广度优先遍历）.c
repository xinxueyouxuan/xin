#include <stdio.h>
#include <stdlib.h>

// 二叉树节点结构
typedef char Type;
typedef struct BiTNode {
    Type data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 队列节点（用于层序遍历）
typedef struct QNode {
    BiTree data;          // 队列中存放的是二叉树节点的指针
    struct QNode *next;
} QNode;

// 队列结构（带头尾指针的链式队列）
typedef struct {
    QNode *front;         // 队头指针
    QNode *rear;          // 队尾指针
} LinkQueue;

// 示例先序序列，用于创建二叉树（#代表空节点）
char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;              // 遍历序列的索引

/*
 * 初始化队列
 */
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
}

/*
 * 判断队列是否为空
 * 返回1为空，0为非空
 */
int QueueEmpty(LinkQueue Q) {
    return (Q.front == Q.rear);
}

/*
 * 入队：将二叉树节点指针存入队列
 */
void EnQueue(LinkQueue *Q, BiTree p) {
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    newNode->data = p;
    newNode->next = NULL;
    Q->rear->next = newNode;
    Q->rear = newNode;
}

/*
 * 出队：取出队头元素（二叉树节点指针）
 */
BiTree DeQueue(LinkQueue *Q) {
    if (QueueEmpty(*Q)) {
        printf("队列为空，无法出队！\n");
        return NULL;
    }
    QNode *p = Q->front->next;
    BiTree e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)          // 如果出队的是最后一个元素，需修改尾指针
        Q->rear = Q->front;
    free(p);
    return e;
}

/*
 * 销毁队列，释放所有节点（包括头节点）
 */
void DestroyQueue(LinkQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

/*
 * 根据先序序列递归创建二叉树
 * T：二级指针，用于修改父节点的孩子指针
 */
void CreateBiTree(BiTree *T) {
    Type ch = str[idx++];
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

/*
 * 层序遍历（广度优先遍历）
 * 思路：
 *   1. 根节点入队。
 *   2. 队列不空时，出队一个节点，访问它。
 *   3. 如果该节点有左孩子，左孩子入队；如果有右孩子，右孩子入队。
 *   4. 重复2~3，直到队列为空。
 */
void LevelOrder(BiTree T) {
    if (T == NULL) {
        printf("空树！\n");
        return;
    }
    LinkQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);           // 根节点入队

    printf("层序遍历结果: ");
    while (!QueueEmpty(Q)) {
        BiTree p = DeQueue(&Q);   // 出队并访问
        printf("%c ", p->data);

        if (p->lchild != NULL)    // 左孩子存在则入队
            EnQueue(&Q, p->lchild);
        if (p->rchild != NULL)    // 右孩子存在则入队
            EnQueue(&Q, p->rchild);
    }
    printf("\n");

    DestroyQueue(&Q);
}

/*
 * 递归释放二叉树所有节点（后序遍历）
 */
void FreeBiTree(BiTree T) {
    if (T != NULL) {
        FreeBiTree(T->lchild);
        FreeBiTree(T->rchild);
        free(T);
    }
}

int main() {
    BiTree T = NULL;

    // 1. 创建二叉树（利用全局先序序列）
    printf("根据先序序列创建二叉树...\n");
    CreateBiTree(&T);

    // 2. 层序遍历
    LevelOrder(T);

    // 3. 释放内存
    FreeBiTree(T);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef char Type;

// 线索二叉树节点结构
typedef struct ThreadNode {
    Type data;                  // 节点数据
    struct ThreadNode *lchild;  // 左孩子指针
    struct ThreadNode *rchild;  // 右孩子指针
    int ltag;                   // 左标志：0-指向左孩子，1-指向前驱
    int rtag;                   // 右标志：0-指向右孩子，1-指向后继
} ThreadNode;

typedef ThreadNode *ThreadTree;

// 先序序列（#表示空节点），用于构建二叉树
char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;                    // 遍历序列的索引

ThreadTree prev;                // 全局变量，记录中序线索化时的前一个访问节点

/*
 * 根据先序序列递归创建二叉树（仅建立节点，未线索化）
 * T：二级指针，用于修改父节点的孩子指针
 */
void createTree(ThreadTree *T) {
    Type ch;
    ch = str[idx++];
    if (ch == '#') {
        *T = NULL;              // 空节点
    } else {
        // 分配新节点
        *T = (ThreadTree)malloc(sizeof(ThreadNode));
        if (*T == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }
        (*T)->data = ch;        // 存储数据
        (*T)->ltag = 0;         // 初始化为0，表示指向孩子
        (*T)->rtag = 0;

        createTree(&(*T)->lchild);  // 递归创建左子树
        createTree(&(*T)->rchild);  // 递归创建右子树
    }
}

/*
 * 中序线索化（递归）
 * p：当前节点
 * 利用全局变量 prev 记录前一个访问的节点，在线索化过程中建立线索
 */
void inThreading(ThreadTree p) {
    if (p != NULL) {
        inThreading(p->lchild);     // 递归左子树线索化

        // 处理当前节点的前驱线索
        if (p->lchild == NULL) {    // 左孩子为空，建立前驱线索
            p->ltag = 1;
            p->lchild = prev;
        }
        // 处理前一个节点的后继线索
        if (prev != NULL && prev->rchild == NULL) {
            prev->rtag = 1;
            prev->rchild = p;
        }
        prev = p;                   // 保持 prev 指向 p 的前驱

        inThreading(p->rchild);     // 递归右子树线索化
    }
}

/*
 * 建立中序线索二叉树的头结点，并完成整棵树的中序线索化
 * head：头结点（二级指针，需要修改主函数中的指针）
 * T：需要线索化的二叉树根节点
 * 头结点结构：
 *   lchild 指向根节点
 *   rchild 指向中序遍历的最后一个节点
 *   中序的第一个节点的 lchild 指向头结点
 *   中序的最后一个节点的 rchild 指向头结点
 */
void createInThread(ThreadTree *head, ThreadTree T) {
    // 创建头结点
    *head = (ThreadTree)malloc(sizeof(ThreadNode));
    if (*head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    (*head)->ltag = 0;          // ltag=0，因为左孩子指向根节点
    (*head)->rtag = 1;          // rtag=1，因为右孩子作为线索指向最后一个节点
    (*head)->rchild = *head;    // 初始回指（处理空树情况）

    if (T == NULL) {
        // 空树：头结点的 lchild 指向自己
        (*head)->lchild = *head;
    } else {
        (*head)->lchild = T;    // 头结点左孩子指向根节点
        prev = *head;           // prev 初始为头结点

        inThreading(T);         // 中序线索化二叉树

        // 线索化结束后，prev 指向中序遍历的最后一个节点
        prev->rchild = *head;   // 最后一个节点的右孩子指向头结点
        prev->rtag = 1;         // 标记为线索
        (*head)->rchild = prev; // 头结点的右孩子指向最后一个节点
    }
}

/*
 * 中序遍历线索二叉树（利用线索，非递归）
 * head：头结点
 */
void inOrderTraverse(ThreadTree head) {
    ThreadTree p = head->lchild;           // p 指向根节点
    while (p != head) {                    // 空树或遍历结束（回到头结点）
        while (p->ltag == 0) {             // 沿左链找到中序第一个节点
            p = p->lchild;
        }
        printf("%c ", p->data);            // 访问节点

        // 如果右标志为线索，则持续沿后继访问
        while (p->rtag == 1 && p->rchild != head) {
            p = p->rchild;
            printf("%c ", p->data);
        }
        p = p->rchild;                     // 转向右子树（可能是孩子或头结点）
    }
}

/*
 * 递归释放二叉树所有节点（包括头结点）
 * 释放时需要区分普通子树和线索，这里采用递归方式释放原始树结构（忽略线索）
 */
void freeThreadTree(ThreadTree *T) {
    if (*T != NULL) {
        // 如果左标志为0，说明左孩子存在，递归释放
        if ((*T)->ltag == 0) {
            freeThreadTree(&(*T)->lchild);
        }
        // 如果右标志为0，说明右孩子存在，递归释放
        if ((*T)->rtag == 0) {
            freeThreadTree(&(*T)->rchild);
        }
        free(*T);
        *T = NULL;
    }
}

int main() {
    ThreadTree head;    // 线索化后的头结点
    ThreadTree T;       // 二叉树的根节点

    // 1. 根据先序序列创建二叉树
    printf("正在根据先序序列创建二叉树...\n");
    createTree(&T);

    // 2. 建立中序线索二叉树（含头结点）
    printf("正在建立中序线索...\n");
    createInThread(&head, T);

    // 3. 中序遍历线索二叉树（非递归）
    printf("中序遍历结果: ");
    inOrderTraverse(head);
    printf("\n");

    // 4. 释放内存（注意：头结点的左孩子为根，先释放根子树，再释放头结点）
    //    由于线索化后节点的左右指针可能被修改，需按原树结构释放。
    //    简便起见，我们直接从根节点采用递归方式释放（忽略线索），然后释放头结点。
    if (head != NULL) {
        if (head->ltag == 0) {   // 如果头结点的左孩子是普通指针（即根存在）
            freeThreadTree(&head->lchild);
        }
        free(head);
    }

    return 0;
}

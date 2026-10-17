#include <stdio.h>
#include <stdlib.h>

typedef char Type;

// 定义二叉树节点
typedef struct treeNode {
    Type data;               // 节点数据
    struct treeNode *lchild; // 左孩子指针
    struct treeNode *rchild; // 右孩子指针
} treeNode;

typedef treeNode* BiTree;    // 二叉树指针类型

// 二叉树的前序遍历（根 -> 左 -> 右）
void preOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c ", T->data);      // 访问根节点
    preOrder(T->lchild);         // 遍历左子树
    preOrder(T->rchild);         // 遍历右子树
}

// 二叉树的中序遍历（左 -> 根 -> 右）
void inOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    inOrder(T->lchild);          // 遍历左子树
    printf("%c ", T->data);      // 访问根节点
    inOrder(T->rchild);          // 遍历右子树
}

// 二叉树的后序遍历（左 -> 右 -> 根）
void postOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    postOrder(T->lchild);        // 遍历左子树
    postOrder(T->rchild);        // 遍历右子树
    printf("%c ", T->data);      // 访问根节点
}

// 创建一个新节点
BiTree createNode(Type data) {
    BiTree newNode = (BiTree)malloc(sizeof(treeNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// 释放二叉树占用的内存（后序遍历方式释放）
void freeTree(BiTree T) {
    if (T == NULL) {
        return;
    }
    freeTree(T->lchild);  // 先释放左子树
    freeTree(T->rchild);  // 再释放右子树
    free(T);              // 最后释放根节点
}

int main() {
    BiTree T;

    // 手动构建一棵二叉树，形状如下：
    //         A
    //       /  \
    //      B    C
    //     / \  /
    //    D  E F
    // 根据节点关系逐个创建并连接
    BiTree nodeA = createNode('A');
    BiTree nodeB = createNode('B');
    BiTree nodeC = createNode('C');
    BiTree nodeD = createNode('D');
    BiTree nodeE = createNode('E');
    BiTree nodeF = createNode('F');

    // 连接左右子树
    nodeA->lchild = nodeB;
    nodeA->rchild = nodeC;
    nodeB->lchild = nodeD;
    nodeB->rchild = nodeE;
    nodeC->lchild = nodeF;   // C的右孩子为空

    T = nodeA;  // 根节点为A

    // 测试前序遍历
    printf("前序遍历结果: ");
    preOrder(T);
    printf("\n");

    // 测试中序遍历
    printf("中序遍历结果: ");
    inOrder(T);
    printf("\n");

    // 测试后序遍历
    printf("后序遍历结果: ");
    postOrder(T);
    printf("\n");

    // 释放整棵树的内存
    freeTree(T);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// ---------- 遍历 ----------
void PreOrder(BiTree T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T)
{
    if (T)
    {
        InOrder(T->lchild);
        printf("%c ", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T)
{
    if (T)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c ", T->data);
    }
}

// ---------- 建节点 ----------
BiTree createNode(ElemType data)
{
    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    if (!newNode)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// ---------- 层序创建二叉树 ----------
// 约定：'^' 表示该位置为空；空节点不占用孩子位置
BiTree CreateBiTreeLevel(char *str)
{
    if (str == NULL || str[0] == '\0' || str[0] == '^')
        return NULL;

    // 简易队列（数组实现），存放"等待挂孩子的节点"
    BiTree queue[100];
    int front = 0, rear = 0;

    // 根节点
    BiTree root = createNode(str[0]);
    queue[rear++] = root;

    int i = 1;   // 从第 2 个字符开始读
    while (i < (int)strlen(str) && front < rear)
    {
        BiTree parent = queue[front++];   // 取出一个待挂孩子的父节点

        // 挂左孩子
        if (i < (int)strlen(str))
        {
            if (str[i] != '^')
            {
                BiTree left = createNode(str[i]);
                parent->lchild = left;
                queue[rear++] = left;     // 有孩子才入队
            }
            i++;
        }

        // 挂右孩子
        if (i < (int)strlen(str))
        {
            if (str[i] != '^')
            {
                BiTree right = createNode(str[i]);
                parent->rchild = right;
                queue[rear++] = right;
            }
            i++;
        }
    }
    return root;
}

int main()
{
    char arr[100];
    printf("请输入层序序列（^ 表示空节点）: ");
    scanf("%s", arr);

    BiTree T = CreateBiTreeLevel(arr);

    printf("前序遍历: ");
    PreOrder(T);
    printf("\n");

    printf("中序遍历: ");
    InOrder(T);
    printf("\n");

    printf("后序遍历: ");
    PostOrder(T);
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 256   // 最大字符种类数（ASCII）

// 哈夫曼树节点结构
typedef struct {
    char ch;            // 字符（仅叶子节点有效）
    int weight;         // 权值（字符频率）
    int parent;         // 父节点下标
    int lchild;         // 左孩子下标
    int rchild;         // 右孩子下标
} HTNode, *HuffmanTree;

// 哈夫曼编码表结构
typedef struct {
    char ch;            // 对应字符
    char code[256];     // 存放编码的字符串
} HuffmanCode;

/*
 * 构建哈夫曼树
 * n：叶子节点个数（字符种类数）
 * weight：权值数组
 * chars：字符数组（与权值一一对应）
 * HT：构建出的哈夫曼树（通过指针返回）
 */
void CreateHuffmanTree(HuffmanTree *HT, int *weight, char *chars, int n) {
    if (n <= 1) return;
    int m = 2 * n - 1;      // 哈夫曼树总节点数
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); // 0号单元不使用

    int i, j;
    // 初始化叶子节点（1~n）
    for (i = 1; i <= n; i++) {
        (*HT)[i].ch = chars[i - 1];
        (*HT)[i].weight = weight[i - 1];
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }
    // 初始化非叶子节点（n+1~m）
    for (i = n + 1; i <= m; i++) {
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].ch = '\0';
    }

    // 构建哈夫曼树（n-1次合并）
    for (i = n + 1; i <= m; i++) {
        int s1, s2;
        int min1 = MAXSIZE * 1000, min2 = MAXSIZE * 1000;
        s1 = s2 = 0;
        for (j = 1; j <= i - 1; j++) {
            if ((*HT)[j].parent == 0) {
                if ((*HT)[j].weight < min1) {
                    min2 = min1;
                    s2 = s1;
                    min1 = (*HT)[j].weight;
                    s1 = j;
                } else if ((*HT)[j].weight < min2) {
                    min2 = (*HT)[j].weight;
                    s2 = j;
                }
            }
        }
        // 合并s1, s2 为新节点i
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

/*
 * 从叶子节点向上回溯，生成哈夫曼编码
 * HT：哈夫曼树
 * HC：编码表（通过指针返回）
 * n：叶子节点数
 */
void HuffmanCoding(HuffmanTree HT, HuffmanCode **HC, int n) {
    // 修正：类型转换为指针类型 HuffmanCode*
    *HC = (HuffmanCode *)malloc((n + 1) * sizeof(HuffmanCode)); // 0号单元不用
    char *cd = (char *)malloc(n * sizeof(char));     // 临时存放编码（逆序）
    cd[n - 1] = '\0';   // 编码结束符

    int i;
    for (i = 1; i <= n; i++) {
        int start = n - 1;          // 从临时数组末尾开始存
        int c = i;                  // 当前节点
        int p = HT[i].parent;       // 父节点
        // 一直回溯到根
        while (p != 0) {
            if (HT[p].lchild == c)
                cd[--start] = '0';  // 左孩子编码0
            else
                cd[--start] = '1';  // 右孩子编码1
            c = p;
            p = HT[p].parent;
        }
        // 将临时编码复制到编码表
        (*HC)[i].ch = HT[i].ch;
        strcpy((*HC)[i].code, &cd[start]);
    }
    free(cd);
}

/*
 * 打印哈夫曼编码表（带权值）
 */
void PrintHuffmanCodeWithWeight(HuffmanCode *HC, int *weight, int n) {
    printf("字符\t权值\t编码\n");
    int i;
    for (i = 1; i <= n; i++) {
        printf("%c\t%d\t%s\n", HC[i].ch, weight[i-1], HC[i].code);
    }
}

int main() {
    // 示例：字符及频度（权值）
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int weight[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(chars) / sizeof(chars[0]);

    HuffmanTree HT = NULL;
    // 1. 构建哈夫曼树
    CreateHuffmanTree(&HT, weight, chars, n);

    // 2. 生成哈夫曼编码
    HuffmanCode *HC = NULL;   // 注意：HC 是指针
    HuffmanCoding(HT, &HC, n);

    // 3. 打印编码表
    PrintHuffmanCodeWithWeight(HC, weight, n);

    // 4. 释放内存
    free(HT);
    free(HC);

    return 0;
}

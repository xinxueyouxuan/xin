#include <stdio.h>
#include <stdlib.h> // 需要用到 malloc 和 free

/*
==========================================================
【归并排序 (Merge Sort) 复杂度总结】
----------------------------------------------------------
时间复杂度：O(n log n) 
  - 最好情况：O(n log n)
  - 最坏情况：O(n log n)
  - 平均情况：O(n log n)
  （无论数据初始状态如何，都要进行 log n 层的拆分，
    每一层都要消耗 O(n) 的时间去合并）

空间复杂度：O(n)
  （不是原地排序。每次合并都需要一个和原数组一样大的
    临时数组 temp 来存放排好序的结果）

稳定性：稳定
  （合并时，如果左右两个排头兵相等，优先拿左边的，
    保证了相同元素的相对顺序不会改变）
==========================================================
*/

// 辅助函数：打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* 
 * 【核心动作：合并 (Merge)】
 * 时间复杂度：O(n) 
 * （这里的 n 是指当前合并范围的长度 right - left + 1，
 *   因为要把这些元素挨个比较并放入临时数组，只需遍历一遍）
 * 
 * 大白话：有两个已经排好序的小分队（左半区和右半区），
 * 我们要把它们合并成一个有序的大队伍，放到一个临时数组 temp 里。
 *
 * 参数：
 * arr[]: 原数组
 * left: 左半区起点
 * mid: 左右半区的分界线
 * right: 右半区终点
 * temp[]: 用来借宿的临时大数组
 */
void merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left;      // 左半区的排头兵（指针）
    int j = mid + 1;   // 右半区的排头兵（指针）
    int k = left;      // 临时数组 temp 的记录指针（注意：temp 的填充位置从 left 开始）

    // 1. 两个小分队都有人的时候，排头兵单挑
    // 时间复杂度：最坏情况下，一个区间的元素全被遍历完 O(n)
    while (i <= mid && j <= right) {
        // 如果左边排头兵 <= 右边排头兵，左边先上
        // (注意：这里用 <= 而不是 <，是为了保证排序的“稳定性”)
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++]; // 左边的人进新队伍，左边指针后移
        } else {
            temp[k++] = arr[j++]; // 右边的人进新队伍，右边指针后移
        }
    }

    // 2. 如果左边小分队还有剩人，直接全部拉进新队伍
    // 时间复杂度：直接拷贝，O(n)
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 3. 如果右边小分队还有剩人，直接全部拉进新队伍
    // 时间复杂度：直接拷贝，O(n)
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 4. 把临时数组 temp 里排好序的成果，抄回原数组 arr
    // 时间复杂度：O(n)
    // 注意：只抄我们当前处理的范围 [left, right]
    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

/* 
 * 【分治主逻辑 (Divide & Conquer)】
 * 时间复杂度：O(n log n)
 * - 拆分：每次对半切，一共切成 log n 层。
 * - 合并：每一层所有子数组加起来，总长度都是 n，合并这 n 个元素需要 O(n)。
 * - 所以总时间 = 层数 * 每层的时间 = log n * O(n) = O(n log n)。
 * 
 * 空间复杂度：O(n) (仅仅是递归调用栈的深度 O(log n) 加上临时数组 O(n))
 * 
 * 大白话：不断从中间劈开数组，直到只剩一个元素，然后再一层层合并回来。
 */
void mergeSortRecursive(int arr[], int left, int right, int temp[]) {
    // 递归终止条件：如果左边界 >= 右边界，说明只有一个元素了，不用再分了
    if (left >= right) {
        return;
    }

    // 1. 找中间点，把数组劈成两半
    // 防止 (left + right) 溢出，用这种方式更安全
    int mid = left + (right - left) / 2; 

    // 2. 递归：左边一半去排队
    // 时间复杂度：T(n/2)
    mergeSortRecursive(arr, left, mid, temp);
    
    // 3. 递归：右边一半去排队
    // 时间复杂度：T(n/2)
    mergeSortRecursive(arr, mid + 1, right, temp);

    // 4. 左右两边都排好序了，现在把它们合并起来
    // 时间复杂度：O(n)
    merge(arr, left, mid, right, temp);
}

// 归并排序主函数（包装一下，方便调用）
// 时间复杂度：O(n log n)
// 空间复杂度：O(n)
void mergeSort(int arr[], int n) {
    // 因为归并排序需要额外空间，我们在这里统一申请。
    // 不要放在递归函数里每次申请，那样会极其浪费内存且慢。
    // 这里的空间消耗就是空间复杂度 O(n) 的主要来源
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    // 调用递归函数，初始范围是 [0, n-1]
    mergeSortRecursive(arr, 0, n - 1, temp);

    // 用完临时数组，记得释放内存（好习惯）
    free(temp);
}

int main() {
    int arr[] = {18, 98, 12, 41, 53, 31, 65, 23, 76, 89};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    printArray(arr, n);

    // 调用归并排序
    // 总时间复杂度: O(n log n)
    // 总空间复杂度: O(n)
    mergeSort(arr, n);

    printf("归并排序后数组: ");
    printArray(arr, n);

    return 0;
}
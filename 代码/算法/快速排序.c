#include <stdio.h>

/*
时间复杂度：O(n log n) (平均)
  - 最好情况：O(n log n) （每次分区都能完美对半分）
  - 最坏情况：O(n^2) （数组原本就有序，或者全是一样的数。每次只分出一个元素，退化成冒泡排序）
  - 平均情况：O(n log n) （绝大多数情况下的表现）
  （快速排序的“快”是建立在平均情况上的，所以它叫快排）

空间复杂度：O(log n)
  （不需要像归并那样申请大数组，它的额外空间全来自于**递归调用的函数栈**。
    最好情况递归树深度是 log n，最坏情况深度是 n。）

稳定性：不稳定
  （在分区交换的时候，无法保证相同元素的相对顺序。比如 [5, 5, 3]，
    基准是5，为了把3换到前面，第一个5会被直接扔到后面去，两个5的相对位置就变了）
*/

// 辅助函数：打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 辅助函数：交换两个数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* 
 * 【核心动作：分区 (Partition)】
 * 时间复杂度：O(n) （要把当前区间 [left, right] 里的所有元素都遍历一遍）
 * 空间复杂度：O(1) （只在原数组里倒腾，不需要额外空间）
 * 
 * 大白话：把区间最左边的数作为“基准(pivot)”，把小兵分两拨。
 */
int partition(int arr[], int left, int right) {
    int pivot = arr[left]; // 1. 挑最左边的作为基准
    int i = left;          // i 是左探子，找比基准大的
    int j = right;         // j 是右探子，找比基准小的

    // 当两个探子没碰头时，一直找
    while (i < j) {
        // 右探子向左走，找比基准小的数
        while (i < j && arr[j] >= pivot) {
            j--;
        }
        
        // 左探子向右走，找比基准大的数
        while (i < j && arr[i] <= pivot) {
            i++;
        }

        // 如果没碰头，说明找到了，把左边大的和右边小的交换位置
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // 最后 i 和 j 碰头了，它们共同指向的位置就是基准应该待的地方
    // 此时基准左边的全都比基准小，右边全都比基准大
    swap(&arr[left], &arr[i]); 
    
    // 返回基准最终的位置，供下一次递归划分
    return i; 
}

/* 
 * 【递归主逻辑】
 * 时间复杂度：O(n log n) (平均) / O(n^2) (最坏)
 * 
 * 大白话：不断把区间劈成两半，直到区间里只剩一个数。
 */
void quickSortRecursive(int arr[], int left, int right) {
    // 递归终止条件：区间里只有一个元素（或没有元素），说明已经有序
    if (left >= right) {
        return; 
    }

    // 1. 找基准点，并把数组分成两半
    // 这里的 partition 执行完，pivotIndex 这个位置就已经完全排好了
    int pivotIndex = partition(arr, left, right);

    // 2. 递归处理左边半边
    quickSortRecursive(arr, left, pivotIndex - 1);
    
    // 3. 递归处理右边半边
    quickSortRecursive(arr, pivotIndex + 1, right);
}

// 快速排序主函数（包装一下，方便调用）
// 总时间复杂度: O(n log n) (平均)
// 总空间复杂度: O(log n) (递归栈深度)
void quickSort(int arr[], int n) {
    quickSortRecursive(arr, 0, n - 1);
}

int main() {
    int arr[] = {18, 98, 12, 41, 53, 31, 65, 23, 76, 89};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    printArray(arr, n);

    // 调用快速排序
    quickSort(arr, n);

    printf("快速排序后数组: ");
    printArray(arr, n);

    return 0;
}
#include <stdio.h>

// 辅助函数：打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* ==========================================
 * 1. 直接插入排序 (Direct Insertion Sort)
 * 核心思想：打牌规则，维护一个有序序列，每次从无序的数中按规则插入到有序的序列中。
 * 最好时间复杂度：O(n) （数据原本有序，每次只比较1次，即笔记中的“尾插优化”）
 * 最坏时间复杂度：O(n^2) （数据逆序，第i轮需要比较i次并移动i次）
 * 空间复杂度：O(1)
 * 稳定性：稳定
 * ========================================== */
void insertionSort(int arr[], int n) {
    // 一共进行 n-1 轮
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // 当前需要插入的数
        int j = i - 1;

        // 每一轮只需要当前的数和上一个比较，如果上一个数大于当前数，则向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        // 找到合适的位置，插入当前数
        arr[j + 1] = key;
    }
}

/* ==========================================
 * 2. 冒泡排序 (Bubble Sort)
 * 核心思想：两两比较，每轮浮上来当前剩余最大的数。
 * 最好时间复杂度：O(n) （使用tag优化，当一轮冒泡没有任何交换时，说明已经是顺序，直接退出）
 * 最坏时间复杂度：O(n^2) （逆序，第i轮要比n-i次并交换n-i次）
 * 空间复杂度：O(1) （只有tag和tmp）
 * 稳定性：稳定
 * ========================================== */
void bubbleSort(int arr[], int n) {
    // 一共进行 n-1 轮
    for (int i = 0; i < n - 1; i++) {
        int tag = 0; // 交换标记，0表示本轮没有发生交换
        
        // 每轮比较的次数，因为每轮会将最大的数放到最后，所以减去i
        for (int j = 0; j < n - 1 - i; j++) {
            // 两两比较，如果前面大于后面，则交换
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                tag = 1; // 发生了交换，标记置为1
            }
        }
        
        // 优化：如果第一轮发现没有任何交换，说明数组已经有序，直接结束
        if (tag == 0) {
            break;
        }
    }
}

/* ==========================================
 * 3. 选择排序 (Selection Sort)
 * 核心思想：每轮从剩下的数中，挑出当前最小的，放到已排序序列的末尾。
 * 最好、最坏时间复杂度：都是 O(n^2) （无论数据如何，都要找n-1轮最小值）
 * 空间复杂度：O(1) （有min索引）
 * 稳定性：不稳定
 * ========================================== */
void selectionSort(int arr[], int n) {
    // 一共进行 n-1 轮
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // 假设当前i位置是最小的
        
        // 在剩下的无序序列中寻找最小的元素
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // 更新最小元素的索引
            }
        }
        
        // 如果找到的最小元素不在当前位置i，则交换
        if (min_idx != i) {
            int tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

// 主函数测试
int main() {
    // 测试数据
    int arr1[] = {5, 2, 9, 1, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {5, 2, 9, 1, 5, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {5, 2, 9, 1, 5, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("原始数组: ");
    printArray(arr1, n1);

    printf("\n--- 测试 直接插入排序 ---\n");
    insertionSort(arr1, n1);
    printArray(arr1, n1);

    printf("\n--- 测试 冒泡排序 (带tag优化) ---\n");
    bubbleSort(arr2, n2);
    printArray(arr2, n2);

    printf("\n--- 测试 选择排序 ---\n");
    selectionSort(arr3, n3);
    printArray(arr3, n3);

    return 0;
}
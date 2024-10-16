#include <stdio.h>

// 函数来交换两个元素
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 函数来获取父节点和子节点中的最大值的索引
int maxHeapify(int arr[], int n, int i) {
    int largest = i; // 初始化最大值为根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根节点大，则更新最大值
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比最大值大，则更新最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点，交换它们并继续下沉
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }

    return largest;
}

// 函数来构建最大堆
void buildMaxHeap(int arr[], int n) {
    int i;

    // 从最后一个非叶子节点开始，从下到上构建最大堆
    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

// 函数来执行堆排序
void heapSort(int arr[], int n) {
    // 构建最大堆
    buildMaxHeap(arr, n);

    // 从堆中提取元素并重新调整堆
    for (int i = n - 1; i > 0; i--) {
        // 将堆顶元素（最大值）与数组末尾的元素交换
        swap(&arr[0], &arr[i]);

        // 重新调整堆
        maxHeapify(arr, i, 0);
    }
}

// 主函数，用于演示堆排序
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
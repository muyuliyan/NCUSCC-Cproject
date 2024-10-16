#include <stdbool.h>

void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 如果在这一轮没有交换过，说明数组已经有序，可以提前结束
        if (!swapped) {
            break;
        }
    }
}

// 这个函数可以用来在排序后打印数组，但在导入数据时不会使用
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        // 这里可以替换为其他方式来处理排序后的数据
        // 例如，可以将其保存到文件或者进行其他操作
    }
}

// 主函数，用于演示冒泡排序
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, n);
    printArray(arr, n); // 这里可以替换为其他方式来处理排序后的数据
    return 0;
}
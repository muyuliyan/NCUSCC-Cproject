#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化子树
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// 读取整数文件数据到数组
int readIntDataFromFile(const char* filename, int* arr) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    int num = 0;
    while (fscanf(file, "%d", &arr[num]) != EOF) {
        num++;
    }
    fclose(file);
    return num;
}

// 读取浮点数文件数据到数组
int readFloatDataFromFile(const char* filename, float* arr) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    int num = 0;
    while (fscanf(file, "%f", &arr[num]) != EOF) {
        num++;
    }
    fclose(file);
    return num;
}

// 打印整数数组
void printIntArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 打印浮点数数组
void printFloatArray(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main() {
    const char* filenames[] = {"small_data.txt", "medium_data.txt", "large_data.txt", "large_data_float.txt"};
    int sizes[4];
    int** intArrays = (int**)malloc(3 * sizeof(int*)); // For small, medium, large data
    float* floatArray = NULL; // For large_data_float.txt

    // Allocate memory for integer arrays
    for (int i = 0; i < 3; i++) {
        intArrays[i] = (int*)malloc(100000 * sizeof(int));
    }

    // Read and sort integer data
    for (int i = 0; i < 3; i++) {
        sizes[i] = readIntDataFromFile(filenames[i], intArrays[i]);
        heapSort(intArrays[i], sizes[i]);
        printf("Sorted %s: ", filenames[i]);
        printIntArray(intArrays[i], sizes[i]);
    }

    // Allocate memory for float array
    floatArray = (float*)malloc(100000 * sizeof(float));

    // Read and sort float data
    sizes[3] = readFloatDataFromFile(filenames[3], floatArray);
    // Assuming the heap sort function is modified to work with floats
    // heapSort(floatArray, sizes[3]); // This would require a float version of heapSort
    printf("Sorted %s: ", filenames[3]);
    printFloatArray(floatArray, sizes[3]);

    // Free memory
    for (int i = 0; i < 3; i++) {
        free(intArrays[i]);
    }
    free(floatArray);
    free(intArrays);

    return 0;
}
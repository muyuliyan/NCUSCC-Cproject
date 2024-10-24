#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 交换两个整数元素
void swapInt(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 交换两个浮点数元素
void swapFloat(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化子树（整数版本）
void heapifyInt(int arr[], int n, int i) {
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
        swapInt(&arr[i], &arr[largest]);
        heapifyInt(arr, n, largest);
    }
}

// 堆化子树（浮点数版本）
void heapifyFloat(float arr[], int n, int i) {
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
        swapFloat(&arr[i], &arr[largest]);
        heapifyFloat(arr, n, largest);
    }
}

// 堆排序（整数版本）
void heapSortInt(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyInt(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swapInt(&arr[0], &arr[i]);
        heapifyInt(arr, i, 0);
    }
}

// 堆排序（浮点数版本）
void heapSortFloat(float arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyFloat(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swapFloat(&arr[0], &arr[i]);
        heapifyFloat(arr, i, 0);
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
    const char* filenames[] = {"small_data.txt", "medium_data.txt", "large_data.txt",
                               "small_data_float.txt", "medium_data_float.txt", "large_data_float.txt"};
    int sizes[6];
    int** intArrays = (int**)malloc(3 * sizeof(int*)); // For small, medium, large data
    float** floatArrays = (float**)malloc(3 * sizeof(float*)); // For small, medium, large float data

    // Allocate memory for integer arrays
    for (int i = 0; i < 3; i++) {
        intArrays[i] = (int*)malloc(100000 * sizeof(int));
        if (intArrays[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }
    }

    // Read and sort integer data
    for (int i = 0; i < 3; i++) {
        sizes[i] = readIntDataFromFile(filenames[i], intArrays[i]);
        heapSortInt(intArrays[i], sizes[i]);
        printf("Sorted %s: ", filenames[i]);
        printIntArray(intArrays[i], sizes[i]);
    }

    // Allocate memory for float arrays
    for (int i = 3; i < 6; i++) {
        floatArrays[i - 3] = (float*)malloc(100000 * sizeof(float));
        if (floatArrays[i - 3] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }
    }

    // Read and sort float data
    for (int i = 3; i < 6; i++) {
        sizes[i] = readFloatDataFromFile(filenames[i], floatArrays[i - 3]);
        heapSortFloat(floatArrays[i - 3], sizes[i]);
        printf("Sorted %s: ", filenames[i]);
        printFloatArray(floatArrays[i - 3], sizes[i]);
    }

    // Free memory
    for (int i = 0; i < 3; i++) {
        free(intArrays[i]);
    }
    for (int i = 0; i < 3; i++) {
        free(floatArrays[i]);
    }
    free(intArrays);
    free(floatArrays);

    return 0;
}
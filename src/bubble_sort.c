#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSortInt(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void bubbleSortFloat(float arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

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

void printIntArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

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
        bubbleSortInt(intArrays[i], sizes[i]);
        printf("Sorted %s: ", filenames[i]);
        printIntArray(intArrays[i], sizes[i]);
    }

    // Allocate memory for float array
    floatArray = (float*)malloc(100000 * sizeof(float));

    // Read and sort float data
    sizes[3] = readFloatDataFromFile(filenames[3], floatArray);
    bubbleSortFloat(floatArray, sizes[3]);
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
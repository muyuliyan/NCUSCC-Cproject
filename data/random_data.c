#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATA_SIZE 100000

void generateRandomData(int size, const char* filename, int isFloat) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; ++i) {
        if (isFloat) {
            double value = (double)rand() / RAND_MAX * 10000; // Generate a random float between 0 and 10000
            fprintf(file, "%f\n", value);
        } else {
            int value = rand() % 10000; // Generate a random integer between 0 and 9999
            fprintf(file, "%d\n", value);
        }
    }

    fclose(file);
}

int main() {
    // Generate different scales of data
    generateRandomData(100, "small_data.txt", 0); // 100 integers
    generateRandomData(1000, "medium_data.txt", 0); // 1000 integers
    generateRandomData(100000, "large_data.txt", 0); // 100,000 integers
    generateRandomData(100000, "large_data_float.txt", 1); // 100,000 floats

    printf("Data generation complete.\n");
    return 0;
}
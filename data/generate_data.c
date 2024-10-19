#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_data(const char* filename, int num_elements, int is_float) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < num_elements; ++i) {
        if (is_float) {
            double random_float = (double)rand() / RAND_MAX * 10000;
            fprintf(file, "%f\n", random_float);
        } else {
            int random_int = rand() % 10000;
            fprintf(file, "%d\n", random_int);
        }
    }

    fclose(file);
}

int main() {
    // Generate different scales of data
    generate_random_data("small_data.txt", 100000, 0); // Change here
    generate_random_data("medium_data.txt", 100000, 0); // Change here
    generate_random_data("large_data.txt", 100000, 0);
    generate_random_data("large_data_float.txt", 100000, 1);

    return 0;
}
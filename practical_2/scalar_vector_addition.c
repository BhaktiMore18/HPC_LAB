#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int size;
    printf("Enter size of vector: ");
    scanf("%d", &size);

    int *vector = (int*)malloc(size * sizeof(int));
    int scalar = 5;

    // Initialize the vector
    for (int i = 0; i < size; i++) {
        vector[i] = i;
    }

    for (int threads = 1; threads <= 8; threads *= 2) {
        omp_set_num_threads(threads);
        
        double start = omp_get_wtime();

        // Parallel scalar addition
        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }

        double end = omp_get_wtime();

        printf("Threads: %d, Time taken: %f seconds\n", threads, end - start);
    }

    free(vector);
    return 0;
}

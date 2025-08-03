#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 200
#define SCALAR 5

void print_vector(int *vec, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int main() {
    int vec[VECTOR_SIZE];
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vec[i] = i;
    }

    int chunk_sizes[] = {1, 5, 10, 20, 50, 100};  // Try different chunk sizes
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    printf("=== STATIC SCHEDULING ===\n");
    for (int c = 0; c < num_chunks; c++) {
        int chunk = chunk_sizes[c];
        double start = omp_get_wtime();

        #pragma omp parallel for schedule(static, chunk)
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vec[i] += SCALAR;
        }

        double end = omp_get_wtime();
        printf("Chunk size: %3d, Time: %f seconds\n", chunk, end - start);
    }

    // Reset vector
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vec[i] = i;
    }

    printf("\n=== DYNAMIC SCHEDULING ===\n");
    for (int c = 0; c < num_chunks; c++) {
        int chunk = chunk_sizes[c];
        double start = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, chunk)
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vec[i] += SCALAR;
        }

        double end = omp_get_wtime();
        printf("Chunk size: %3d, Time: %f seconds\n", chunk, end - start);
    }

    // Demonstrate `nowait`
    printf("\n=== NOWAIT DEMONSTRATION ===\n");
    int result[VECTOR_SIZE];
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < VECTOR_SIZE/2; i++) {
            result[i] = vec[i] + SCALAR;
        }

        #pragma omp for
        for (int i = VECTOR_SIZE/2; i < VECTOR_SIZE; i++) {
            result[i] = vec[i] + SCALAR;
        }
    }

    double end = omp_get_wtime();
    printf("NOWAIT used. Time: %f seconds\n", end - start);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 2000

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void fill_matrix(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
}

void matrix_addition(int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        fill_matrix(n);
        printf("\nMatrix Size: %d x %d\n", n, n);

        for (int t = 0; t < 4; t++) {
            omp_set_num_threads(threads[t]);
            clock_t start = clock();
            matrix_addition(n);
            clock_t end = clock();

            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Threads: %d, Time: %f seconds\n", threads[t], time_taken);
        }
    }

    return 0;
}

#include <stdio.h>
// #include <omp.h>

#define N 4   // number of rows
#define M 4   // number of cols

int main() {
    int i, j;
    double A[N][M], C[N][M];
    double scalar = 5.0;

    // Initialize matrix A
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            A[i][j] = i + j; // just example values
        }
    }

    // Perform matrix-scalar multiplication in parallel
    #pragma omp parallel for private(j) shared(A, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            C[i][j] = scalar * A[i][j];
        }
    }

    // Print results
    printf("Result matrix C = scalar * A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%6.2f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

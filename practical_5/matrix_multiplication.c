#include <stdio.h>
#include <stdlib.h>
// #include <omp.h>

#define N 500  // you can change size

int main() {
    int i, j, k;
    double start, end;
    double **A, **B, **C;

    // Allocate memory for matrices
    A = (double**)malloc(N * sizeof(double*));
    B = (double**)malloc(N * sizeof(double*));
    C = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        A[i] = (double*)malloc(N * sizeof(double));
        B[i] = (double*)malloc(N * sizeof(double));
        C[i] = (double*)malloc(N * sizeof(double));
    }

    // Initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;  // just using 1.0 for simplicity
            B[i][j] = 2.0;
            C[i][j] = 0.0;
        }
    }

    // Record start time
    start = omp_get_wtime();

    // Parallel Matrix Multiplication
    #pragma omp parallel for private(i, j, k) shared(A, B, C) schedule(static)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            double sum = 0.0;
            for (k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    // Record end time
    end = omp_get_wtime();


    // // Print the result matrix
    // printf("\nResult Matrix C (A x B):\n");
    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < N; j++) {
    //         printf("%d ", C[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("Matrix multiplication completed in %f seconds.\n", end - start);

    // Free memory
    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A); free(B); free(C);

    return 0;
}

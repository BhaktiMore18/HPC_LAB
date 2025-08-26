#include <stdio.h>
// #include <omp.h>

#define M 3   // rows of matrix
#define N 3   // columns of matrix

int main() {
    int A[M][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int x[N] = {1, 2, 3};
    int y[M];  // Result vector

    // Parallel Matrix-Vector Multiplication
    #pragma omp parallel for shared(A, x, y)
    for (int i = 0; i < M; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            sum += A[i][j] * x[j];
        }
        y[i] = sum;  // store result
    }

    // Print final result
    printf("Resultant Vector (y = A * x):\n");
    for (int i = 0; i < M; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
// #include <omp.h>

// Comparison functions for sorting
int asc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n;
    printf("Enter size of vectors: ");
    scanf("%d", &n);

    int* A = (int*)malloc(n * sizeof(int));
    int* B = (int*)malloc(n * sizeof(int));

    printf("Enter elements of vector A:\n");
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);

    printf("Enter elements of vector B:\n");
    for (int i = 0; i < n; i++) scanf("%d", &B[i]);

    // Sort A ascending and B descending
    qsort(A, n, sizeof(int), asc);
    qsort(B, n, sizeof(int), desc);

    int result = 0;

    // Parallel dot product
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        result += A[i] * B[i];
    }

    printf("Minimum Scalar Product (Dot Product): %d\n", result);

    free(A);
    free(B);
    return 0;
}

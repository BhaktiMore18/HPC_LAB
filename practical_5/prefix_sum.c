#include <stdio.h>
// #include <omp.h>

int main() {
    int n = 8;
    int A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int P[8];

    // Copy input into prefix array initially
    for (int i = 0; i < n; i++) {
        P[i] = A[i];
    }

    // Parallel prefix sum using log(n) steps
    for (int step = 1; step < n; step *= 2) {
        #pragma omp parallel for
        for (int i = step; i < n; i++) {
            P[i] = P[i] + P[i - step];
        }
    }

    // Print the result
    printf("Prefix Sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");

    return 0;
}

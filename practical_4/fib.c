#include <stdio.h>
// #include <omp.h>

// Recursive Fibonacci with OpenMP Tasks
long long fib(int n) {
    long long x, y;

    if (n < 2) return n;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Enter n for Fibonacci: ");
    scanf("%d", &n);

    long long result;
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single // only one thread starts tasks
        result = fib(n);
    }
    end = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}

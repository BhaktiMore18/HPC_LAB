#include <stdio.h>
// #include <omp.h>

int main() {
    int num_threads;

    // Ask user for number of threads
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    // Set number of threads at runtime
    omp_set_num_threads(num_threads);

    // Sequential Hello World
    printf("\nSequential Hello World:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello World (sequential %d)\n", i);
    }

    // Parallel Hello World
    printf("\nParallel Hello World:\n");
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello World from thread %d\n", tid);
    }

    return 0;
}

#include <stdio.h>
#include <omp.h>
int main() {
    long num_steps = 100000000;  // More steps = more accurate
    double step = 1.0 / (double)num_steps;
    double pi = 0.0;
    int num_threads;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        double x, sum = 0.0;

        for (long i = id; i < num_steps; i += nthreads) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        pi += sum;
    }

    pi *= step;

    double end_time = omp_get_wtime();
    printf("Approximate value of pi = %.15f\n", pi);
    printf("Time taken with %d thread(s): %f seconds\n", num_threads, end_time - start_time);
    return 0;
}

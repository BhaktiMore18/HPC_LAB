#include <stdio.h>
// #include <omp.h>

#define BUFFER_SIZE 5
#define NITEMS 10   // total items to produce

int buffer[BUFFER_SIZE];
int count = 0;   // current items in buffer
int in = 0, out = 0;

int main() {
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();

        if (tid == 0) { // Producer
            for (int i = 1; i <= NITEMS; i++) {
                #pragma omp critical
                {
                    if (count < BUFFER_SIZE) {   // only produce if space available
                        buffer[in] = i;
                        in = (in + 1) % BUFFER_SIZE;
                        count++;
                        printf("Producer produced: %d | Buffer count: %d\n", i, count);
                    }
                }
            }
        } 
        else if (tid == 1) { // Consumer
            for (int i = 1; i <= NITEMS; i++) {
                #pragma omp critical
                {
                    if (count > 0) {  // only consume if something is there
                        int item = buffer[out];
                        out = (out + 1) % BUFFER_SIZE;
                        count--;
                        printf("Consumer consumed: %d | Buffer count: %d\n", item, count);
                    }
                }
            }
        }
    }

    return 0;
}

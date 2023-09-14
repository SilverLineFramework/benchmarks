#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8
#define NUM_ITERATIONS 100000

typedef struct {
    int thread_num;
    int *shared_array;
} ThreadArgs;

void *thread_func(void *arg) {
    ThreadArgs *args = (ThreadArgs *) arg;
    int thread_num = args->thread_num;
    int *shared_array = args->shared_array;
    int i;
    for (i = 0; i < NUM_ITERATIONS; i++) {
        shared_array[thread_num]++;
        if (thread_num % 2 == 0) {
            shared_array[thread_num + 1]--;
        } else {
            shared_array[thread_num - 1]--;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int *shared_array = (int *) malloc(NUM_THREADS * sizeof(int));
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        shared_array[i] = 0;
        thread_args[i].thread_num = i;
        thread_args[i].shared_array = shared_array;
        pthread_create(&threads[i], NULL, thread_func, (void *) &thread_args[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int sum = 0;
    for (i = 0; i < NUM_THREADS; i++) {
        sum += shared_array[i];
    }

    printf("sum = %d\n", sum);

    free(shared_array);

    return 0;
}




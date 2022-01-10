/**
 * @file polybench/cholesky.h
 * @brief Adapted from cholesky decomposition benchmark.
 */

#include <stdio.h>
#include <math.h>
#include "../block.h"

/**
 * @brief Cholesky decomposition
 */
void block_cholesky(data_t *data) {
    int N = (int) floor(sqrtf((float)(data->len / sizeof(float))));
    int i, j, k;

    float *A = data->f32;
    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++) {
            for (k = 0; k < j; k++) {
                A[i * N + j] -= A[i * N + k] * A[j * N + k];
            }
            A[i * N + j] /= A[j * N + j];
        }
        for (k = 0; k < i; k++) {
            A[i * N + i] -= A[i * N + k] * A[i * N + k];
        }
        A[i * N + i] = sqrtf(A[i * N + i]);
    }

    printf("[Block] Cholesky N=%d\n", N);
}

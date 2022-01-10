/**
 * @file polybench/mm.c
 * @brief Matrix Multiplication; adapted from Polybench 2mm and 3mm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../block.h"

/**
 * @brief Single matrix multiplication A(ni, nk) * B(nk, nj).
 */
static float *matmul(float *A, float *B, int ni, int nj, int nk) {

    int i, j, k;
    float *res = malloc(sizeof(float) * ni * nj);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            res[i * nk + j] = 0;
            for (k = 0; k < nk; k++) {
                res[i * nk + j] += A[i * nk + k] * B[k * nj + j];
            }
        }
    }
    return res;
}


/**
 * @brief Get square matrix partition size
 */
static int partition(int len, int num) {
    return (int) floor(sqrt(
        (float) (len / sizeof(float) / num)
    ));
}


/**
 * @brief 2 Matrix Multiplications (f32)
 *
 * Splits data into 3 different square matrices.
 */
void block_2mm(data_t *data) {
    int N = partition(data->len, 3);

    float *A = data->f32;
    float *B = A + (N * N);
    float *C = B + (N * N);

    float *D = matmul(A, B, N, N, N);
    float *E = matmul(C, D, N, N, N);

    free(data->f32);
    free(D);
    data->f32 = E;
    data->len = sizeof(float) * N * N;
    printf("[Block] 2mm N=%d\n", N);
}


/**
 * @brief 3 Matrix Multiplications (f32)
 */
void block_3mm(data_t *data) {
    int N = partition(data->len, 4);

    float *A = data->f32;
    float *B = A + (N * N);
    float *C = B + (N * N);
    float *D = C + (N * N);

    float *E = matmul(A, B, N, N, N);
    float *F = matmul(C, D, N, N, N);
    float *G = matmul(E, F, N, N, N);

    free(data->f32);
    free(E);
    free(F);
    data->f32 = G;
    data->len = sizeof(float) * N * N;
    printf("[Block] 3mm N=%d\n", N);
}

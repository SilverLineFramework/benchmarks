/**
 * @file polybench/correlation.c
 * @brief Adapted from polybench correlation benchmark.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../block.h"

#define DATA_DIM 20

/** @brief Correlation (f32 -> f32)
 *
 * Casts data as a MxN float32 matrix, where N is `len / (M * 4)`.
 * Returns a MxM buffer containing the correlation matrix.
 */
void block_correlation(data_t *data) {

    int i, j, k;

    const int M = DATA_DIM;
    int N = data->len / (M * 4);
    float eps = 0.1;

    float mean[DATA_DIM];
    for (j = 0; j < M; j++) {
        mean[j] = 0.0;
        for (i = 0; i < N; i++) {
            mean[j] += data->f32[i * M + j];
        }
        mean[j] /= (float) N;
    }

    float stddev[DATA_DIM];
    for (j = 0; j < M; j++) {
        for (i = 0; i < N; i++) {
            float _centered = (data->f32[i * M + j] - mean[j]);
            stddev[j] += _centered * _centered;
        }
        stddev[j] /= (float) N;
        stddev[j] = sqrtf(stddev[j]);
        stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            data->f32[i * M + j] -= mean[j];
            data->f32[i * M + j] /= sqrtf((float) N) * stddev[j];
        }
    }

    float *corr = malloc(sizeof(float) * M * M);
    for (i = 0; i < M - 1; i++) {
        corr[i * M + i] = 1.0;
        for (j = i + 1; j < M; j++) {
            corr[i * M + j] = 0.0;
            for (k = 0; k < N; k++) {
                corr[i * M + j] += (
                    data->f32[k * M + i] * data->f32[k * M + j]);
            }
            corr[j * M + i] = corr[i * M + j];
        }
    }
    corr[(M - 1) * M + (M - 1)] = 1.0;

    free(data->f32);
    data->f32 = corr;
    data->len = sizeof(float) * M * M;
    printf("[Block] Correlation %dx%d\n", N, M);
}

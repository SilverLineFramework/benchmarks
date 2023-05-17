#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


float mat_get(matrix_t *A, int h, int w) { return A->data[h * A->w + w]; }
void mat_set(matrix_t *A, int h, int w, float x) { A->data[h * A->w + w] = x; }

matrix_t *mat_create(int h, int w) {
    matrix_t *res = malloc(sizeof(matrix_t));
    res->w = w;
    res->h = h;
    res->size = w * h;
    res->data = malloc(sizeof(float) * res->size);
    return res;
}

void mat_clear(matrix_t *mat) {
    for (int i = 0; i < mat->size; i++) { mat->data[i] = 0.0; }
}

void mat_rand(matrix_t *mat) {
    for (int i = 0; i < mat->size; i++) {
        mat->data[i] = ((float) rand()) / ((float) RAND_MAX);
    }
}

void mat_destroy(matrix_t *mat) {
    if (mat != NULL) { free(mat->data); free(mat); }
}

matrix_t *mat_multiply(matrix_t *A, matrix_t *B, matrix_t *C) {
    if (A->w != B->h) { return NULL; }
    if (C == NULL) { C = mat_create(A->h, B->w); }
    for (int i = 0; i < C->h; i++) {
        for (int j = 0; j < C->w; j++) {
            float acc = 0.0;
            for (int k = 0; k < A->w; k++) {
                acc += mat_get(A, i, k) * mat_get(B, k, j);
            }
            mat_set(C, i, j, acc);
        }
    }
    return C;
}

void mat_norm(matrix_t *A) {
    float acc = 0.0;
    for (int i = 0; i < A->size; i++) { acc += A->data[i] * A->data[i]; }
    acc = sqrt(acc);
    for (int i = 0; i < A->size; i++) { A->data[i] = A->data[i] / acc; }
}

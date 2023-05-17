#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int w;
    int h;
    int size;
    float *data;
} matrix_t;

float mat_get(matrix_t *A, int h, int w);
void mat_set(matrix_t *A, int h, int w, float x);
matrix_t *mat_create(int h, int w);
void mat_clear(matrix_t *mat);
void mat_norm(matrix_t *A);
matrix_t *mat_multiply(matrix_t *A, matrix_t *B, matrix_t *C);
void mat_rand(matrix_t *mat);
void mat_destroy(matrix_t *mat);

#endif

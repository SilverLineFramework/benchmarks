#include "matrix.h"
#include "api.h"
#include <math.h>   
#include <stdio.h>
#include <stdlib.h>


matrix_t *eig(matrix_t *A, int k) {
    matrix_t *x0 = mat_create(A->w, 1);
    matrix_t *x1 = mat_create(A->w, 1);
    srand(42);
    mat_rand(x0);
    for (int i = 0; i < k; i++) {
        mat_multiply(A, x0, x1);
        mat_norm(x1);
        mat_multiply(A, x1, x0);
        mat_norm(x0);
    }
    mat_destroy(x1);
    return x0;
}
int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int s = atoi(argv[3]);
    if (s > n) { s = n; }

    matrix_t *A = mat_create(n, n);
    srand(42);
    mat_rand(A);

#ifdef SILVERLINE
    char rt_uuid[64];
    runtime_get_uuid(rt_uuid);
#endif

// Full RTT benchmark
#ifdef ACTIVE
#ifdef SILVERLINE
    char topic_in[256];
    snprintf(topic_in, 256, "realm/benchmarking/in/%s", rt_uuid);
    int ch_in = ch_open(topic_in, CH_RDONLY, 0);

    char topic_out[256];
    snprintf(topic_out, 256, "realm/benchmarking/out/%s", rt_uuid);
    int ch_out = ch_open(topic_out, CH_WRONLY, 0);

    int chs[1] = {ch_in};
    while(1) {
        ch_poll(chs, 1, 0);
        ch_read_msg(ch_in, (char *) A->data, A->size * sizeof(float));
        if (isnan(A->data[0])) { return 0; }
        matrix_t *res = eig(A, k);
        ch_write_msg(ch_out, (char *) A->data, s * sizeof(float));
        mat_destroy(res);
    }
#endif
// Compute-only benchmark (spin until any message is received)
#elif defined PASSIVE
#ifdef SILVERLINE
    char topic_in[256];
    snprintf(topic_in, 256, "realm/benchmarking/in/%s", rt_uuid);
    int ch_in = ch_open(topic_in, CH_RDONLY, 0);
    char buf[1];

    period_set_flags(1);
    while(ch_read_msg(ch_in, buf, 1) == 0) {
        period_start();
        matrix_t *res = eig(A, k);
        printf("v[0]: %f\n", res->data[0]);
        mat_destroy(res);
        period_end();
    }
#endif
// One-shot benchmark
#else
    matrix_t *res = eig(A, k);
    printf("v[0]: %f\n", res->data[1]);
    mat_destroy(res);
    return 0;
#endif
}

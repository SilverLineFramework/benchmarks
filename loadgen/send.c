#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"

#include <stdio.h>

uint64_t tv2us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec * 1000000) + (uint64_t)(ts.tv_nsec / 1000);
}

float randf() { return ((float) rand()) / ((float) RAND_MAX); }

void channel_setup(int *ch_in, int *ch_out, int *ch_bench) {
    char rt_uuid[64];
    char mod_uuid[64];
    runtime_get_uuid(rt_uuid);
    module_get_uuid(mod_uuid);

    char topic_in[256];
    snprintf(topic_in, 256, "realm/benchmarking/in/%s", rt_uuid);
    *ch_in = ch_open(topic_in, CH_WRONLY, 0);

    char topic_out[256];
    snprintf(topic_out, 256, "realm/benchmarking/out/%s", rt_uuid);
    *ch_out = ch_open(topic_out, CH_RDONLY, 0);

    char topic_benchmark[256];
    snprintf(topic_benchmark, 256, "realm/proc/profile/raw32/%s/%s",
        rt_uuid, mod_uuid);
    *ch_bench = ch_open(topic_benchmark, CH_WRONLY, 0);
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int s = atoi(argv[3]);

    int ch_in, ch_out, ch_bench;
    channel_setup(&ch_in, &ch_out, &ch_bench);

    uint32_t *results = malloc(sizeof(uint32_t) * n * k);
    float *input = malloc(sizeof(float) * s);
    srand(42);
    for (int i = 0; i < s; i++) { input[i] = randf(); }

    int j = 0;
    int chs[1] = {ch_out};
    char null[1];
    for(int round = 0; round < n; round++) {
        ch_write_msg(ch_in, (char *) input, s * sizeof(float));
        uint64_t start = tv2us();
        for(int actor = 0; actor < k; actor++) {
            ch_poll(chs, 1, 0);
            results[j++] = tv2us() - start;
            ch_read_msg(ch_out, null, 1);
        }
    }
    ch_write_msg(ch_bench, (char *) results, sizeof(uint32_t) * n * k);

    float nan[1];
    nan[0] = NAN;
    ch_write_msg(ch_in, (char *) nan, sizeof(float));
}

/**
 * @file benchmark.c
 * @brief Main benchmark dispatcher
 */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "channels.h"

#define BUF_SIZE 1000000
#define CHANNEL_IN "ch/test/in"
#define CHANNEL_OUT "ch/test/out"

int block_identity(char *buf, int len) {
    return len;
}

int block_not(char *buf, int len) {
    for (int i = 0; i < len; i++) { buf[i] = ~buf[i]; }
    return len;
}

/** @brief Dispatch table */
int (*processing_blocks[])(char *buf, int len) = {
    &block_identity,
    &block_not,
};

/**
 * @brief Benchmark state and configuration.
 */
typedef struct {
    /** Channel for data input */
    int data_in;
    /** Channel for data output */
    int data_out;
    /** Buffer for interacting with data */
    char *buf;
    /** Order of processing blocks to apply */
    int *blocks;
    /** Number of blocks */
    int num_blocks;
} benchmark_t;

/**
 * @brief Message handler / block dispatcher
 */
void handler(benchmark_t *bench) {
    int size = ch_read_msg(bench->data_in, bench->buf, BUF_SIZE);
    for (int i = 0; i < bench->num_blocks; i++) {
        if (bench->blocks[i] * sizeof(void *) < sizeof(processing_blocks)) {
            size = processing_blocks[bench->blocks[i]](bench->buf, size);
        }
    }
    ch_write_msg(bench->data_out, bench->buf, size);
}

/**
 * @brief Open channels and handle messages in a loop.
 */
int main(int argc, char *argv[]) {
    benchmark_t bench;
    bench.data_in = ch_open("ch/test/in", 0, 0);
    bench.data_out = ch_open(CHANNEL_OUT, 0, O_WRONLY);
    bench.blocks = malloc(sizeof(int) * (argc - 1));
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        bench.blocks[i - 1] = atoi(argv[i]);
    }
    bench.buf = malloc(BUF_SIZE);

    int poll_chs[] = {bench.data_in};
    while (1) {
        int res = ch_poll(poll_chs, 1, 1000);
        if (res != -1) { handler(&bench); }
    }
    return 0;
}

/**
 * @file benchmark.c
 * @brief Main benchmark dispatcher
 */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "api.h"

#define BUF_SIZE 65536

/** @brief Identity block. */
int block_identity(char *buf, int len) {
    printf("[Block] Identity -> %02X...\n", buf[0] & 0xff);
    return len;
}

/** @brief Simple bitwise not block for testing */
int block_not(char *buf, int len) {
    for (int i = 0; i < len; i++) { buf[i] = ~buf[i]; }
    printf("[Block] Bitwise Not -> %02X...\n", buf[0] & 0xff);
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
    printf("[Benchmark] Received: %02X... (%d)\n", bench->buf[0] & 0xff, size);
    for (int i = 0; i < bench->num_blocks; i++) {
        if (bench->blocks[i] * sizeof(void *) < sizeof(processing_blocks)) {
            size = processing_blocks[bench->blocks[i]](bench->buf, size);
        } else {
            printf("[Block] Invalid block index: %d\n", bench->blocks[i]);
        }
    }
    ch_write_msg(bench->data_out, bench->buf, size);
}

/** Join topic path. */
char *path_join(char *a, char *b) {
    char *res = malloc(strlen(a) + strlen(b) + 2);
    sprintf(res, "%s/%s", a, b);
    return res;
}

/** Subscribe to channels. */
void init_channels(benchmark_t *bench) {
    char uuid_buf[37];
    module_get_uuid(uuid_buf);

    char *ch_in = path_join("ch/in", uuid_buf);
    bench->data_in = ch_open(ch_in, CH_RDONLY, 0);
    free(ch_in);

    char *ch_out = path_join("ch/out", uuid_buf);
    bench->data_out = ch_open(ch_out, CH_WRONLY, 0);
    free(ch_out);
}

/** Initialize blocks. */
void init_blocks(benchmark_t *bench, int argc, char *argv[]) {
    bench->blocks = malloc(sizeof(int) * (argc - 1));
    for (int i = 1; i < argc; i++) {
        bench->blocks[i - 1] = atoi(argv[i]);
    }
    bench->num_blocks = argc - 1;
    bench->buf = malloc(BUF_SIZE);
}

/**
 * @brief Open channels and handle messages in a loop.
 */
int main(int argc, char *argv[]) {
    benchmark_t bench;
    init_channels(&bench);
    init_blocks(&bench, argc, argv);

    int poll_chs[] = {bench.data_in};
    while (1) {
        int res = ch_poll(poll_chs, 1, 10000);
        if (res > 0) { handler(&bench); }
    }
    return 0;
}

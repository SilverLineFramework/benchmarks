/**
 * @file runtime.c
 * @brief Replacement main file with runtime API hooks.
 */

#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "dp.h"

/** Join topic path. */
static char *path_join(char *a, char *b) {
    char *res = malloc(strlen(a) + strlen(b) + 2);
    sprintf(res, "%s/%s", a, b);
    return res;
}

/** Subscribe to channels. */
static void init_channels(int *in, int *out) {
    char uuid_buf[37];
    module_get_uuid(uuid_buf);

    char *ch_in = path_join("benchmark/in", uuid_buf);
    *in = ch_open(ch_in, CH_RDONLY, 0);
    free(ch_in);

    char *ch_out = path_join("benchmark/out", uuid_buf);
    *out = ch_open(ch_out, CH_WRONLY, 0);
    free(ch_out);
}

/** Exhaust input data */
static int handle_input(int data_in) {
    // Read to exhaustion
    char read_buf[1024];
    int bytes_read = 1;
    while (bytes_read > 0) {
        bytes_read = ch_read_msg(data_in, read_buf, 1024);
    }
    // Super janky exit condition
    return strncmp(read_buf, "exit", 4);
}

/** Write random output data */
static void handle_output(int data_out, dp_t *dp) {
    int size = dp_draw(dp);
    char *buf = malloc(size);
    for (int i = 0; i < size / 4; i++) {
        ((int *) buf)[i] = rand();
    }
    ch_write_msg(data_out, buf, size);
    free(buf);
}

/** Hash function: djb2 (http://www.cse.yorku.ca/~oz/hash.html) */
static unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

/** Loop function; should be called into by main */
int loop(int argc, char **argv, int (*func)(int, char **)) {

    if (argc < 1) {
        printf("argc should be at least 1!\n");
        exit(-1);
    }

    dp_t dp;
    dp_init(&dp, hash(argv[0]));

    int data_in, data_out;
    init_channels(&data_in, &data_out);

    // Start with data out to act as a ready signal
    handle_output(data_out, &dp);

    int poll_chs[] = {data_in};
    while (1) {
        int res = ch_poll(poll_chs, 1, 5000);
        if (res > 0) {
            if (!handle_input(data_in)) { break;}
            func(argc, argv);
            handle_output(data_out, &dp);
        }
    }
    return 0;
}

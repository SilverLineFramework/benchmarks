/**
 * @file runtime.c
 * @brief Replacement main file with runtime API hooks.
 */

#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "dp.h"

/** Join topic path. */
char *path_join(char *a, char *b) {
    char *res = malloc(strlen(a) + strlen(b) + 2);
    sprintf(res, "%s/%s", a, b);
    return res;
}

/** Subscribe to channels. */
void init_channels(int *in, int *out) {
    char uuid_buf[37];
    module_get_uuid(uuid_buf);

    char *ch_in = path_join("benchmark/in", uuid_buf);
    *in = ch_open(ch_in, CH_RDONLY, 0);
    free(ch_in);

    char *ch_out = path_join("benchmark/out", uuid_buf);
    *out = ch_open(ch_out, CH_WRONLY, 0);
    free(ch_out);
}

/** Generate random output buffer. */
char *generate_output_data(int size) {
    char *buf = malloc(size);
    for (int i = 0; i < size / 4; i++) {
        ((int *) buf)[i] = rand();
    }
    return buf;
}

/** Loop function; should be called into by main */
int loop(int argc, char **argv, int (*func)(int, char **)) {
    dp_t dp;
    dp_init(&dp);

    int data_in, data_out;
    init_channels(&data_in, &data_out);

    int poll_chs[] = {data_in};
    while (1) {
        int res = ch_poll(poll_chs, 1, 5000);
        if (res > 0) {
            // Read to exhaustion
            char read_buf[1024];
            int bytes_read = 1;
            while (bytes_read > 0) {
                bytes_read = ch_read_msg(data_in, read_buf, 1024);
            }
            // Super janky exit condition
            if (!strncmp(read_buf, "exit", 4)) { break; }

            func(argc, argv);

            // Write random data
            int size = dp_draw(&dp);
            char *buf = generate_output_data(size);
            ch_write_msg(data_out, buf, size);
            free(buf);
        }
    }
    return 0;
}

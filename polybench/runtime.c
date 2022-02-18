/**
 * @file runtime.c
 * @brief Replacement main file with runtime API hooks.
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "api.h"

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

#define MAX_CLUSTERS 16

/** Generate output data. */
int tables[MAX_CLUSTERS];
int means[MAX_CLUSTERS];
int num_clusters;
int total;

/** Draw from geometric */
int sample_geometric() {
    double x = (double) rand() / (double) RAND_MAX;

    return ceil(log(x) / log(0.999));
}

/** Initialize dirichlet process */
void dp_init() {
    for (int i = 0; i < MAX_CLUSTERS; i++) { tables[i] = 0; }
    total = 1;   // total starts at alpha
    num_clusters = 0;
}

/** Draw from dirichlet process */
int dp_draw() {
    double x = (double) rand() / (double) RAND_MAX;

    double acc = 1 / (double) total;
    int i;

    // Draw new
    if (x < acc) {
        means[num_clusters] = sample_geometric();
        num_clusters += 1;
        i = num_clusters - 1;
    // Sample from existing table
    } else {
        for (i = 0; i < MAX_CLUSTERS; i++) {
            acc += (double) tables[i] / (double) total;
            if (acc > x) { break; }
        }
    }

    tables[i] += 1;
    total += 1;
    return means[i];
}


char *buf;
int size;

void generate_output_data() {
    size = dp_draw();
    for (int i = 0; i < size / 4; i++) {
        ((int *) buf)[i] = rand();
    }
}

int loop(int argc, char **argv, int (*func)(int, char **)) {

    int data_in, data_out;
    init_channels(&data_in, &data_out);

    int poll_chs[] = {data_in};
    while (1) {
        int res = ch_poll(poll_chs, 1, 10000);
        if (res > 0) {
            char read_buf[8192];
            ch_read_msg(data_in, read_buf, 8192);
            func(argc, argv);
            generate_output_data();
            ch_write_msg(data_out, buf, size);
        } else {
            break;
        }
    }

    return 0;
}

/**
 * @file passive.c
 * @brief Passive profiling with data inputs.
 */

#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "wrapper.h"

#define BUF_LEN 1000

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

/** Loop wrapper around benchmark main
*   Called by the main function for a given benchmark suite
*   Funnels appropriate inputs to benchmarks argc/argv
*/
int main(int argc, char **argv) {

    // Manual profiling mode
    period_set_flags(1);

    int data_in, data_out;
    init_channels(&data_in, &data_out);

    // Module initialization always starts a period
    period_yield();

    char buf[1];
    int i = 0;
    while(1) {
        if(ch_read_msg(data_in, buf, 1)) { break; }
        period_start();
        benchmark_main(argc, argv);
        period_yield();
        i += 1;
    }
    printf("Exiting after %d loops\n", i);
    ch_write_msg(data_out, "done", 4);
    return 0;
}

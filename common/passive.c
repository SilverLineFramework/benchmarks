/**
 * @file active.c
 * @brief Main loop for passive profiling.
 */

#include <stdlib.h>
#include <string.h>
#include "api.h"

/** Join topic path. */
static char *path_join(char *a, char *b) {
    char *res = malloc(strlen(a) + strlen(b) + 2);
    sprintf(res, "%s/%s", a, b);
    return res;
}

/** Loop function; should be called into by main */
int loop(int argc, char **argv, int (*func)(int, char **)) {

    // Manual profiling mode
    period_set_flags(1);

    char uuid_buf[37];
    module_get_uuid(uuid_buf);
    char *ch_ctrl = path_join("benchmark/in", uuid_buf);
    int ctrl = ch_open(ch_ctrl, CH_RDONLY, 0);
    free(ch_ctrl);

    // Module initialization always starts a period
    period_end();

    char buf[1];
    while (1) {
        if(ch_read_msg(ctrl, buf, 1)) { break; }
        period_start();
        func(argc, argv);
        period_end();
    }
    return 0;
}

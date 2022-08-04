/**
 * @file wrapper.c
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
static void init_channels(int *exit_in, int *in, int *out) {
    char uuid_buf[37];
    module_get_uuid(uuid_buf);

    char *ch_in;
    // Input data
    ch_in = path_join("in", "1");
    *in = ch_open(ch_in, CH_RDONLY, 0);
    free(ch_in);

    // Exit condition
    ch_in = path_join("benchmark/exit", "all");
    *exit_in = ch_open(ch_in, CH_RDONLY, 0);
    free(ch_in);

    char *ch_out = path_join("benchmark/out", uuid_buf);
    *out = ch_open(ch_out, CH_WRONLY, 0);
    free(ch_out);
}


static void free_args(int argc, char ***argv) {
  for (int i = 0; i < argc; i++) {
    free((*argv)[i]);
  }
  free(*argv);
  *argv = NULL;
}

/** Parse argv from the input data stream 
*   Assume comma-separated inputs for now 
*   Return argc */
static int parse_args(char*** argv, int *repeat, char *data) {
  int argc;
  const char d[2] = ",";

  char *token = strtok(data, d);
  if (token == NULL) {
    printf("Null data-in\n");
    goto fail;
  } 
  else {
    *repeat = atoi(token);
    if (!(token = strtok(NULL, d))) { goto fail; }
    argc = atoi(token);
    *argv = (char **) malloc(argc * sizeof(char*));
    int i = 0;
    /* Get argvs */
    while ((token = strtok(NULL, d))) {
      (*argv)[i++] = strdup(token);
    }
    if (i != argc) {
      printf("Error: Inconsistent argc (%d) and parsed count (%d)\n", argc, i);
      free_args(i, argv);
      goto fail;
    }
  }

  printf("Repeat: %d | Bench argv[1]: %s\n", *repeat, (*argv)[1]);

  return argc;

fail:
  *repeat = 0;
  *argv = NULL;
  argc = 0;
  return argc;
}


/** Loop wrapper around benchmark main
*   Called by the main function for a given benchmark suite
*   Funnels appropriate inputs to benchmarks argc/argv
*/
int main(int argc, char **argv) {

    // Manual profiling mode
    period_set_flags(1);

    int exit_fd, data_in_fd, data_out_fd;
    init_channels(&exit_fd, &data_in_fd, &data_out_fd);

    // Module initialization always starts a period
    period_yield();

    char exit[1];
    char *buf = (char*) malloc(BUF_LEN);
    int poll_fds[] = {data_in_fd};

    int bench_argc;
    char **bench_argv;
    int repeat = 1;

    int i = 0;
    while(1) {
        if(ch_read_msg(exit_fd, exit, 1)) { break; }
        int res = ch_poll(poll_fds, 1, 5000);
        if (res != 0) {
          if (res < 0) {
            printf("Exiting due to error.\n");
            break;
          }
          ch_read_msg(data_in_fd, buf, BUF_LEN);
          bench_argc = parse_args(&bench_argv, &repeat, buf);

          while (repeat > 0) {
            period_start();
            benchmark_main(bench_argc, bench_argv);
            period_yield();
            repeat--;
            i += 1;
          }
          free_args(bench_argc, &bench_argv);
        } 
        else {
          // Default implemented provided by approriate benchmark suite
          printf("No args\n");
          // bench_argc = get_default_args(&bench_argv);
        }
    }
    printf("Exiting after %d loops\n", i);
    ch_write_msg(data_out_fd, "done", 4);
    return 0;
}

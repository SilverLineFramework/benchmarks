/**
 * @file active.c
 * @brief Main loop for passive profiling.
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/api.h"
#include "../common/passive.h"
#include "wrapper.h"

/** Loop function; should be called into by main */
int main(int argc, char* argv[]) {

    // Manual profiling mode
    period_set_flags(1);

    // Module initialization always starts a period
    period_yield();

    DIR *d = argc > 1 ? opendir(argv[1]) : NULL;
    struct dirent *dir;
    char filepath[1000];
    
    char **bench_argv;
    // Only argv[1] matters for now
    bench_argv = (char**) malloc(argc * sizeof(char*));

    int i = 0;
    if (d) {
      // Read files from directory
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
          filepath[0] = 0;
          strcat(filepath, argv[1]);
          strcat(filepath, "/");
          strcat(filepath, dir->d_name);

          strcpy(bench_argv[1], filepath);
          bench_argv[1] = strdup(filepath);

          bench_argv[2][0] = '\0';
          printf("Bench argv[1]: %s\n", bench_argv[1]);

          // Invoke function for period
          period_start();
          benchmark_main(argc, bench_argv);
          period_yield();
          i += 1;
        }
      }
    }
    else {
      printf("Could not open directory\n");
    }
    printf("Exiting after %d loops\n", i);
    return 0;
}

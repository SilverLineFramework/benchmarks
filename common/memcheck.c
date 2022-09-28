/**
 * @file memcheck.c
 * @brief Perform checking of memory results
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "api.h"
#include "wrapper.h"

#define BUF_LEN 1000
#define N 2

/** Loop wrapper around benchmark main
*   Called by the main function for a given benchmark suite
*   Funnels appropriate inputs to benchmarks argc/argv
*/
int main(int argc, char **argv) {

    char ch_in[] = "memcheck/vote";
    char ch_out[] = "memcheck/result";
    int data_in = ch_open(ch_in, CH_RDONLY, 0);
    int data_out = ch_open(ch_out, CH_WRONLY, 0);

    int *checksums = (int*) malloc(N * sizeof(int));

    while(1) {
      // Get checksums
      for (int i = 0; i < N; i++) {
        int poll = 0;
        while (poll <= 0) {  
          poll = ch_poll(&data_in, 1, 2000); 
          printf("Wait voting\n");
        }
        printf("Out!\n");
        ch_read_msg(data_in, (char*) &checksums[i], 4);
      }
      bool result = false;
      for (int i = 0; i < (N-1); i++) {
        result |= (checksums[i] != checksums[i+1]);
      }
      ch_write_msg(data_out, (char*) result, 1);
    }
    return 0;
}

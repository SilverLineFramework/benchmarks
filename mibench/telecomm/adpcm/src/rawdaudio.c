/* testd - Test adpcm decoder */

#include "adpcm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../../../../common/runtime.h"

struct adpcm_state state;

#define NSAMPLES 1000

char	abuf[NSAMPLES/2];
short	sbuf[NSAMPLES];

int benchmark_main(int argc, char *argv[]) {
    int n;

    #ifdef LARGE
    char source[80] = "data/mibench/telecomm/large.adpcm";
    #else
    char source[80] = "data/mibench/telecomm/small.adpcm";
    #endif

    int input = open(source, O_RDONLY);

    while(1) {
        n = read(input, abuf, NSAMPLES/2);
        if ( n < 0 ) {
            perror("input file");
        }
        if ( n == 0 ) break;
        adpcm_decoder(abuf, sbuf, n*2, &state);
    }

    return 0;
}

int main(int argc, char *argv[]) {
   return loop(argc, argv, &benchmark_main);
}

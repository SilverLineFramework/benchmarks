
/* testc - Test adpcm coder */

#include "adpcm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct adpcm_state state;

#define NSAMPLES 1000

char	abuf[NSAMPLES/2];
short	sbuf[NSAMPLES];

int main(int argc, char *argv[]) {
    int n;

    #ifdef LARGE
    char source[80] = "data/mibench/adpcm_large.pcm";
    #else
    char source[80] = "data/mibench/adpcm_small.pcm";
    #endif

    int input = open(source, O_RDONLY);

    while(1) {
	    n = read(input, sbuf, NSAMPLES*2);
        if ( n < 0 ) {
            perror("input file");
        }
        if ( n == 0 ) break;
        adpcm_coder(sbuf, abuf, n/2, &state);
    }

    close(input);

    return 0;
}


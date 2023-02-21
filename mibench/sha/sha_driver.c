/* NIST Secure Hash Algorithm */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sha.h"

int main(int argc, char **argv)
{

    #ifdef LARGE
    FILE *fin = fopen("data/mibench/sha_large.asc", "r");
    #else
    FILE *fin = fopen("data/mibench/sha_small.asc", "r");
    #endif

    SHA_INFO sha_info;

	sha_stream(&sha_info, fin);

    fclose(fin);

    return(0);
}


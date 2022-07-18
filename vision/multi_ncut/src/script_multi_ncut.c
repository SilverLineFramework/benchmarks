/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "segment.h"
#include "../../../common/runtime.h"

int benchmark_main(int argc, char* argv[])
{
    float sigma = 0.6;
    float k = 4;
    int min_size = 10;
    int num_ccs[1] = {0};
    I2D* im;
    I2D* seg;
    int ret;

    #if SIZE == 0
        char im1[100] = "data/vision/multi_ncut/sqcif/1.bmp";
    #elif SIZE == 1
        char im1[100] = "data/vision/multi_ncut/qcif/1.bmp";
    #else
        char im1[100] = "data/vision/multi_ncut/cif/1.bmp";
    #endif
    im = readImage(im1);

    seg = segment_image(im, sigma, k, min_size, num_ccs);

    iFreeHandle(im); 
    iFreeHandle(seg);
    
    return 0;
}

int main(int argc, char *argv[]) {
   return loop(argc, argv, &benchmark_main);
}

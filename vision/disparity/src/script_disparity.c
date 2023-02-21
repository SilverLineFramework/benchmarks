/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"

int main(int argc, char* argv[])
{
    int rows = 32;
    int cols = 32;
    I2D *imleft, *imright, *retDisparity;
    
    int i, j;
    char im1[100], im2[100], timFile[100];
    int WIN_SZ=8, SHIFT=64;

    #if SIZE == 0
        char base[100] = "data/vision/disparity/sqcif";
    #elif SIZE == 1
        char base[100] = "data/vision/disparity/qcif";
    #else /* SIZE == 2 */
        char base[100] = "data/vision/disparity/cif";
    #endif


    sprintf(im1, "%s/1.bmp", base);
    sprintf(im2, "%s/2.bmp", base);
    
    imleft = readImage(im1);
    imright = readImage(im2);

    rows = imleft->height;
    cols = imleft->width;

#ifdef test
    WIN_SZ = 2;
    SHIFT = 1;
#endif
#ifdef sim_fast
    WIN_SZ = 4;
    SHIFT = 4;
#endif
#ifdef sim
    WIN_SZ = 4;
    SHIFT = 8;
#endif

    retDisparity = getDisparity(imleft, imright, WIN_SZ, SHIFT);
    
    iFreeHandle(imleft);
    iFreeHandle(imright);
    iFreeHandle(retDisparity);
    return 0;
}


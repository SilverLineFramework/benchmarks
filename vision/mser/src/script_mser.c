/********************************
Author: Sravanthi Kota Venkata
********************************/

#include "mser.h"

#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

int benchmark_main(int argc, char* argv[])
{

    int which_image;
    int i, j, k;
    I2D *idx;
    I2D *I;
    I2D *It;
    int rows=196, cols=98;
    int minVal = 1000;
    int maxVal = -1000;
    int lev = 10;
    
    #if SIZE == 0
    char im1[100] = "data/vision/mser/sqcif/1.bmp";
    #elif SIZE == 1
    char im1[100] = "data/vision/mser/qcif/1.bmp";
    #else /* SIZE == 2*/
    char im1[100] = "data/vision/mser/cif/1.bmp";
    #endif

    I = readImage(im1);
    rows = I->height;
    cols = I->width;

    It = readImage(im1);

    k = 0;
    for(i=0; i<cols; i++)
    {
        for(j=0; j<rows; j++)
        {
            asubsref(It,k++) = subsref(I,j,i);
        }
    }
    
    idx = mser(It, 2);

#ifdef CHECK   
    /** Self checking - use expected.txt from data directory  **/
    {
        int tol, ret=0;
        tol = 1;
#ifdef GENERATE_OUTPUT
        writeMatrix(idx, argv[1]);
#endif
        ret = selfCheck(idx, argv[1], tol);
        if (ret == -1)
            printf("Error in MSER\n");
    }
    /** Self checking done **/
#endif    
   
    iFreeHandle(idx);
    iFreeHandle(I);
    iFreeHandle(It);
    
    return 0;
}


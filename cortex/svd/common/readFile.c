/********************************
Author: Sravanthi Kota Venkata
********************************/
#include <stdlib.h>
#include "sdvbs_common.h"

F2D* readFile()
{
    F2D *fill;
    float temp;
    int rows = 70, cols = 70;
    int i, j;

    fill = fSetArray(rows, cols, 0);

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            subsref(fill,i,j) = (float) rand() / (float) RAND_MAX;
        }
    }

    return fill;
}

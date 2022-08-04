/********************************
Author: Sravanthi Kota Venkata
********************************/

#include "texture.h"

int WIDTHin,HEIGHTin;
F2D *target, *result;
int WIDTH,HEIGHT;
int localx, localy,targetin=0;
int *atlas;
int *xloopin, *yloopin;
int *xloopout, *yloopout;

int  benchmark_main(int argc, char **argv)
{
    params* data;
    I2D *im;
    F2D* image;
    unsigned int *start, *end, *elapsed;

    data = malloc(sizeof(params));
    im = parse_flags(argc, argv);
    image = fiDeepCopy(im);
    init_params(data);

    create_texture(image, data);
    
    iFreeHandle(im);
    fFreeHandle(image);
    free(data);

    fFreeHandle(target);
    fFreeHandle(result);
    free(atlas);
//    free(xloopout);
//    free(yloopout);
    
	return 0;
}

int main(int argc, char *argv[]) {
   return loop(argc, argv, &benchmark_main);
}

I2D* parse_flags(int argc, char ** argv)
{
    int i, tsx,tsy;
    I2D* image;

    #if SIZE == 0
    char fileNm[256] = "data/vision/texture/sqcif/1.bmp";
    #elif SIZE == 1
    char fileNm[256] = "data/vision/texture/qcif/1.bmp";
    #else
    char fileNm[256] = "data/vision/texture/cif/1.bmp";
    #endif

    image = readImage(fileNm);
    WIDTHin = image->width;
    HEIGHTin = image->height;

    localx = 3;
    localy = 3;

#ifdef test
    WIDTH = WIDTHin*2;
    HEIGHT = HEIGHTin*2;
    localx = 2;
    localy = 2;
#endif
#ifdef sim_fast
    WIDTH = WIDTHin*2;
    HEIGHT = HEIGHTin*2;
    localx = 3;
    localy = 3;
#endif
#ifdef sim
    WIDTH = WIDTHin*3;
    HEIGHT = HEIGHTin*3;
    localx = 2;
    localy = 2;
#endif
#ifdef sqcif
    WIDTH = WIDTHin*6;
    HEIGHT = HEIGHTin*6;
    localx = 2;
    localy = 2;
#endif
#ifdef qcif
    WIDTH = WIDTHin*10;
    HEIGHT = HEIGHTin*10;
    localx = 2;
    localy = 2;
#endif
#ifdef cif
    WIDTH = WIDTHin*10;
    HEIGHT = HEIGHTin*10;
    localx = 3;
    localy = 3;
#endif
#ifdef vga
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 3;
    localy = 3;
#endif
#ifdef fullhd
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 15;
    localy = 15;
#endif
#ifdef wuxga
    WIDTH = WIDTHin*20;
    HEIGHT = HEIGHTin*20;
    localx = 5;
    localy = 5;
#endif

    result = fMallocHandle(1,HEIGHT*WIDTH);
    target = fMallocHandle(1, WIDTH*HEIGHT);
 
    atlas = malloc(2*WIDTH*HEIGHT*sizeof(int));
    xloopout = malloc(2*WIDTH*sizeof(int));
    yloopout = malloc(2*HEIGHT*sizeof(int));
    
    for(i=-WIDTH/2;i<WIDTH+WIDTH/2;i++)
    {
        arrayref(xloopout,i+WIDTH/2) = (WIDTH+i)%WIDTH;
    }
    for(i=-HEIGHT/2;i<HEIGHT+HEIGHT/2;i++)
    {
        arrayref(yloopout,i+HEIGHT/2) = (HEIGHT+i)%HEIGHT;
    }
    xloopout += WIDTH/2; yloopout += HEIGHT/2;

    if (result == NULL)
    {
        printf("Can't allocate %dx%d image. Exiting.\n",WIDTH,HEIGHT);
        exit(1);
    }

    return image;
}

void init_params(params *data)
{
    int i,j;
    data->localx = localx; data->localy = localy;
    data->widthin = WIDTHin; data->widthout = WIDTH;
    data->heightin = HEIGHTin; data->heightout = HEIGHT;


    if(!targetin)
    {
        for(i=0;i<data->heightout;i++)
        {
            for(j=0;j<data->widthout;j++)
            {
                asubsref(target,a(j,i,data->widthout)+R) = 1.0;
//                asubsref(target,a(j,i,data->widthout)+G) = 1.0;
//                asubsref(target,a(j,i,data->widthout)+B) = 1.0;
            }
        }
    }
 
    for(i=0;i<data->heightout;i++)
    {
        for(j=0;j<data->widthout;j++)
        {
            asubsref(result,a(j,i,data->widthout)+R)  = 1.0;
//            asubsref(result,a(j,i,data->widthout)+G)  = 1.0;
//            asubsref(result,a(j,i,data->widthout)+B)  = 1.0;
        }
    }
}

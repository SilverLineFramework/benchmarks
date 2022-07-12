#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../../common/runtime.h"

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

struct my3DVertexStruct {
  int x, y, z;
  double distance;
};

int compare(const void *elem1, const void *elem2)
{
  /* D = [(x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2]^(1/2) */
  /* sort based on distances from the origin... */

  double distance1, distance2;

  distance1 = (*((struct my3DVertexStruct *)elem1)).distance;
  distance2 = (*((struct my3DVertexStruct *)elem2)).distance;

  return (distance1 > distance2) ? 1 : ((distance1 == distance2) ? 0 : -1);
}


int
benchmark_main(int argc, char *argv[]) {
  struct my3DVertexStruct *array = malloc(MAXARRAY * sizeof(struct my3DVertexStruct));
  FILE *fp;
  int i,count=0;
  int x, y, z;

    fp = fopen("data/mibench/automotive/input_large.dat","r");

    while((fscanf(fp, "%d", &x) == 1) && (fscanf(fp, "%d", &y) == 1) && (fscanf(fp, "%d", &z) == 1) &&  (count < MAXARRAY)) {
	 array[count].x = x;
	 array[count].y = y;
	 array[count].z = z;
	 array[count].distance = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	 count++;
    }

  qsort(array,count,sizeof(struct my3DVertexStruct),compare);
  free(array);
    fclose(fp);

  return 0;
}

int main(int argc, char *argv[]) {
   return loop(argc, argv, &benchmark_main);
}

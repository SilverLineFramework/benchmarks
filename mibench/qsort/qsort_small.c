#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

int compare(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((char *) elem1, (char *) elem2);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}


int main(int argc, char *argv[]) {
  char *array = malloc(MAXARRAY * 32 * sizeof(char));

  FILE *fp;
  int i,count=0;
  
    fp = fopen("data/mibench/qsort_small.dat","r");
    while((fscanf(fp, "%s", &array[32 * count]) == 1) && (count < MAXARRAY)) {
	 count++;
    }
    qsort(array,count, 32,compare);
  
  free(array);

    fclose(fp);
  return 0;
}

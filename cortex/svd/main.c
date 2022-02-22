/*
 * SVD for latent semantic analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/sdvbs_common.h"

#include "../../common/runtime.h"


#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

/* Functions declarations */
int svd(F2D *, F2D *, F2D *);
void sortSVDResult(F2D *, F2D *, F2D *);
F2D* readFile();

void printMatrix(F2D *m)
{
	int i = 0, j = 0;
	for (i = 0; i < m->height; i++)
	{
		for (j = 0; j < m->width; j++)
			printf("%6.2f ", subsref(m, i, j));

		printf("\n");
	}
}

void printFloatSubMatrix(F2D *m, int size)
{
	int i = 0, j = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%6.2f ", subsref(m, i, j));

		printf("\n");
	}
}

void printIntSubMatrix(I2D *m, int size)
{
	int i = 0, j = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%3d ", subsref(m, i, j));

		printf("\n");
	}
}


int benchmark_main(int argc, char **argv)
{
	// Initialize u,s,v
	F2D * u = readFile();
	F2D * s = fSetArray(1, u->width, 0);
	F2D * v = fSetArray(u->width, u->width, 0);

	svd(u, s, v);
	sortSVDResult(u, s, v);

	// Multiply singular values to U and V
	int i, j;
	for (i = 0; i < s->width; i++)
	{
		for (j = 0; j < u->height; j++)
			subsref(u, j, i) = subsref(u, j, i) * subsref(s, 0, i);
		for (j = 0; j < v->height; j++)
					subsref(v, j, i) = subsref(v, j, i) * subsref(s, 0, i);
	}

	free(u);
	free(s);
	free(v);

  return 0;
}


int main(int argc, char **argv) {
  return loop(argc, argv, &benchmark_main);
}

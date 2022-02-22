#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/runtime.h"

int *k_means(double **data, int n, int m, int k, double t, double **centroids);

void get_data(int n, int m, double **data)
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++) {
            data[i][j] = (double) rand() / (double) RAND_MAX;
        }
	}
}

int benchmark_main(int argc, char **argv)
{
    int n = 1000, m = 10, k = 3;
    int i, j;

	//alloc data
	double **data = calloc(n, sizeof(double *));
	for(i=0; i<n; i++)
	{
        data[i] = calloc(m, sizeof(double));
	}

	get_data(n, m, data);

	int *c = k_means(data, n, m, k, 1e-8, 0);

	//free memory
	if(!c) free(c);
	for(i=0; i<n; i++) {
		free(data[i]);
	}
	if(!data) free(data);

	return 0;
}

int main(int argc, char **argv) {
  return loop(argc, argv, &benchmark_main);
}

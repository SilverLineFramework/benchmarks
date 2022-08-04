#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

int *k_means(double **data, int n, int m, int k, double t, double **centroids);
void eigen(double *a,double *ev,int n);

double SIGMA = 0.1;
double DIV_FACTOR = 500;

double distance(double *p1, double *p2, int m)
{
	int i;
	double dist = 0;
	//find euclidean distance
	for(i=0; i<m; i++)
		dist += (p2[i] - p1[i])*(p2[i] - p1[i]);

	return dist;
}

void adjacency(double **data, int n, int m, double *A)
{
	int i=0, j=0;
	for(i=0; i<n; i++) {
		for(j=i;j<n;j++){
			if(i==j) A[(n*i+j)] = 0;
			else
				A[(n*i+j)] = -exp(-distance(data[i], data[j], m)); // Gauss Kernel
			A[(n*j+i)] = A[(n*i+j)];
		}
	}
}


void get_k_data(double *A, double *ev, int n, int k, double **k_data)
{
	int i, j, l;
	int index = 0;
	double min = DBL_MAX;

	int *check = calloc(n, sizeof(int));

	for(i=0; i<k; i++)
	{
		min = DBL_MAX;
		for(j=0; j<n; j++)
		{
			if(check[j]) continue;
			else {
				if(ev[j]<min) {
					min = ev[j];
					index = j;
				}
			}
		}
		check[index] = 1;
		for(l=0;l<n;l++) 
			k_data[l][i] = A[l*n+index];
	}
}

void get_data(const char* data_file, int n, int m, double **data)
{
	int i, j;
	FILE *fp = fopen(data_file,"r");

	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
			fscanf(fp, "%lf", &data[i][j]);
	}
    fclose(fp);
}

void USAGE()
{
	printf("USAGE: \n");
	printf("./spc data_file n m k SIGMA DIV_FACTOR\n");
	printf("data_file = dataset text file in the format specified below \n");
	printf("n = total number of data points \n");
	printf("m = dimensionality of data \n");
	printf("k = number of desired clusters\n");
	printf("SIGMA = Gauss Kernel Sigma (typically set it to 0.707)\n");
	printf("DIV_FACTOR = Factor to avoid overflowing. Might require for Data-points \n");
	printf("very far away or with very high abs value (typically set it to 1) \n");
	printf("\n");
	printf("**** data_file format ****\n");
	printf("data_file should be in the form nxm\n");
	printf("n = number of rows (total number of data points)\n");
	printf("m = number of columns (data point dimensions)\n");
}

int benchmark_main(int argc, char *argv[])
{
	int i, j;

    #if SIZE == 0
        char data_file[1000] = "data/cortex/spectral/R15";
        // int n = 600, m = 2, k = 15;
        int n = 100, m = 2, k = 5;
        SIGMA = 0.707;
        DIV_FACTOR = 1;
    #elif SIZE == 1
        char data_file[1000] = "data/cortex/spectral/Aggregation";
        // int n = 788, m = 2, k = 7;
        int n = 150, m = 2, k = 7;
        SIGMA = 0.707;
        DIV_FACTOR = 1;
    #else /* SIZE == 2 */
        char data_file[1000] = "data/cortex/spectral/D31";
        // int n = 1600, m = 2, k = 16;
        int n = 200, m = 2, k = 10;
        SIGMA = 0.707;
        DIV_FACTOR = 1;
    #endif

	//alloc data
	double **data = calloc(n, sizeof(double *));
	for(i=0; i<n; i++)
	{
		data[i] = calloc(m, sizeof(double));
	}

	//alloc Adjacency/Laplacian Matrix
	double *A  = calloc(n*n, sizeof(double));
	if(!A) { 
		printf("Data Set too large. Could not allocate memory \n");
		return 1;
	}

	//alloc degree matrix
	double *D = calloc(n, sizeof(double));

	//eigen vectors
	double *ev = calloc(n, sizeof(double));

	//k_data
	double **k_data = calloc(n, sizeof(double *));
	for(i=0; i<n; i++)
	{
		k_data[i] = calloc(k, sizeof(double));
	}

	//get data
	get_data(data_file, n, m, data);

	//find adjacency matrix
	adjacency(data, n, m, A);

	//Calculate Laplacian matrix (degree - adjacency)
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			D[i] += -A[(n*i+j)];
		A[(n*i+i)] = D[i];
	}

	//Second level Laplacian
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			A[(n*i+j)] = (A[(n*i+j)]/sqrt(D[i]))/sqrt(D[j]);
	}

	eigen(A, ev, n);

	//find eigen values that are close to zero and corresponding eigen vectors.
	get_k_data(A, ev, n, k, k_data);

	//peform k-means on each of these eigen vectors
	int *c = k_means(k_data, n, k, k, 1e-8, 0);

   /****
   ** housekeeping */
	if(!c) free(c);
	if(!ev) free(ev);
	if(!D) free(D);
	if(!A) free(A);

	for(i=0; i<n; i++) {
		free(k_data[i]);
		free(data[i]);
	}
	if(!k_data) free(k_data);
	if(!data) free(data);

	return 0;
}


#include <stdio.h>
#include <stdlib.h>

#define DOUBLE_MAX 1e20

void OptimalBST(double **e, double **w, int **root, double *p, double *q, int size)
{
	int i = 0, j = 0, len = 0, r = 0;
	double t = 0.0;
	for (i = 0; i <= size; ++i)
	{
		e[i][i] = q[i];
		w[i][i] = q[i];
	}
	for (len = 1; len <= size; ++len)
	{
		for (i = 0; i <= size - len; ++i)
		{
			j = i + len;
			e[i][j] = DOUBLE_MAX;
			w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
			for (r = i; r <= j - 1; ++r)
			{
				t = e[i][r] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j - 1] = r;
				}
			}
		}
	}
}

void ConstructOptimalBST(int **root, int size)
{
	
}

void testOptimalBinarySearchTrees()
{
	int size = 5;
	double p[] = { 0.15, 0.10, 0.05, 0.10, 0.20 };
	double q[] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
	//int size = 7;
	//double p[] = {0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
	//double q[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
	int i;
	double **e, **w;
	int **root;
	e = (double **)malloc((size + 1) * sizeof(double *));
	w = (double **)malloc((size + 1) * sizeof(double *));
	for (i = 0; i < size + 1; ++i)
	{
		e[i] = (double *)malloc((size + 1) * sizeof(double));
		w[i] = (double *)malloc((size + 1) * sizeof(double));
	}
	root = (int **)malloc(size * sizeof(int *));
	for (i = 0; i < size; ++i)
		root[i] = (int *)malloc(size * sizeof(int));

	OptimalBST(e, w, root, p, q, size);
	printf("Minimum cost : %f\n", e[0][size]);


	for (i = 0; i < size + 1; ++i)
	{
		free(e[i]);
		free(w[i]);
	}
	free(e);
	free(w);
	for (i = 0; i < size; ++i)
		free(root[i]);
	free(root);
}
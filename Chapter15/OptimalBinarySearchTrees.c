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

void ConstructOptimalBST(int **root, int size, int i, int j)
{
	if (i == 0 && j == size - 1)
		printf("k%d is the root\n", root[i][j] + 1);
	if (i + 1 < j)
	{
		if (root[i][j] >= 1)
		{
			printf("k%d is the left child of k%d\n", root[i][root[i][j] - 1] + 1, root[i][j] + 1);
			ConstructOptimalBST(root, size, i, root[i][j] - 1);
		}
		else
			printf("d%d is the left child of k%d\n", 0, root[i][j] + 1);
		if (root[i][j] < size - 1)
		{
			printf("k%d is the right child of k%d\n", root[root[i][j] + 1][j] + 1, root[i][j] + 1);
			ConstructOptimalBST(root, size, root[i][j] + 1, j);
		}
		else
			printf("d%d is the right child of k%d\n", size, root[i][j] + 1);
	}
	else if (i + 1 == j)
	{
		if (root[i][j] == i)
		{
			printf("d%d is the left child of k%d\n", i, i + 1);
			printf("k%d is the right child of k%d\n", i + 2, i + 1);
			ConstructOptimalBST(root, size, j, j);
		}
		else if (root[i][j] == j)
		{
			printf("k%d is the left child of k%d\n", i + 1, i + 2);
			ConstructOptimalBST(root, size, i, i);
			printf("d%d is the right child of k%d\n", i + 2, i + 2);
		}
	}
	else if (i == j)
	{
		printf("d%d is the left child of k%d\n", i, i + 1);
		printf("d%d is the right child of k%d\n", i + 1, i + 1);
	}
}

void testOptimalBinarySearchTrees()
{
	//int size = 5;
	//double p[] = { 0.15, 0.10, 0.05, 0.10, 0.20 };
	//double q[] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
	int size = 7;
	double p[] = { 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14 };
	double q[] = { 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05 };
	int i, j;
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
	ConstructOptimalBST(root, size, 0, size - 1);
	printf("table e :\n");
	for (i = 0; i < size + 1; ++i)
	{
		for (j = size; j >= i; --j)
			printf("%f  ", e[i][j]);
		printf("\n");
	}
	printf("table w :\n");
	for (i = 0; i < size + 1; ++i)
	{
		for (j = size; j >= i; --j)
			printf("%f  ", w[i][j]);
		printf("\n");
	}	printf("table root :\n");
	for (i = 0; i < size; ++i)
	{
		for (j = size - 1; j >= i; --j)
			printf("%d  ", root[i][j] + 1);
		printf("\n");
	}

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
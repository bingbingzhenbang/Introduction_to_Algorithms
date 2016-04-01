#include <stdio.h>
#include <stdlib.h>

void MatrixChainOrder(int **m, int **s, int size, int *p)
{
	int i = 0, j = 0, k = 0, length = 0, q = 0;
	for (i = 0; i < size; ++i)
		m[i][i] = 0;
	for (length = 2; length <= size; ++length)
	{
		for (i = 0; i <= size - length; ++i)
		{
			j = i + length - 1;
			m[i][j] = INT_MAX;
			for (k = i; k <= j - 1; ++k)
			{
				q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if (q <= m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void PrintOptimalParens(int **s, int i, int j)
{
	if (i == j)
		printf("A%d", i + 1);
	else
	{
		printf("(");
		PrintOptimalParens(s, i, s[i][j]);
		PrintOptimalParens(s, s[i][j] + 1, j);
		printf(")");
	}
}

void testMatrixChainMultiplication()
{
	int i = 0, size = 0;
	int *p;
	int **m, **s;
	size = 6;
	int arr[] = {30, 35, 15, 5, 10, 20, 25};
	p = arr;
	//FILE *fp = fopen("matrix_chain_multiplication_input", "r");
	//if (fp == NULL)
	//{
	//	printf("cannnot open file!\n");
	//	return;
	//}
	//fscanf(fp, "%d", &size);
	//p = (int*)malloc((size + 1) * sizeof(int));
	//for (i = 0; i < size + 1; ++i)
	//	fscanf(fp, "%d", p + i);
	//fclose(fp);
	m = (int **)malloc(size * sizeof(int*));
	s = (int **)malloc(size * sizeof(int*));
	for (i = 0; i < size; ++i)
	{
		m[i] = (int *)malloc(size * sizeof(int));
		s[i] = (int *)malloc(size * sizeof(int));
	}
	MatrixChainOrder(m, s, size, p);
	printf("Minimum number of scalar multiplications : %d\n", m[0][size - 1]);
	printf("Optimal parenthesization :\n");
	PrintOptimalParens(s, 0, size - 1);
	printf("\n");

	for (i = 0; i < size; ++i)
	{
		free(m[i]);
		free(s[i]);
	}
	free(m);
	free(s);
	//free(p);
}
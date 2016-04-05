#include <stdio.h>
#include <stdlib.h>

enum TableDirectionINT
{
	Enum_Null,
	Enum_Top,
	Enum_Left,
	Enum_TopLeft
};

int compareINT(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void LCSLengthINT(int **c, int **b, int m, int n, int *X, int *Y)
{
	int i = 0, j = 0;
	for (i = 0; i < m + 1; ++i)
		c[i][0] = 0;
	for (j = 0; j < n + 1; ++j)
		c[0][j] = 0;

	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if (X[i] == Y[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
				b[i][j] = Enum_TopLeft;
			}
			else
			{
				if (c[i][j + 1] >= c[i + 1][j])
				{
					c[i + 1][j + 1] = c[i][j + 1];
					b[i][j] = Enum_Top;
				}
				else
				{
					c[i + 1][j + 1] = c[i + 1][j];
					b[i][j] = Enum_Left;
				}
			}
		}
	}
}

void PrintLCSINT(int **b, int *X, int i, int j)
{
	if (i == -1 || j == -1)
		return;
	else
	{
		if (b[i][j] == Enum_TopLeft)
		{
			PrintLCSINT(b, X, i - 1, j - 1);
			printf("%d ", X[i]);
		}
		else if (b[i][j] == Enum_Top)
			PrintLCSINT(b, X, i - 1, j);
		else if (b[i][j] == Enum_Left)
			PrintLCSINT(b, X, i, j - 1);
	}
}

int LCSLengthLeastMemoryINT(int m, int n, int *X, int *Y)
{
	int i = 0, j = 0, p = 0, q = 0, rt = 0;
	int *c = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; ++i)
		c[i] = 0;
	for (i = 0; i < m; ++i)
	{
		p = c[0];
		if (X[i] == Y[0])
			c[0] = 1;
		for (j = 1; j < n; ++j)
		{
			q = p;
			p = c[j];
			if (X[i] == Y[j])
				c[j] = q + 1;
			else
			{
				if (c[j] < c[j - 1])
					c[j] = c[j - 1];
			}
		}
	}
	rt = c[n - 1];
	free(c);
	return rt;
}

void testLongestMonotonicallyIncreasingSubsequence()
{
	int arr[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8 };
	int m = sizeof(arr) / sizeof(int), n, i;
	int *p, **c, **b;
	p = (int *)malloc(m * sizeof(int));
	for (i = 0; i < m; ++i)
		p[i] = arr[i];
	n = m;
	c = (int **)malloc((m + 1) * sizeof(int *));
	for (i = 0; i < m + 1; ++i)
		c[i] = (int *)malloc((n + 1) * sizeof(int));
	b = (int **)malloc(m * sizeof(int *));
	for (i = 0; i < m; ++i)
		b[i] = (int *)malloc(n * sizeof(int));

	printf("Before sort :\n");
	for (i = 0; i < m; ++i)
		printf("%d ", p[i]);
	qsort(p, m, sizeof(int), compareINT);
	printf("\n");
	printf("After sort :\n");
	for (i = 0; i < m; ++i)
		printf("%d ", p[i]);
	printf("\n");
	LCSLengthINT(c, b, m, n, arr, p);
	printf("LCS Length : %d\n", c[m][n]);
	printf("LCS is :\n");
	PrintLCSINT(b, arr, m - 1, n - 1);
	printf("\n");
	printf("LCS Length Least Memory : %d\n", LCSLengthLeastMemoryINT(m, n, arr, p));

	free(p);
	for (i = 0; i < m + 1; ++i)
		free(c[i]);
	free(c);
	for (i = 0; i < m; ++i)
		free(b[i]);
	free(b);
}
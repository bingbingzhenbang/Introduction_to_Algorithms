#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
	int *c = (int *)malloc(n * sizeof(int));
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

int BinarySearch(int *y, int len, int dest)
{
	int left = 0, right = len - 1, mid = 0;
	if (dest < y[0])
		return 0;
	else if (dest >= y[len - 1])
		return len;
	else
	{
		while (left + 1 < right)
		{
			mid = (left + right) / 2;
			if (y[mid] > dest)
				right = mid;
			else if (y[mid] < dest)
				left = mid;
			else
				++left;
		}
		return left + 1;
	}
}

void BruteLongestMonotonicallyIncreasingSubsequence(int *data, int size)
{
	int i = 0, j = 0, s = 0, x = 0, currentLen = 0;
	int **S, *y;
	if (size <= 0)
		return;
	S = (int **)malloc(size * sizeof(int *));
	y = (int *)malloc(size * sizeof(int));
	for (i = 0; i < size; ++i)
	{
		S[i] = (int *)malloc(size * sizeof(int));
		y[i] = INT_MAX;
		for (j = 0; j < size; ++j)
			S[i][j] = INT_MAX;
	}
	currentLen = 1;
	y[0] = data[0];
	S[0][0] = data[0];
	for (i = 1; i < size; ++i)
	{
		x = data[i];
		s = BinarySearch(y, currentLen, x);
		//if (s == 0)
		//{
		//	y[0] = x;
		//	S[0][0] = x;
		//}
		//else
		//{
		//for (j = 0; j < s; ++j)
		//	S[s][j] = S[s - 1][j];
		//y[s] = x;
		//S[s][s] = x;
		//if (s == currentLen)
		//	++currentLen;
		//}
		// simplified way
		for (j = 0; j < s; ++j)
			S[s][j] = S[s - 1][j];
		y[s] = x;
		S[s][s] = x;
		if (s == currentLen)
			++currentLen;
	}
	printf("Brute Longest Monotonically Increasing Subsequence Length : %d\n", currentLen);
	for (i = 0; i < currentLen; ++i)
	{
		for (j = 0; j <= i; ++j)
			printf("%d ", S[i][j]);
		printf("\n");
	}

	for (i = 0; i < size; ++i)
		free(S[i]);
	free(S);
	free(y);
}

void LongestMonotonicallyIncreasingSubsequence(int *data, int size)
{
	int i = 0, j = 0, s = 0, x = 0, currentLen = 0;
	int *y, *prev, *all_index, *subSequence;
	if (size <= 0)
		return;
	y = (int *)malloc(size * sizeof(int));
	prev = (int *)malloc(size * sizeof(int));
	all_index = (int *)malloc(size * sizeof(int));
	for (i = 0; i < size; ++i)
	{
		y[i] = INT_MAX;
		prev[i] = INT_MAX;
		all_index[i] = INT_MAX;
	}
	currentLen = 1;
	y[0] = data[0];
	prev[0] = -1;
	all_index[0] = 0;
	for (i = 1; i < size; ++i)
	{
		x = data[i];
		s = BinarySearch(y, currentLen, x);
		y[s] = x;
		all_index[s] = i;
		if (s == 0)
			prev[i] = -1;
		else
			prev[i] = all_index[s - 1];
		if (s == currentLen)
			++currentLen;
	}
	subSequence = (int *)malloc(currentLen * sizeof(int));
	for (i = currentLen - 1, s = all_index[i]; i >= 0 && s != -1; --i)
	{
		subSequence[i] = data[s];
		s = prev[s];
	}
	printf("Longest Monotonically Increasing Subsequence Length : %d\n", currentLen);
	for (i = 0; i < currentLen; ++i)
		printf("%d ", subSequence[i]);
	printf("\n");

	free(y);
	free(prev);
	free(all_index);
	free(subSequence);
}

void testBinarySearch()
{
	//int arr[] = { 1, 1, 3, 5, 6, 9, 9, 9, 10, 10, 10 };
	int arr[] = { 1, 1, 6, 9, 13 };
	int target = 10, len = sizeof(arr) / sizeof(int), rt = 0;;
	rt = BinarySearch(arr, len, target);
	printf("rt = %d\n", rt);
}

void testLongestMonotonicallyIncreasingSubsequence()
{
	//int arr[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8 };
	//int arr[] = { 20, 1, 21, 3, 22, 5, 23, 7, 26, 30, 31, 9 };
	//int arr[] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 };
	//int arr[] = { 7, 8, 9, 1, 2, 3, 4 };
	//int arr[] = { 1, 1, 2, 2, 2, 3, 3, 5, 3 };
	//int arr[] = { 2, 1, 3, 0, 4, 1, 5, 2, 7 };
	int arr[] = { 3, 5, 6, 2, 5, 4, 19, 5, 6, 7, 12 };
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
	LCSLengthINT(c, b, m, n, p, arr);
	printf("LCS Length : %d\n", c[m][n]);
	printf("LCS is :\n");
	PrintLCSINT(b, p, m - 1, n - 1);
	printf("\n");
	printf("LCS Length Least Memory : %d\n", LCSLengthLeastMemoryINT(m, n, arr, p));

	free(p);
	for (i = 0; i < m + 1; ++i)
		free(c[i]);
	free(c);
	for (i = 0; i < m; ++i)
		free(b[i]);
	free(b);

	//testBinarySearch();
	BruteLongestMonotonicallyIncreasingSubsequence(arr, m);
	LongestMonotonicallyIncreasingSubsequence(arr, m);
}
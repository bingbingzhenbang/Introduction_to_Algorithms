#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TableDirection
{
	Enum_Null,
	Enum_Top,
	Enum_Left,
	Enum_TopLeft
};

void LCSLength(int **c, int **b, int m, int n, char *X, char *Y)
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

void PrintLCS(int **b, char *X, int i, int j)
{
	if (i == -1 || j == -1)
		return;
	else
	{
		if (b[i][j] == Enum_TopLeft)
		{
			PrintLCS(b, X, i - 1, j - 1);
			printf("%c", X[i]);
		}
		else if (b[i][j] == Enum_Top)
			PrintLCS(b, X, i - 1, j);
		else if (b[i][j] == Enum_Left)
			PrintLCS(b, X, i, j - 1);
	}
}


void testLongestCommonSubsequence()
{
	char arr1[] = "ABCBDAB";
	char arr2[] = "BDCABA";
	//char arr1[] = "10010101";
	//char arr2[] = "010110110";
	int m = strlen(arr1), n = strlen(arr2), i = 0;
	int **c, **b;
	c = (int **)malloc((m + 1) * sizeof(int *));
	for (i = 0; i < m + 1; ++i)
		c[i] = (int *)malloc((n + 1) * sizeof(int));
	b = (int **)malloc(m * sizeof(int *));
	for (i = 0; i < m; ++i)
		b[i] = (int *)malloc(n * sizeof(int));

	LCSLength(c, b, m, n, arr1, arr2);
	printf("LCS Length : %d\n", c[m][n]);
	printf("LCS is : \n");
	PrintLCS(b, arr1, m - 1, n - 1);
	printf("\n");

	for (i = 0; i < m + 1; ++i)
		free(c[i]);
	free(c);
	for (i = 0; i < m; ++i)
		free(b[i]);
	free(b);
}
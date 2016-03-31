#include <stdio.h>
#include <stdlib.h>

void FastestWay(int *f_star, int *l_star, int size, int **f, int **l, int *e, int *x, int **a, int **t)
{
	int i = 0;
	f[0][0] = e[0] + a[0][0];
	f[1][0] = e[1] + a[1][0];
	for (i = 1; i < size; ++i)
	{
		if (f[0][i - 1]  <= f[1][i - 1] + t[1][i - 1])
		{
			f[0][i] = f[0][i - 1] + a[0][i];
			l[0][i - 1] = 0;
		}
		else
		{
			f[0][i] = f[1][i - 1] + t[1][i - 1] + a[0][i];
			l[0][i - 1] = 1;
		}
		if (f[1][i - 1] <= f[0][i - 1] + t[0][i - 1])
		{
			f[1][i] = f[1][i - 1] + a[1][i];
			l[1][i - 1] = 1;
		}
		else
		{
			f[1][i] = f[0][i - 1] + t[0][i - 1] + a[1][i];
			l[1][i - 1] = 0;
		}
	}
	if (f[0][size - 1] + x[0] <= f[1][size - 1] + x[1])
	{
		*f_star = f[0][size - 1] + x[0];
		*l_star = 0;
	}
	else
	{
		*f_star = f[1][size - 1] + x[1];
		*l_star = 1;
	}
}

void FastestWayLessMemory(int *f_star, int *l_star, int size, int *f, int **l, int *e, int *x, int **a, int **t)
{
	int i = 0, f_0, f_1;
	f[0] = e[0] + a[0][0];
	f[1] = e[1] + a[1][0];
	for (i = 1; i < size; ++i)
	{
		f_0 = f[0];
		f_1 = f[1];
		if (f_0 <= f_1 + t[1][i - 1])
		{
			f[0] = f_0 + a[0][i];
			l[0][i - 1] = 0;
		}
		else
		{
			f[0] = f_1 + t[1][i - 1] + a[0][i];
			l[0][i - 1] = 1;
		}
		if (f_1 <= f_0 + t[0][i - 1])
		{
			f[1] = f_1 + a[1][i];
			l[1][i - 1] = 1;
		}
		else
		{
			f[1] = f_0 + t[0][i - 1] + a[1][i];
			l[1][i - 1] = 0;
		}
	}
	if (f[0] + x[0] <= f[1] + x[1])
	{
		*f_star = f[0] + x[0];
		*l_star = 0;
	}
	else
	{
		*f_star = f[1] + x[1];
		*l_star = 1;
	}
}

void PrintStations(int line, int **l, int j)
{
	if (j > 0)
		PrintStations(l[line][j - 1], l, j - 1);
	printf("line : %d station : %d \n", line + 1, j + 1);
}

void ReversePrintStations(int size, int l_star, int **l)
{
	int i = l_star, j = size - 2;
	printf("line : %d station : %d \n", i + 1, size);
	for (; j >= 0; --j)
	{
		i = l[i][j];
		printf("line : %d station : %d \n", i + 1, j + 1);
	}
}

void testAssemblyLineScheduling()
{
	int i = 0, size = 0, f_star = 0, l_star = 0;
	int e[2], x[2];
	int *f[2], *a[2], *t[2], *l[2];
	FILE *fp = fopen("assembly_line_scheduling_input", "r");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d%d%d%d%d", &size, e, e + 1, x, x + 1);
	f[0] = (int*)malloc(size * sizeof(int));
	f[1] = (int*)malloc(size * sizeof(int));
	a[0] = (int*)malloc(size * sizeof(int));
	a[1] = (int*)malloc(size * sizeof(int));
	t[0] = (int*)malloc((size - 1)* sizeof(int));
	t[1] = (int*)malloc((size - 1)* sizeof(int));
	l[0] = (int*)malloc((size - 1)* sizeof(int));
	l[1] = (int*)malloc((size - 1)* sizeof(int));
	for (i = 0; i < size; ++i)
		fscanf(fp, "%d", &a[0][i]);
	for (i = 0; i < size; ++i)
		fscanf(fp, "%d", &a[1][i]);
	for (i = 0; i < size - 1; ++i)
		fscanf(fp, "%d", &t[0][i]);
	for (i = 0; i < size - 1; ++i)
		fscanf(fp, "%d", &t[1][i]);
	fclose(fp);

	printf("Assembly Line Scheduling\n");
	FastestWay(&f_star, &l_star, size, f, l, e, x, a, t);
	printf("Minimum Path : %d\n", f_star);
	printf("PrintStations :\n");
	PrintStations(l_star, l, size - 1);
	printf("\n");
	printf("ReversePrintStations :\n");
	ReversePrintStations(size, l_star, l);

	free(f[0]);
	free(f[1]);
	free(a[0]);
	free(a[1]);
	free(t[0]);
	free(t[1]);
	free(l[0]);
	free(l[1]);
}

void testAssemblyLineSchedulingLessMemory()
{
	int i = 0, size = 0, f_star = 0, l_star = 0;
	int e[2], x[2], f[2];
	int *a[2], *t[2], *l[2];
	FILE *fp = fopen("assembly_line_scheduling_input", "r");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d%d%d%d%d", &size, e, e + 1, x, x + 1);
	a[0] = (int*)malloc(size * sizeof(int));
	a[1] = (int*)malloc(size * sizeof(int));
	t[0] = (int*)malloc((size - 1)* sizeof(int));
	t[1] = (int*)malloc((size - 1)* sizeof(int));
	l[0] = (int*)malloc((size - 1)* sizeof(int));
	l[1] = (int*)malloc((size - 1)* sizeof(int));
	for (i = 0; i < size; ++i)
		fscanf(fp, "%d", &a[0][i]);
	for (i = 0; i < size; ++i)
		fscanf(fp, "%d", &a[1][i]);
	for (i = 0; i < size - 1; ++i)
		fscanf(fp, "%d", &t[0][i]);
	for (i = 0; i < size - 1; ++i)
		fscanf(fp, "%d", &t[1][i]);
	fclose(fp);

	printf("Assembly Line Scheduling Less Memory\n");
	FastestWayLessMemory(&f_star, &l_star, size, f, l, e, x, a, t);
	printf("Minimum Path : %d\n", f_star);
	printf("PrintStations :\n");
	PrintStations(l_star, l, size - 1);
	printf("\n");
	printf("ReversePrintStations :\n");
	ReversePrintStations(size, l_star, l);

	free(a[0]);
	free(a[1]);
	free(t[0]);
	free(t[1]);
	free(l[0]);
	free(l[1]);
}
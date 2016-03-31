#include <stdio.h>
#include <stdlib.h>

void testMatrixChainMultiplication()
{
	int i = 0, size = 0;
	int *p;
	FILE *fp = fopen("matrix_chain_multiplication_input", "r");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	p = (int*)malloc((size + 1) * sizeof(int));
	for (i = 0; i < size + 1; ++i)
		fscanf(fp, "%d", p + i);
	fclose(fp);
	free(p);
}
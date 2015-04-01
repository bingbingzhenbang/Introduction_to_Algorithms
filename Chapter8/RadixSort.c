#include "RadixSort.h"
#include <stdio.h>
#include <stdlib.h>

void BitsSort(ElementType *array, int *bitsArray, int size)
{
	int i, countSize, min=INT_MAX, max=INT_MIN;
	ElementType *outputArray;
	int *countArray;

	for (i=0; i<size; ++i)
	{
		if (bitsArray[i] < min)
			min = bitsArray[i];
		if (bitsArray[i] > max)
			max = bitsArray[i];
	}

	countSize = max - min + 1;

	countArray = (int *)malloc(countSize * sizeof(int));
	outputArray = (ElementType *)malloc(size * sizeof(ElementType));

	for (i=0; i<countSize; ++i)
		countArray[i] = 0;

	for (i=0; i<size; ++i)
		++countArray[bitsArray[i] - min];

	for (i=1; i<countSize; ++i)
		countArray[i] += countArray[i-1];

	for (i=size-1; i>=0; --i)
		outputArray[--countArray[bitsArray[i] - min]] = array[i];

	for (i=0; i<size; ++i)
		array[i] = outputArray[i];

	free(countArray);
	free(outputArray);
}

void RadixSort(ElementType *array, int size, int r, int pBase)
{
	ElementType max = INT_MIN, *bitsArray, base, divider;
	int i, j, maxBit;

	for (i=0; i<size; ++i)
		if (array[i] > max)
			max = array[i];

	for (base = pBase, i=1; i<r; base *= pBase, ++i)
		;

	bitsArray = (ElementType *)malloc(size * sizeof(ElementType));

	for (maxBit=0, i=1; i<max; ++maxBit, i *= pBase)
		;

	for (i=0, divider=1; i<r; ++i, divider *= pBase)
		;

	for (i=0, base=1; i<maxBit; i += r, base *= divider)
	{
		for (j=0; j<size; ++j)
			bitsArray[j] = (array[j]/base) % divider;
		BitsSort(array, bitsArray, size);
	}

	free(bitsArray);
}

void TestRadixSort()
{
	int i, size, r, pBase;
	ElementType *input;
	FILE *fp = fopen("radix_sort_input", "r");
	printf("Test radix sort\n");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	input = (ElementType *)malloc(size * sizeof(ElementType));

	for (i=0; i<size; ++i)
		fscanf(fp, "%d", input + i);

	printf("input r and pBase:\n");
	scanf("%d%d", &r, &pBase);

	RadixSort(input, size, r, pBase);

	for (i=0; i<size; ++i)
		printf("%d\n", input[i]);

	fclose(fp);
	free(input);
}
#include "LinearTimeSort.h"
#include <stdio.h>
#include <stdlib.h>

void CountingSort(ElementType *outputArray, ElementType *inputArray, int size)
{
	ElementType min = INT_MAX, max = INT_MIN;
	ElementType *count;
	int i, cntSize;

	for (i=0; i<size; ++i)
	{
		if (inputArray[i] < min)
			min = inputArray[i];
		if (inputArray[i] > max)
			max = inputArray[i];
	}
	cntSize = max - min + 1;

	count = (ElementType *)malloc(cntSize * sizeof(ElementType));

	for (i=0; i<cntSize; ++i)
		count[i] = 0;

	for (i=0; i<size; ++i)
		++count[inputArray[i] - min];

	for (i=1; i<cntSize; ++i)
		count[i] += count[i-1];

	for (i=size - 1; i>=0; --i)
		outputArray[--count[inputArray[i] - min]] = inputArray[i];

	free(count);
}

void InplaceCountingSort(ElementType *array, int size)
{
	ElementType min = INT_MAX, max = INT_MIN;
	ElementType *count;
	int i, j, cnt,cntSize;

	for (i=0; i<size; ++i)
	{
		if (array[i] < min)
			min = array[i];
		if (array[i] > max)
			max = array[i];
	}
	cntSize = max - min + 1;

	count = (ElementType *)malloc(cntSize * sizeof(ElementType));

	for (i=0; i<cntSize; ++i)
		count[i] = 0;

	for (i=0; i<size; ++i)
		++count[array[i]-min];

	for (i=0, j=0; i<cntSize; ++i)
	{
		for (cnt=0; cnt<count[i]; ++cnt)
			array[j++] = i + min;
	}

	free(count);
}

void TestLinearTimeSort()
{
	int i, size;
	ElementType *input, *output;
	FILE *fp = fopen("sort_input", "r");
	printf("Test linear time sort\n");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	input = (ElementType *)malloc(size * sizeof(ElementType));
	output = (ElementType *)malloc(size * sizeof(ElementType));

	for (i=0; i<size; ++i)
	{
		fscanf(fp, "%d", input + i);
	}

	//CountingSort(output, input, size);
	InplaceCountingSort(input, size);

	for (i=0; i<size; ++i)
		printf("%d\n", input[i]);

	fclose(fp);
	free(input);
	free(output);
}
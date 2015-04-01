#include "QuickSelect.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int AdditionalPartion(DataType *array, int begin, int end, int dis)
{
	int i, j;
	int Length = end - begin;
	DataType x = array[end];
	for (i=begin-1, j=begin; j<=end-1; ++j)
	{
		if (array[j] <= x)
		{
			Swap(&array[++i], &array[j]);
			if (dis > Length)
				Swap(&array[i+dis], &array[j+dis]);
		}
	}
	Swap(&array[++i], &array[end]);
	if (dis > Length)
		Swap(&array[i+dis], &array[end+dis]);
	
	return i;
}

void AdditionalInsertSort(DataType *array, int begin, int end, int dis)
{
	int i, j;
	DataType key, dKey;
	for (j=begin+1; j<=end; ++j)
	{
		key = array[j];
		if (dis > end - begin)
			dKey = array[j+dis];
		for (i=j-1; i>=0 && array[i]>key; --i)
		{
			array[i+1] = array[i];
			if (dis > end - begin)
				array[i+1+dis] = array[i+dis];
		}
		array[i+1] = key;
		if (dis > end - begin)
			array[i+1+dis] = dKey;
	}
}

DataType AdditionalSelect(DataType *array, int begin, int end, int nth, int dis)
{
	DataType midData = 0, *midArray;
	int size, midSize, i, k, q, midBegin, choose;

	while (begin < end)
	{
		size = end - begin + 1;

		if (size % LEN == 0)
			midSize = size/LEN;
		else
			midSize = size/LEN + 1;

		midArray = (DataType *)malloc(midSize * sizeof(DataType));

		for (i=0, midBegin=begin, choose=begin+LEN/2; i<midSize-1; ++i, midBegin += LEN, choose += LEN)
		{
			AdditionalInsertSort(array, midBegin, midBegin+LEN-1, dis);
			midArray[i] = array[choose];
		}
		AdditionalInsertSort(array, midBegin, end, dis);
		midArray[i] = array[midBegin + (end-midBegin)/2];

		midData = Select(midArray, 0, midSize-1, (midSize+1)/2);
		free(midArray);

		for (i=begin; i<=end && array[i]!=midData; ++i)
			;

		Swap(&array[i], &array[end]);
		if (dis > end - begin)
			Swap(&array[i+dis], &array[end+dis]);

		q = AdditionalPartion(array, begin, end, dis);
		k = q - begin + 1;

		if (k==nth)
			return array[q];
		else if (nth<k)
			end = q-1;
		else
		{
			begin = q+1;
			nth -= k;
		}
	}
	return array[begin];
}

DataType QuickSelect(DataType *array, int begin, int end, int nth)
{
	int i, m, q, size, bSize;
	DataType nthData, midData, *bArray;

	if (begin < end)
	{
		size = end - begin + 1;

		m = size/2;

		if (nth >= m)
			return Select(array, begin, end, nth);

		for (i=begin; i<begin + m; ++i)
		{
			if (array[i] > array[i+m])
				Swap(&array[i], &array[i+m]);
		}

		midData = AdditionalSelect(array, begin, begin+m-1, nth, m);

		if (size%2==0)
		{
			bSize = 2*nth;
			bArray = (DataType *)malloc(bSize * sizeof(DataType));
			for (i=0; i<nth; ++i)
			{
				bArray[i] = array[i];
				bArray[i+nth] = array[i+m];
			}
		}
		else
		{
			bSize = 2*nth + 1;
			bArray = (DataType *)malloc(bSize * sizeof(DataType));
			for (i=0; i<nth; ++i)
			{
				bArray[i] = array[i];
				bArray[i+nth] = array[i+m];
			}
			bArray[2 * nth] = array[end];
		}

		nthData = Select(bArray, 0, bSize-1, nth);
		free(bArray);

		for (i=begin; i<=end && array[i]!=nthData; ++i)
			;

		Swap(&array[i], &array[end]);

		q = Partion(array, begin, end);

		return array[q];
	}
	return array[begin];
}

void TestQuickSelect()
{
	time_t t;
	int i, k, size, nth;
	DataType *array, data;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");

	printf("input size, -1 to end:\n");
	scanf("%d", &size);

	while (size != -1)
	{
		array = (DataType *)malloc(size * sizeof(DataType));

		printf("input nth\n");
		scanf("%d", &nth);

		for (i=0; i<size; ++i)
			array[i] = i+1;
		for (i=0; i<size; ++i)
		{
			k = i + (double)rand()/RAND_MAX * (size - 1 - i);
			Swap(&array[i], &array[k]);
		}

		data = QuickSelect(array, 0, size-1, nth);

		printf("%d th\t%d\n", nth, data);

		printf("input size, -1 to end:\n");
		scanf("%d", &size);

		free(array);
	}
}
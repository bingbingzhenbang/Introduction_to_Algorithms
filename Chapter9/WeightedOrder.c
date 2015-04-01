#include "WeightedOrder.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SwapWeight(WeightData *w1, WeightData *w2)
{
	WeightData temp;
	temp = *w1;
	*w1 = *w2;
	*w2 = temp;
}

int WeightedPartion(WeightData *array, int begin, int end)
{
	int i, j, k;
	WeightData x;

	x = array[end];

	for (i=begin-1, j=begin; j<=end-1; ++j)
	{
		if (array[j].m_Value <= x.m_Value)
			SwapWeight(&array[++i], &array[j]);
	}
	SwapWeight(&array[++i], &array[end]);

	return i;
}

void WeightedInsertSort(WeightData *array, int begin, int end)
{
	int i, j;
	WeightData key;
	for (j=begin+1; j<=end; ++j)
	{
		key = array[j];
		for (i=j-1; i>=0 && array[i].m_Value > key.m_Value; --i)
			array[i+1] = array[i];
		array[i+1] = key;
	}
}

WeightData WeightedSelect(int *selectedIndex, WeightData *array, int begin, int end, int nth)
{
	WeightData midData, *midArray;
	int size, midSize, midIndex=0, i, k, q, midBegin, choose;

	while (begin < end)
	{
		size = end - begin + 1;

		if (size % LEN == 0)
			midSize = size/LEN;
		else
			midSize = size/LEN + 1;

		midArray = (WeightData *)malloc(midSize * sizeof(WeightData));

		for (i=0, midBegin=begin, choose=begin+LEN/2; i<midSize-1; ++i, midBegin += LEN, choose += LEN)
		{
			WeightedInsertSort(array, midBegin, midBegin+LEN-1);
			midArray[i] = array[choose];
		}
		WeightedInsertSort(array, midBegin, end);
		midArray[i] = array[midBegin + (end-midBegin)/2];

		midData = WeightedSelect(&midIndex, midArray, 0, midSize-1, (midSize+1)/2);
		free(midArray);

		for (midIndex=begin; midIndex<=end 
			&& array[midIndex].m_Value==midData.m_Value && array[midIndex].m_Weight==midData.m_Weight; ++midIndex)
			;

		SwapWeight(&array[midIndex], &array[end]);

		q = WeightedPartion(array, begin, end);
		k = q - begin + 1;

		if (k==nth)
		{
			*selectedIndex = q;
			return array[q];
		}
		else if (nth<k)
			end = q-1;
		else
		{
			begin = q+1;
			nth -= k;
		}
	}
	*selectedIndex = begin;
	return array[begin];
}

WeightData WeightedValueMedian(int *selectedIndex, WeightData *array, int begin, int end)
{
	int size = end - begin + 1;

	return WeightedSelect(selectedIndex, array, begin, end, (size+1)/2);
}

WeightData WeightedMedian(WeightData *array, int begin, int end, double WL, double WR)
{
	int i=0, size, midIndex;
	WeightData midData;
	double wL=WL, wR=WR;

	while (begin < end)
	{
		size = end - begin + 1;

		wL = WL;
		wR = WR;

		midData = WeightedValueMedian(&midIndex, array, begin, end);

		for (i=begin; i<midIndex; ++i)
			wL += array[i].m_Weight;

		for (i=midIndex+1; i<=end; ++i)
			wR += array[i].m_Weight;

		if (wL < 0.5 + ERROR && wR <= 0.5 + ERROR)
		{
			return midData;
		}
		else if (wL >= 0.5)
		{
			end = midIndex;
			WR = wR;
		}
		else
		{
			begin = midIndex;
			WL = wL;
		}
	}
	return array[begin];
}

void TestWeightMedian()
{
	time_t t;
	int i, k, size, midIndex=0;
	DataType *values;
	WeightData *array, mid;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");
	printf("input size:\n");
	scanf("%d", &size);
	values = (DataType *)malloc(size * sizeof(DataType));
	array = (WeightData *)malloc(size * sizeof(WeightData));
	for (i=0; i<size; ++i)
		values[i] = i+1;

	for (i=0; i<size; ++i)
	{
		k = i + (double)rand()/RAND_MAX * (size - 1 - i);
		Swap(&values[i], &values[k]);
	}

	for (i=0; i<size; ++i)
	{
		array[i].m_Value = values[i];
		array[i].m_Weight = 1/(double)size;
	}

	//mid = WeightedValueMedian(&midIndex, array, 0, size-1);

	//printf("index = %d\nvalue = %d\nweight = %f\n\n", midIndex, mid.m_Value, mid.m_Weight);

	mid = WeightedMedian(array, 0, size-1, 0, 0);

	printf("value = %d\nweight = %f\n\n", mid.m_Value, mid.m_Weight);

	free(values);
	free(array);
}
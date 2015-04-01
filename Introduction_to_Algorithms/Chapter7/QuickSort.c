#include "QuickSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(ElementType *d1, ElementType *d2)
{
	ElementType temp;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
	return;
}

void SwapInterval(IntervalPtr *ptr1, IntervalPtr *ptr2)
{
	IntervalPtr temp;
	temp = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = temp;
}

int Partion(ElementType *array, int begin, int end)
{
	int i, j;
	ElementType x = array[end];

	for (i=begin-1, j=begin; j<=end-1; ++j)
	{
		if (array[j] <= x)
			Swap(&array[++i], &array[j]);
	}
	Swap(&array[++i], &array[end]);

	return i;
}

void QuickSort(ElementType *array, int begin, int end)
{
	int mid;
	if (begin < end)
	{
		mid = Partion(array, begin, end);
		QuickSort(array, begin, mid - 1);
		QuickSort(array, mid + 1, end);
	}
}

int RandomPartion(ElementType *array, int begin, int end)
{
	int x;
	x = begin + (double)rand()/RAND_MAX * (end - begin);
	Swap(&array[x], &array[end]);
	return Partion(array, begin, end);
}

void RandomQuickSort(ElementType *array, int begin, int end)
{
	int mid;
	if (begin < end)
	{
		mid = RandomPartion(array, begin, end);
		RandomQuickSort(array, begin, mid - 1);
		RandomQuickSort(array, mid + 1, end);
	}
}

void QuickInsertSort(ElementType *array, int size, int k)
{
	PartialQuickSort(array, 0, size-1, k);
	InsertSort(array, size);
}

void PartialQuickSort(ElementType *array, int begin, int end, int k)
{
	int mid;
	if (end - begin + 1 > k)
	{
		mid = Partion(array, begin, end);
		PartialQuickSort(array, begin, mid-1, k);
		PartialQuickSort(array, mid+1, end, k);
	}
}

void InsertSort(ElementType *array, int size)
{
	int i, j;
	ElementType key;
	for (j=1; j<size; ++j)
	{
		key = array[j];
		for (i=j-1; i>=0 && array[i]>key; --i)
			array[i+1] = array[i];
		array[i+1] = key;
	}
}

int HoarePartion(ElementType *array, int begin, int end)
{
	int i, j;
	ElementType x;
	i = begin;
	j = end;
	x = array[begin];

	while (1)
	{
		for (; array[j]>x; --j)
			;
		for (; array[i]<x; ++i)
			;
		if (i < j)
			Swap(&array[i++], &array[j--]);
		else
			return j;
	}

}

void StoogeSort(ElementType *array, int begin, int end)
{
	int k;
	if (array[begin] > array[end])
		Swap(&array[begin], &array[end]);
	if (begin + 1 >= end)
		return;

	k = (end - begin + 1)/3;

	StoogeSort(array, begin, end - k);
	StoogeSort(array, begin + k, end);
	StoogeSort(array, begin, end - k);
}

void TailQuickSort(ElementType *array, int begin, int end)
{
	int mid;
	while (begin < end)
	{
		mid = Partion(array, begin, end);
		TailQuickSort(array, begin, mid - 1);
		begin = mid + 1;
	}
}

int IntervalLess(IntervalPtr ptr1, IntervalPtr ptr2)
{
	return (ptr1->m_Right < ptr2->m_Left)? 1 : 0;
}

int IntervalGreater(IntervalPtr ptr1, IntervalPtr ptr2)
{
	return (ptr1->m_Left > ptr2->m_Right)? 1 : 0;
}

Divid IntervalPartion(IntervalPtr *array, int begin, int end)
{
	Divid a;
	int i, j, k;
	Interval domain;

	i = begin - 1;
	j = end + 1;
	k = begin;
	domain = *array[end];

	while (k<=end && k<j)
	{
		if (IntervalLess(array[k], &domain))
			SwapInterval(&array[++i], &array[k++]);
		else if (IntervalGreater(array[k], &domain))
			SwapInterval(&array[--j], &array[k]);
		else
		{
			domain.m_Left = (domain.m_Left > array[k]->m_Left) ? domain.m_Left : array[k]->m_Left;
			domain.m_Right = (domain.m_Right < array[k]->m_Right) ? domain.m_Right : array[k]->m_Right;
			++k;
		}
	}
	a.m_i = i;
	a.m_j = j;
	return a;
}

void IntervalSort(IntervalPtr *array, int begin, int end)
{
	Divid q;
	if (begin >= end)
		return;

	q = IntervalPartion(array, begin, end);
	IntervalSort(array, begin, q.m_i);
	IntervalSort(array, q.m_j, end);
}

void TestPartion()
{
	int array[] = {13,19,9,5,12,8,7,4,11,2,6,21};
	int i, p, size;
	size = sizeof(array)/sizeof(int);
	printf("Test partion:\n");
	p = HoarePartion(array, 0, size - 1);
	for (i=0; i<size; ++i)
		printf("%3d", *(array+i));
	printf("\n");
}

void TestQuickSort()
{
	int i, size, k;
	ElementType *array;
	time_t t;
	FILE *fp = fopen("sort_input", "r");
	printf("Test quick sort:\n");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	srand((unsigned)time(&t));
	fscanf(fp, "%d", &size);
	array = (ElementType *)malloc(size * sizeof(ElementType));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", array + i);

	k = 2;

	TailQuickSort(array, 0, size - 1);

	for (i=0; i<size; ++i)
		printf("%2d\n", array[i]);

	fclose(fp);
	free(array);
}

void  TestIntervalSort()
{
	int i, size;
	IntervalPtr *intervalList, *ptr;
	FILE *fp = fopen("interval_sort_input", "r");
	printf("Test interval sort:\n");
	if (fp == NULL)
	{
		printf("cannnot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	intervalList = (IntervalPtr *)malloc(size * sizeof(IntervalPtr));
	for (ptr=intervalList; ptr<intervalList+size; ++ptr)
	{
		*ptr = (IntervalPtr)malloc(sizeof(Interval));
		fscanf(fp, "%d%d", &(*ptr)->m_Left, &(*ptr)->m_Right);

		if ((*ptr)->m_Left > (*ptr)->m_Right)
		{
			printf("Interval error!\n");
			return;
		}
	}

	IntervalSort(intervalList, 0, size-1);

	for (ptr=intervalList; ptr<intervalList+size; ++ptr)
		printf("%3d  %3d\n", (*ptr)->m_Left, (*ptr)->m_Right);

	for (i=0; i<size; ++i)
		free(intervalList[i]);
	free(intervalList);

	fclose(fp);
}
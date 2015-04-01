#include "Random.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static int *Array;
static int *Power;
static int Size = 0;

void Merge(int *array, int *power, int p, int q, int r)
{
	int i, j, k, n1, n2;
	int *L, *R, *Lpower, *Rpower;

	n1 = q - p + 1;
	n2 = r - q;

	L = (int*)malloc((n1 + 1) * sizeof(int));
	R = (int*)malloc((n2 + 1) * sizeof(int));
	Lpower = (int*)malloc((n1 + 1) * sizeof(int));
	Rpower = (int*)malloc((n2 + 1) * sizeof(int));

	for (i=0; i<n1; ++i)
	{
		L[i] = array[i + p];
		Lpower[i] = power[i + p];
	}
	L[n1] = INT_MAX;
	Lpower[n1] = INT_MAX;

	for (i=0; i<n2; ++i)
	{
		R[i] = array[i + q + 1];
		Rpower[i] = power[i + q + 1];
	}
	R[n2] = INT_MAX;
	Rpower[n2] = INT_MAX;

	i=0;j=0;
	for (k=p; k<r+1; ++k)
	{
		if (Lpower[i]<=Rpower[j])
		{
			array[k] = L[i];
			power[k] = Lpower[i++];
		}
		else
		{
			array[k] = R[j];
			power[k] = Rpower[j++];
		}
	}
	free(L);
	free(R);
	free(Lpower);
	free(Rpower);
}

void MergeSort(int *array, int *power, int p, int q)
{
	if (p < q)
	{
		int mid = (p + q)/2;
		MergeSort(array, power, p, mid);
		MergeSort(array, power, mid + 1, q);
		Merge(array, power, p, mid, q);
	}
}

void InitialArray(int size)
{
	int i;
	Array = (int*)malloc(size * sizeof(int));
	Size = size;
	for (i=0; i<size; ++i)
		Array[i] = i+1;
}

void PowerRandomSort()
{
	MergeSort(Array, Power, 0, Size - 1);
}

void TestPowerRandomSort(int size)
{
	int i;
	int cube;

	srand((unsigned)time(0));

	InitialArray(size);

	Power = (int*)malloc(size * sizeof(int));
	cube = size * size * size;
	for (i=0; i<size; ++i)
		Power[i] = (double)rand()/RAND_MAX * cube;

	PowerRandomSort();

	for (i=0; i<Size; ++i)
		printf("%d\n", Array[i]);
}

void RandomInPlace()
{
	int i, k, p;
	for (i=0; i<Size; ++i)
	{
		k = i + (double)rand()/RAND_MAX * (Size - i - 1);
		p = Array[k];
		Array[k] = Array[i];
		Array[i] = p;
	}
}

void TestRandomInPlace(int size)
{
	int i;

	srand((unsigned)time(0));

	InitialArray(size);

	RandomInPlace();

	for (i=0; i<Size; ++i)
		printf("%d\n", Array[i]);
}

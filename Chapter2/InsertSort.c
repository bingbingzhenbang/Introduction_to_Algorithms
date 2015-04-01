#include "decla.h"

void InsertSort(Item *array, int size)
{
	int i, j;
	Item key;
	for (j=1; j<size; ++j)
	{
		key = array[j];
		for (i = j-1; i>=0 && array[i]>key; --i)
			array[i+1] = array[i];

		array[i+1] = key;
	}
}

void RecurInsertSort(Item *array, int p, int q)
{
	int i;
	Item key;
	if (p<q)
	{
		RecurInsertSort(array, p, q-1);
		key = array[q];
		for (i=q-1; i>=0 && array[i]>=key; --i)
			array[i+1] = array[i];
		array[i+1] = key;
	}
}
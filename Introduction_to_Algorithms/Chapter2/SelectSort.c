#include "decla.h"

void SelectSort(Item *array, int size)
{
	int i, j, k;
	Item key;
	for (i=0; i<size-1; ++i)
	{
		k = i;
		key = array[i];
		for (j=i+1; j<size; ++j)
		{
			if (array[j] < array[k])
				k = j;
		}
		array[i] = array[k];
		array[k] = key;
	}
}
#include "decla.h"

void BubbleSort(Item *array, int size)
{
	int i, j;
	Item temp;
	for (i=0; i<size-1; ++i)
	{
		for (j=size-1; j>i; --j)
		{
			if (array[j-1] > array[j])
			{
				temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			}
		}
	}
}
#include "decla.h"
#include <stdlib.h>

int MergeInversionCount(Item *array, int p, int q, int r)
{
	int i, j, k, n1, n2, count = 0;
	Item *L, *R;

	n1 = q - p + 1;
	n2 = r - q;

	L = (Item*)malloc((n1 + 1) * sizeof(Item));
	R = (Item*)malloc((n2 + 1) * sizeof(Item));

	for (i=0; i<n1; ++i)
		L[i] = array[i + p];
	L[n1] = ITEMMAX;

	for (i=0; i<n2; ++i)
		R[i] = array[i + q + 1];
	R[n2] = ITEMMAX;

	i=0;j=0;
	for (k=p; k<r+1; ++k)
	{
		if (L[i]<=R[j])
			array[k] = L[i++];
		else
		{
			array[k] = R[j++];
			if (i != n1)
				count += n1 - i;
		}
	}
	free(L);
	free(R);

	return count;
}

int InversionCount(Item *array, int p, int q)
{
	int count = 0, mid;
	if (p<q)
	{
		mid = (p+q)/2;
		count += InversionCount(array, p, mid);
		count += InversionCount(array, mid+1, q);
		count += MergeInversionCount(array, p, mid, q);
	}
	return count;
}

int InversionTest(Item *array, int size)
{
	int count = 0, i, j;

	for (i=0; i<size-1; ++i)
	{
		for (j=i+1; j<size; ++j)
		{
			if (array[i]>array[j])
				++count;
		}
	}

	return count;
}
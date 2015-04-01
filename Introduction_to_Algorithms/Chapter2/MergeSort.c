#include "decla.h"
#include <stdlib.h>

void Merge(Item *array, int p, int q, int r)
{
	int i, j, k, n1, n2;
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
			array[k] = R[j++];
	}
	free(L);
	free(R);
}

void MergeSort(Item *array, int p, int q)
{
	if (p < q)
	{
		int mid = (p + q)/2;
		MergeSort(array, p, mid);
		MergeSort(array, mid + 1, q);
		Merge(array, p, mid, q);
	}
}
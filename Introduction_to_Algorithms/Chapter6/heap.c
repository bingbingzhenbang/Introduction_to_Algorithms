#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

HeapPtr BuildHeap(ElementType *array, int size)
{
	int i = 0, cap;
	HeapPtr ptr = (HeapPtr)malloc(sizeof(Heap));
	ptr->m_Size = size;
	cap = (size > MAXHEAP) ? (size+1) : MAXHEAP;
	ptr->m_Data = (ElementType*)malloc(cap * sizeof(ElementType));
	ptr->m_Capaity = cap;

	for (i=0; i<size; ++i)
		ptr->m_Data[i] = array[i];

	for (i=(ptr->m_Size/2)-1; i>=0; --i)
		MaxHeapify(ptr, i);

	return ptr;
}

void HeapSort(ElementType *array, int size)
{
	int i; ElementType temp;
	HeapPtr ptr = BuildHeap(array, size);
	while (ptr->m_Size >= 2)
	{
		temp = ptr->m_Data[ptr->m_Size-1];
		ptr->m_Data[ptr->m_Size-1] = ptr->m_Data[0];
		ptr->m_Data[0] = temp;
		--ptr->m_Size;
		MaxHeapify(ptr, 0);
	}
	for (i=0; i<size; ++i)
		array[i] = ptr->m_Data[i];
	DestructHeap(ptr);
	return;
}

void MaxHeapify(HeapPtr ptr, int i)
{
	int largest = i, L, R;
	if (i>=0 && i<ptr->m_Size)
	{
		L = Left(i);
		R = Right(i);

		if (L < ptr->m_Size && ptr->m_Data[L] > ptr->m_Data[i])
			largest = L;

		if (R < ptr->m_Size && ptr->m_Data[R] > ptr->m_Data[largest])
			largest = R;

		if (largest != i)
		{
			ElementType temp = ptr->m_Data[i];
			ptr->m_Data[i] = ptr->m_Data[largest];
			ptr->m_Data[largest] = temp;
			MaxHeapify(ptr, largest);
		}
	}
}

void DestructHeap(HeapPtr ptr)
{
	ptr->m_Size = 0;
	free(ptr->m_Data);
	free(ptr);
}

void TestHeap()
{
	int i, size;
	ElementType *array = NULL;
	HeapPtr ptr;
	FILE *fp;
	fp = fopen("input", "r");
	if (fp)
	{
		fscanf(fp, "%d", &size);
		array = (ElementType*)malloc(size * sizeof(ElementType));
		if (array == NULL)
		{
			printf("No memory!\n");
			return;
		}
		for (i=0; i<size; ++i)
			fscanf(fp, "%d", array + i);

		HeapSort(array, size);

		for (i=0; i<size; ++i)
			printf("%d\n", array[i]);

		free(array);
		fclose(fp);
	}
}
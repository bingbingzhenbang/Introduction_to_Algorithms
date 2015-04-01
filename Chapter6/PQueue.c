#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>

Compare CompareFunction[Enum_TypeCount]={Greater, Less};

int Greater(DataType *d1, DataType *d2)
{
	return ((d1->m_key > d2->m_key) ? 1:0);
}

int Less(DataType *d1, DataType *d2)
{
	return ((d1->m_key < d2->m_key) ? 1:0);
}

void Swap(DataType *d1, DataType *d2)
{
	DataType temp;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

void Initial(PQueue *ptr, int type)
{
	ptr->m_Size = ptr->m_Capaity = 0;
	ptr->m_HeapType = type;
	ptr->m_Data = NULL;
}

PQueue* BuildPQueue(DataType *array, int size, Compare compare)
{
	int cap, i;
	PQueue *ptr = (PQueue*)malloc(sizeof(PQueue));
	ptr->m_Size = size;
	cap = (MAXHEAP > size) ? MAXHEAP : (size + 1);
	ptr->m_Data = (DataType*)malloc(cap * sizeof(DataType));
	ptr->m_Capaity = cap;

	for (i=0; i<size; ++i)
		ptr->m_Data[i] = array[i];

	for (i=size/2-1; i>=0; --i)
		Heapify(ptr, i, compare);

	return ptr;
}

void Heapify(PQueue *ptr, int i, Compare compare)
{
	int L, R, largest = i;
	if (i>=0 && i<ptr->m_Size)
	{
		L = Left(i);
		R = Right(i);

		if (L < ptr->m_Size && compare( &ptr->m_Data[L], &ptr->m_Data[i]) )
			largest = L;
		if (R < ptr->m_Size && compare( &ptr->m_Data[R], &ptr->m_Data[largest]) )
			largest = R;

		if (largest != i)
		{
			Swap(&ptr->m_Data[i], &ptr->m_Data[largest]);
			Heapify(ptr, largest, compare);
		}
	}
}

DataType GetTop(PQueue *ptr)
{
	return ptr->m_Data[0];
}

DataType PopTop(PQueue *ptr)
{
	DataType max = ptr->m_Data[0];

	if (ptr->m_Size > 1)
	{
		Swap(&ptr->m_Data[0], &ptr->m_Data[ptr->m_Size-1]);
		--ptr->m_Size;
		Heapify(ptr, 0, CompareFunction[ptr->m_HeapType]);
	}
	else
		--ptr->m_Size;

	return max;
}

void IncreaseKey(PQueue *ptr, int i, Key key)
{
	int parent;
	if (key < ptr->m_Data[i].m_key)
	{
		printf("key less!\n");
		return;
	}
	ptr->m_Data[i].m_key = key;
	while (i > 0 && Greater(&ptr->m_Data[i], &ptr->m_Data[Parent(i)]))
	{
		Swap(&ptr->m_Data[i], &ptr->m_Data[Parent(i)]);
		i = Parent(i);
	}
}

void DecreaseKey(PQueue *ptr, int i, Key key)
{
	int parent;
	if (key > ptr->m_Data[i].m_key)
	{
		printf("key less!\n");
		return;
	}
	ptr->m_Data[i].m_key = key;
	while (i > 0 && Less(&ptr->m_Data[i], &ptr->m_Data[Parent(i)]))
	{
		Swap(&ptr->m_Data[i], &ptr->m_Data[Parent(i)]);
		i = Parent(i);
	}
}

void InsertItem(PQueue *ptr, DataType element)
{
	int cap, i;
	DataType *newArray;
	if (ptr->m_Size == ptr->m_Capaity)
	{
		cap = 2 * ptr->m_Capaity;
		cap = (cap > MAXHEAP)?cap:MAXHEAP;
		newArray = (DataType*)malloc(cap * sizeof(DataType));
		for (i=0; i<ptr->m_Size; ++i)
			newArray[i] = ptr->m_Data[i];
		
		if (ptr->m_Data != NULL)
			free(ptr->m_Data);
		ptr->m_Data = newArray;
		ptr->m_Capaity = cap;
	}
	++ptr->m_Size;
	switch (ptr->m_HeapType)
	{
	case Enum_MaxHeap:
		{
			ptr->m_Data[ptr->m_Size - 1].m_key = INT_MIN;
			ptr->m_Data[ptr->m_Size - 1].m_value = element.m_value;
			IncreaseKey(ptr, ptr->m_Size-1, element.m_key);
		}
		break;
	case Enum_MinHeap:
		{
			ptr->m_Data[ptr->m_Size - 1].m_key = INT_MAX;
			ptr->m_Data[ptr->m_Size - 1].m_value = element.m_value;
			DecreaseKey(ptr, ptr->m_Size-1, element.m_key);
		}
		break;
	default:
		break;
	}
}

void DestructData(PQueue *ptr)
{
	ptr->m_Size = 0;
	if (ptr->m_Data != NULL)
		free(ptr->m_Data);
}

void DestructPQueue(PQueue *ptr)
{
	ptr->m_Size = 0;
	free(ptr->m_Data);
	free(ptr);
}

void TestPQueue()
{
	int i, size;
	DataType *array, data;
	PQueue *pq;
	FILE *fp = fopen("input", "r");
	if (!fp)
	{
		printf("cannot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	array = (DataType*)malloc(size * sizeof(DataType));

	for (i=0; i<size; ++i)
		fscanf(fp, "%d%d", &array[i].m_key, &array[i].m_value);

	pq = BuildPQueue(array, size, Greater);
	pq->m_HeapType = 0;
	for (i=0; i<pq->m_Size; ++i)
		printf("key = %3d value = %3d\n", pq->m_Data[i].m_key, pq->m_Data[i].m_value);

	for (i=0; i<10; ++i)
	{
		data.m_key = i * i - 10;
		data.m_value = i * i * i;
		InsertItem(pq, data);
	}

	printf("After insert:\n");
	while (pq->m_Size > 0)
	{
		data = PopTop(pq);
		printf("key = %3d value = %3d\n", data.m_key, data.m_value);
	}


	fclose(fp);
	free(array);
	DestructPQueue(pq);

	return;
}
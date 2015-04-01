#include "MergeLinkSort.h"
#include <stdio.h>
#include <stdlib.h>

void MergeLinkSort(Key *outputArray, int totalSize, LinkNodePtr *ptrList, int listSize, int size)
{
	int i, j;
	DataType data, *dataList;
	LinkNodePtr ptr;
	PQueue *pq;

	dataList = (DataType*)malloc(listSize * sizeof(DataType));

	for (i=0, j=0; i<size && j<listSize; ++i)
	{
		ptr = ptrList[i];
		if (ptr != NULL)
		{
			dataList[j].m_key = ptr->m_Key;
			dataList[j++].m_value = i;
		}
	}
	pq = BuildPQueue(dataList, listSize, Less);
	pq->m_HeapType = 1;
	for (i=0; i<totalSize; ++i)
	{
		data = GetTop(pq);
		outputArray[i] = data.m_key;
		ptrList[data.m_value] = ptrList[data.m_value]->m_Next;
		if (ptrList[data.m_value] != NULL)
			pq->m_Data[0].m_key = ptrList[data.m_value]->m_Key;
		else
		{
			Swap(&pq->m_Data[0], &pq->m_Data[pq->m_Size-1]);
			--pq->m_Size;
		}
		Heapify(pq, 0, CompareFunction[pq->m_HeapType]);
	}
	free(dataList);
	DestructPQueue(pq);
}

void TestMergeLinkSort()
{
	int i, size, listSize, totalSize, key;
	LinkNodePtr *ptrList, ptr, qtr;
	Key *output;
	FILE *fp = fopen("link_input", "r");
	if (!fp)
	{
		printf("cannot open file\n");
		return;
	}
	fscanf(fp, "%d", &size);
	ptrList = (LinkNodePtr *)malloc(size * sizeof(LinkNodePtr));
	
	listSize = 0;
	totalSize = 0;
	for (i=0; i<size; ++i)
	{
		ptrList[i] = NULL;
		fscanf(fp, "%d", &key);
		if (key != ENDNUM)
		{
			++listSize;
			ptr = ptrList[i] = (LinkNodePtr)malloc(sizeof(LinkNode));
			ptr->m_Key = key;
			++totalSize;
			fscanf(fp, "%d", &key);
			while (key != ENDNUM)
			{
				ptr->m_Next = (LinkNodePtr)malloc(sizeof(LinkNode));
				ptr->m_Next->m_Key = key;
				++totalSize;
				ptr = ptr->m_Next;
				fscanf(fp, "%d", &key);
			}
			ptr->m_Next = NULL;
		}
	}
	printf("totalSize = %d\n", totalSize);

	output = (Key*)malloc(totalSize * sizeof(Key));

	MergeLinkSort(output, totalSize, ptrList, listSize, size);

	for (i=0; i<totalSize; ++i)
		printf("%d\n", output[i]);

	for (i=0; i<size; ++i)
	{
		ptr = ptrList[i];
		while (ptr != NULL)
		{
			qtr = ptr;
			ptr = ptr->m_Next;
			free(qtr);
		}
	}
	free(output);
	return;
}
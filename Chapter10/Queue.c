#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayQueueInitial(ArrayQueuePtr pQ)
{
	pQ->m_head = pQ->m_tail = 0;
	pQ->m_capacity = MAXSIZE;
	pQ->m_cnt = 0;
	pQ->m_array = (DataType *)malloc(MAXSIZE * sizeof(DataType));
}

void ArrayQueueDestruct(ArrayQueuePtr pQ)
{
	free(pQ->m_array);
}

int QueueNext(ArrayQueuePtr pQ, int n)
{
	if (n == pQ->m_capacity-1)
		return 0;
	else
		return ++n;
}

int ArrayQueueEmpty(ArrayQueuePtr pQ)
{
	return (pQ->m_head == pQ->m_tail);
}

int ArrayQueueFull(ArrayQueuePtr pQ)
{
	return (pQ->m_head == QueueNext(pQ, pQ->m_tail));
}

DataType ArrayQueueFront(ArrayQueuePtr pQ)
{
	return *(pQ->m_array + pQ->m_head);
}

void ArrayEnqueue(ArrayQueuePtr pQ, DataType x)
{
	int i, j, size;
	DataType *newArray;
	if (ArrayQueueFull(pQ))
	{
		size = 2*pQ->m_capacity + 1;
		newArray = (DataType *)malloc(size * sizeof(DataType));

		for (i=pQ->m_head, j=0; j<pQ->m_capacity-1; i=QueueNext(pQ, i), ++j)
			newArray[j] = pQ->m_array[i];
		free(pQ->m_array);

		pQ->m_head = 0;
		pQ->m_tail = j;
		pQ->m_capacity = size;
		pQ->m_array = newArray;
	}
	*(pQ->m_array + pQ->m_tail) = x;
	pQ->m_tail = QueueNext(pQ, pQ->m_tail);
	++pQ->m_cnt;
}

DataType ArrayDequeue(ArrayQueuePtr pQ)
{
	DataType data = *(pQ->m_array + pQ->m_head);
	pQ->m_head = QueueNext(pQ, pQ->m_head);
	--pQ->m_cnt;
	return data;
}

void TestArrayQueue()
{
	DataType x;
	ArrayQueuePtr ptr;
	ptr = (ArrayQueuePtr)malloc(sizeof(ArrayQueue));

	ArrayQueueInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		ArrayEnqueue(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayQueueEmpty(ptr))
		printf("%d\n", ArrayDequeue(ptr));

	ArrayQueueDestruct(ptr);
	free(ptr);
}

void LinkQueueInitial(LinkQueuePtr pQ)
{
	LinkListInitial(pQ);
}

void LinkQueueDestruct(LinkQueuePtr pQ)
{
	LinkListDestruct(pQ);
}

int LinkQueueEmpty(LinkQueuePtr pQ)
{
	return (pQ->m_count==0);
}

DataType LinkQueueFront(LinkQueuePtr pQ)
{
	return pQ->m_head->m_data;
}

void LinkEnqueue(LinkQueuePtr pQ, DataType x)
{
	BackInsertKey(pQ, x);
}

DataType LinkDequeue(LinkQueuePtr pQ)
{
	LinkNodePtr p=pQ->m_head;
	DataType data=p->m_data;
	RemoveLinkNode(pQ, p);
	free(p);
	return data;
}

void TestLinkQueue()
{
	DataType x;
	LinkQueuePtr ptr;
	ptr = (LinkQueuePtr)malloc(sizeof(LinkQueue));

	LinkQueueInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		LinkEnqueue(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!LinkQueueEmpty(ptr))
		printf("%d\n", LinkDequeue(ptr));

	LinkQueueDestruct(ptr);
	free(ptr);
}
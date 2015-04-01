#include "Deque.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayDequeInitial(ArrayDequePtr pD)
{
	pD->m_head = 0;
	pD->m_tail = 1;
	pD->m_capacity = MAXSIZE;
	pD->m_array = (DataType *)malloc(MAXSIZE * sizeof(DataType));
}

void Reallocate(ArrayDequePtr pD, int size)
{
	int i, j;
	DataType *newArray;

	newArray = (DataType *)malloc(size * sizeof(DataType));

	for (i=DequeNext(pD, pD->m_head), j=0;
		j<pD->m_capacity-2; i=DequeNext(pD, i), ++j)
		newArray[j] = pD->m_array[i];
	free(pD->m_array);

	pD->m_capacity = size;
	pD->m_tail = j;
	pD->m_head = DequePrev(pD, 0);
	pD->m_array = newArray;
}

int DequePrev(ArrayDequePtr pD, int n)
{
	if (n==0)
		return pD->m_capacity-1;
	else
		--n;
}

int DequeNext(ArrayDequePtr pD, int n)
{
	if (n==pD->m_capacity-1)
		return 0;
	else
		return ++n;
}

int ArrayDequeEmpty(ArrayDequePtr pD)
{
	return (DequeNext(pD, pD->m_head) == pD->m_tail);
}

int ArrayDequeFull(ArrayDequePtr pD)
{
	return (DequePrev(pD, pD->m_head) == pD->m_tail);
}

DataType ArrayDequeFront(ArrayDequePtr pD)
{
	return pD->m_array[DequeNext(pD, pD->m_head)];
}

DataType ArrayDequeBack(ArrayDequePtr pD)
{
	return pD->m_array[DequePrev(pD, pD->m_tail)];
}

void EndequeFront(ArrayDequePtr pD, DataType x)
{
	int size;
	if (ArrayDequeFull(pD))
	{
		size = 2*pD->m_capacity+3;
		Reallocate(pD, size);
	}
	pD->m_array[pD->m_head] = x;
	pD->m_head = DequePrev(pD, pD->m_head);
}

DataType DedequeFront(ArrayDequePtr pD)
{
	int i = DequeNext(pD, pD->m_head);
	DataType x = pD->m_array[i];
	pD->m_head = i;
	return x;
}

void EndequeBack(ArrayDequePtr pD, DataType x)
{
	int size;
	if (ArrayDequeFull(pD))
	{
		size = 2*pD->m_capacity+3;
		Reallocate(pD, size);
	}
	pD->m_array[pD->m_tail] = x;
	pD->m_tail = DequeNext(pD, pD->m_tail);
}

DataType DedequeBack(ArrayDequePtr pD)
{
	int i = DequePrev(pD, pD->m_tail);
	DataType x = pD->m_array[i];
	pD->m_tail = i;
	return x;
}

void TestArrayDeque()
{
	DataType x;
	ArrayDequePtr ptr;
	ptr = (ArrayDequePtr)malloc(sizeof(ArrayDeque));

	ArrayDequeInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		EndequeBack(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayDequeEmpty(ptr))
		printf("%d\n", DedequeFront(ptr));

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		EndequeFront(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayDequeEmpty(ptr))
		printf("%d\n", DedequeBack(ptr));

	free(ptr->m_array);
	free(ptr);
}
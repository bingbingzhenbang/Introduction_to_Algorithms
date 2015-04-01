#include "StackQueue.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayStackQueueInitial(ArrayStackQueuePtr pSQ)
{
	pSQ->m_first = (ArrayStackPtr)malloc(sizeof(ArrayStack));
	pSQ->m_second = (ArrayStackPtr)malloc(sizeof(ArrayStack));
	ArrayStackInitial(pSQ->m_first);
	ArrayStackInitial(pSQ->m_second);
}

void ArrayStackQueueDestruct(ArrayStackQueuePtr pSQ)
{
	ArrayStackDestruct(pSQ->m_first);
	ArrayStackDestruct(pSQ->m_second);
	free(pSQ->m_first);
	free(pSQ->m_second);
}

int ArrayStackQueueEmpty(ArrayStackQueuePtr pSQ)
{
	return ArrayStackEmpty(pSQ->m_first) && ArrayStackEmpty(pSQ->m_second);
}

DataType ArrayStackQueueFront(ArrayStackQueuePtr pSQ)
{
	DataType x;
	if (ArrayStackEmpty(pSQ->m_second))
	{
		while (!ArrayStackEmpty(pSQ->m_first))
		{
			x = ArrayStackPop(pSQ->m_first);
			ArrayStackPush(pSQ->m_second, x);
		}
	}
	return ArrayStackTop(pSQ->m_second);
}

void ArrayStackQueueEnqueue(ArrayStackQueuePtr pSQ, DataType x)
{
	ArrayStackPush(pSQ->m_first, x);
}

DataType ArrayStackQueueDequeue(ArrayStackQueuePtr pSQ)
{
	DataType x, y;
	if (ArrayStackEmpty(pSQ->m_second))
	{
		while (!ArrayStackEmpty(pSQ->m_first))
		{
			x = ArrayStackPop(pSQ->m_first);
			ArrayStackPush(pSQ->m_second, x);
		}
	}
	y = ArrayStackPop(pSQ->m_second);
	while (!ArrayStackEmpty(pSQ->m_second))
	{
		x = ArrayStackPop(pSQ->m_second);
		ArrayStackPush(pSQ->m_first, x);
	}
	return y;
}

void TestStackQueue()
{
	DataType x;
	ArrayStackQueuePtr ptr;
	ptr = (ArrayStackQueuePtr)malloc(sizeof(ArrayStackQueue));

	ArrayStackQueueInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		ArrayStackQueueEnqueue(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayStackQueueEmpty(ptr))
		printf("%d\n", ArrayStackQueueDequeue(ptr));

	ArrayStackQueueDestruct(ptr);
	free(ptr);
}
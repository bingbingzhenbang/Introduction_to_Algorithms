#include "QueueStack.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayQueueStackInitial(ArrayQueueStackPtr pQS)
{
	pQS->m_top = 1;
	pQS->m_queue[0] = (ArrayQueuePtr)malloc(sizeof(ArrayQueue));
	pQS->m_queue[1] = (ArrayQueuePtr)malloc(sizeof(ArrayQueue));
	ArrayQueueInitial(pQS->m_queue[0]);
	ArrayQueueInitial(pQS->m_queue[1]);
}

void ArrayQueueStackDestruct(ArrayQueueStackPtr pQS)
{
	ArrayQueueDestruct(pQS->m_queue[0]);
	ArrayQueueDestruct(pQS->m_queue[1]);
	free(pQS->m_queue[0]);
	free(pQS->m_queue[1]);
}

int ArrayQueueStackEmpty(ArrayQueueStackPtr pQS)
{
	return ArrayQueueEmpty(pQS->m_queue[0]) && ArrayQueueEmpty(pQS->m_queue[1]);
}

DataType ArrayQueueStackTop(ArrayQueueStackPtr pQS)
{
	return ArrayQueueFront(pQS->m_queue[pQS->m_top]);
}

DataType ArrayQueueStackPop(ArrayQueueStackPtr pQS)
{
	DataType x = ArrayDequeue(pQS->m_queue[pQS->m_top]);
	
	while (pQS->m_queue[1-pQS->m_top]->m_cnt > 1)
		ArrayEnqueue(pQS->m_queue[pQS->m_top], ArrayDequeue(pQS->m_queue[1-pQS->m_top]));

	pQS->m_top = 1-pQS->m_top;
	return x;
}

void ArrayQueueStackPush(ArrayQueueStackPtr pQS, DataType x)
{
	if (!ArrayQueueEmpty(pQS->m_queue[pQS->m_top]))
		ArrayEnqueue(pQS->m_queue[1-pQS->m_top], ArrayDequeue(pQS->m_queue[pQS->m_top]));
	ArrayEnqueue(pQS->m_queue[pQS->m_top], x);
}

void TestQueueStack()
{
	DataType x;
	ArrayQueueStackPtr ptr;
	ptr = (ArrayQueueStackPtr)malloc(sizeof(ArrayQueueStack));

	ArrayQueueStackInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		ArrayQueueStackPush(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayQueueStackEmpty(ptr))
		printf("%d\n", ArrayQueueStackPop(ptr));

	ArrayQueueStackDestruct(ptr);
	free(ptr);
}
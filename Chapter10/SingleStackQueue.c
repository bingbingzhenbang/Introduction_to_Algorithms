#include "SingleStackQueue.h"
#include <stdio.h>
#include <stdlib.h>

void SingleStackQueueInitial(SingleStackQueuePtr pSQ)
{
	ArrayStackInitial(pSQ);
}

void SingleStackQueueDestruct(SingleStackQueuePtr pSQ)
{
	ArrayStackDestruct(pSQ);
}

int SingleStackQueueEmpty(SingleStackQueuePtr pSQ)
{
	return ArrayStackEmpty(pSQ);
}

DataType SingleStackQueueFront(SingleStackQueuePtr pSQ)
{
	return ArrayStackTop(pSQ);
}

void SingleStackQueueEnqueue(SingleStackQueuePtr pSQ, DataType x)
{
	if (!SingleStackQueueEmpty(pSQ))
	{
		DataType data = ArrayStackPop(pSQ);
		SingleStackQueueEnqueue(pSQ, x);
		ArrayStackPush(pSQ, data);
	}
	else
		ArrayStackPush(pSQ, x);
}

DataType SingleStackQueueDequeue(SingleStackQueuePtr pSQ)
{
	return ArrayStackPop(pSQ);
}

void TestSingleStackQueue()
{
	DataType x;
	SingleStackQueuePtr ptr;
	ptr = (SingleStackQueuePtr)malloc(sizeof(SingleStackQueue));

	SingleStackQueueInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		SingleStackQueueEnqueue(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!SingleStackQueueEmpty(ptr))
		printf("%d\n", SingleStackQueueDequeue(ptr));

	SingleStackQueueDestruct(ptr);
	free(ptr);
}
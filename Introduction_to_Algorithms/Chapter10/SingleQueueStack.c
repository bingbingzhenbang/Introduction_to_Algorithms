#include "SingleQueueStack.h"
#include <stdio.h>
#include <stdlib.h>

void SingleQueueStackInitial(SingleQueueStackPtr pQS)
{
	LinkQueueInitial(pQS);
}

void SingleQueueStackDestruct(SingleQueueStackPtr pQS)
{
	LinkQueueDestruct(pQS);
}

int SingleQueueStackEmpty(SingleQueueStackPtr pQS)
{
	return LinkQueueEmpty(pQS);
}

DataType SingleQueueStackTop(SingleQueueStackPtr pQS)
{
	return LinkQueueFront(pQS);
}

DataType SingleQueueStackPop(SingleQueueStackPtr pQS)
{
	return LinkDequeue(pQS);
}

void SingleQueueStackPush(SingleQueueStackPtr pQS, DataType x)
{
	if (!SingleQueueStackEmpty(pQS))
	{
		LinkListReverse(pQS);
		LinkEnqueue(pQS, x);
		LinkListReverse(pQS);
	}
	else
		LinkEnqueue(pQS, x);
}

void TestSingleQueueStack()
{
	DataType x;
	SingleQueueStackPtr ptr;
	ptr = (SingleQueueStackPtr)malloc(sizeof(SingleQueueStack));

	SingleQueueStackInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		SingleQueueStackPush(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!SingleQueueStackEmpty(ptr))
		printf("%d\n", SingleQueueStackPop(ptr));

	SingleQueueStackDestruct(ptr);
	free(ptr);
}
#ifndef QUEUESTACK_H
#define QUEUESTACK_H

#include "Queue.h"

typedef struct ArrayQueueStack
{
	int m_top;
	ArrayQueuePtr m_queue[2];
}ArrayQueueStack;

typedef ArrayQueueStack* ArrayQueueStackPtr;

void ArrayQueueStackInitial(ArrayQueueStackPtr pQS);
void ArrayQueueStackDestruct(ArrayQueueStackPtr pQS);
int ArrayQueueStackEmpty(ArrayQueueStackPtr pQS);

DataType ArrayQueueStackTop(ArrayQueueStackPtr pQS);
DataType ArrayQueueStackPop(ArrayQueueStackPtr pQS);
void ArrayQueueStackPush(ArrayQueueStackPtr pQS, DataType x);

void TestQueueStack();

#endif // QUEUESTACK_H
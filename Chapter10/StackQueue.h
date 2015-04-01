#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "Stack.h"

typedef struct ArrayStackQueue
{
	ArrayStackPtr m_first;
	ArrayStackPtr m_second;
}ArrayStackQueue;

typedef ArrayStackQueue* ArrayStackQueuePtr;

void ArrayStackQueueInitial(ArrayStackQueuePtr pSQ);
void ArrayStackQueueDestruct(ArrayStackQueuePtr pSQ);
int ArrayStackQueueEmpty(ArrayStackQueuePtr pSQ);

DataType ArrayStackQueueFront(ArrayStackQueuePtr pSQ);
void ArrayStackQueueEnqueue(ArrayStackQueuePtr pSQ, DataType x);
DataType ArrayStackQueueDequeue(ArrayStackQueuePtr pSQ);

void TestStackQueue();

#endif // STACKQUEUE_H
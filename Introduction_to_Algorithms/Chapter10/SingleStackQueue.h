#ifndef SINGLESTACKQUEUE_H
#define SINGLESTACKQUEUE_H

#include "Stack.h"

typedef ArrayStack SingleStackQueue;
typedef ArrayStackPtr SingleStackQueuePtr;

void SingleStackQueueInitial(SingleStackQueuePtr pSQ);
void SingleStackQueueDestruct(SingleStackQueuePtr pSQ);
int SingleStackQueueEmpty(SingleStackQueuePtr pSQ);

DataType SingleStackQueueFront(SingleStackQueuePtr pSQ);
void SingleStackQueueEnqueue(SingleStackQueuePtr pSQ, DataType x);
DataType SingleStackQueueDequeue(SingleStackQueuePtr pSQ);

void TestSingleStackQueue();

#endif // SINGLESTACKQUEUE_H
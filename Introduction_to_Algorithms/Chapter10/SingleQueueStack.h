#ifndef SINGLEQUEUESTACK_H
#define SINGLEQUEUESTACK_H

#include "Queue.h"

typedef LinkQueue SingleQueueStack;
typedef LinkQueuePtr SingleQueueStackPtr;

void SingleQueueStackInitial(SingleQueueStackPtr pQS);
void SingleQueueStackDestruct(SingleQueueStackPtr pQS);
int SingleQueueStackEmpty(SingleQueueStackPtr pQS);

DataType SingleQueueStackTop(SingleQueueStackPtr pQS);
DataType SingleQueueStackPop(SingleQueueStackPtr pQS);
void SingleQueueStackPush(SingleQueueStackPtr pQS, DataType x);

void TestSingleQueueStack();

#endif // SINGLEQUEUESTACK_H
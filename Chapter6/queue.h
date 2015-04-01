#ifndef QUEUE_H
#define QUEUE_H

#include "PQueue.h"

typedef Value Element;
typedef PQueue Queue;

void EnQueue(Queue *que, Element x);
Element DeQueue(Queue *que);

void TestQueue();

#endif // QUEUE_H
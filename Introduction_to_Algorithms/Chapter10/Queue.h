#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

typedef struct ArrayQueue
{
	int m_head;
	int m_tail;
	int m_capacity;
	int m_cnt;
	DataType *m_array;
}ArrayQueue;

typedef ArrayQueue* ArrayQueuePtr;
typedef LinkList LinkQueue;
typedef LinkListPtr LinkQueuePtr;

void ArrayQueueInitial(ArrayQueuePtr pQ);
void ArrayQueueDestruct(ArrayQueuePtr pQ);
int QueueNext(ArrayQueuePtr pQ, int n);
int ArrayQueueEmpty(ArrayQueuePtr pQ);
int ArrayQueueFull(ArrayQueuePtr pQ);
DataType ArrayQueueFront(ArrayQueuePtr pQ);
void ArrayEnqueue(ArrayQueuePtr pQ, DataType x);
DataType ArrayDequeue(ArrayQueuePtr pQ);

void TestArrayQueue();

void LinkQueueInitial(LinkQueuePtr pQ);
void LinkQueueDestruct(LinkQueuePtr pQ);
int LinkQueueEmpty(LinkQueuePtr pQ);
DataType LinkQueueFront(LinkQueuePtr pQ);
void LinkEnqueue(LinkQueuePtr pQ, DataType x);
DataType LinkDequeue(LinkQueuePtr pQ);

void TestLinkQueue();

#endif // QUEUE_H
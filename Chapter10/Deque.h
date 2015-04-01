#ifndef DEQUE_H
#define DEQUE_H

#include "LinkedList.h"

typedef struct ArrayDeque
{
	int m_head;
	int m_tail;
	int m_capacity;
	DataType *m_array;
}ArrayDeque;

typedef ArrayDeque* ArrayDequePtr;

void ArrayDequeInitial(ArrayDequePtr pD);
void Reallocate(ArrayDequePtr pD, int size);

int DequePrev(ArrayDequePtr pD, int n);
int DequeNext(ArrayDequePtr pD, int n);

int ArrayDequeEmpty(ArrayDequePtr pD);
int ArrayDequeFull(ArrayDequePtr pD);

DataType ArrayDequeFront(ArrayDequePtr pD);
DataType ArrayDequeBack(ArrayDequePtr pD);

void EndequeFront(ArrayDequePtr pD, DataType x);
DataType DedequeFront(ArrayDequePtr pD);

void EndequeBack(ArrayDequePtr pD, DataType x);
DataType DedequeBack(ArrayDequePtr pD);

void TestArrayDeque();

#endif // DEQUE_H
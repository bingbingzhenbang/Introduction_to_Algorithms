#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

typedef struct ArrayStack
{
	int m_top;
	int m_capacity;
	DataType *m_array;
}ArrayStack;

typedef ArrayStack* ArrayStackPtr;
typedef LinkList LinkStack;
typedef LinkListPtr LinkStackPtr;

void ArrayStackInitial(ArrayStackPtr pS);
void ArrayStackDestruct(ArrayStackPtr pS);
int ArrayStackEmpty(ArrayStackPtr pS);
DataType ArrayStackTop(ArrayStackPtr pS);
DataType ArrayStackPop(ArrayStackPtr pS);
void ArrayStackPush(ArrayStackPtr pS, DataType x);

void TestArrayStack();

void LinkStackInitial(LinkStackPtr pS);
void LinkStackDestruct(LinkStackPtr pS);
int LinkStackEmpty(LinkStackPtr pS);
DataType LinkStackTop(LinkStackPtr pS);
DataType LinkStackPop(LinkStackPtr pS);
void LinkStackPush(LinkStackPtr pS, DataType x);

void TestLinkStack();

#endif // STACK_H
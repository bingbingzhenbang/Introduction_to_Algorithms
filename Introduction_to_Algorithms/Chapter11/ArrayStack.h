#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "HashDef.h"

#define DEFAULTSIZE 5

typedef struct ArrayStack
{
	int m_top;
	int m_capacity;
	KeyType *m_array;
}ArrayStack;

typedef ArrayStack* ArrayStackPtr;

void ArrayStackInitial(ArrayStackPtr pS);
void ArrayStackDestruct(ArrayStackPtr pS);
int ArrayStackEmpty(ArrayStackPtr pS);
KeyType ArrayStackTop(ArrayStackPtr pS);
KeyType ArrayStackPop(ArrayStackPtr pS);
void ArrayStackPush(ArrayStackPtr pS, KeyType x);

#endif // ARRAYSTACK_H
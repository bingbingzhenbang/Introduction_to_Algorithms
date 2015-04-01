#ifndef STACK_H
#define STACK_H

#include "PQueue.h"

typedef Value Element;
typedef PQueue Stack;

void Push(Stack *st, Element x);
Element Pop(Stack *st);

void TestStack();

#endif // STACK_H
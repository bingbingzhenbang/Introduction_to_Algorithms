#include "ArrayStack.h"
#include <stdlib.h>

void ArrayStackInitial(ArrayStackPtr pS)
{
	pS->m_top = -1;
	pS->m_capacity = DEFAULTSIZE;
	pS->m_array = (KeyType *)malloc(DEFAULTSIZE * sizeof(KeyType));
}

void ArrayStackDestruct(ArrayStackPtr pS)
{
	free(pS->m_array);
}

int ArrayStackEmpty(ArrayStackPtr pS)
{
	return (pS->m_top == -1);
}

KeyType ArrayStackTop(ArrayStackPtr pS)
{
	return pS->m_array[pS->m_top];
}

KeyType ArrayStackPop(ArrayStackPtr pS)
{
	return pS->m_array[pS->m_top--];
}

void ArrayStackPush(ArrayStackPtr pS, KeyType x)
{
	int i, size;
	KeyType *newArray;
	if (pS->m_top == pS->m_capacity-1)
	{
		size = 2*pS->m_capacity+1;
		newArray = (KeyType *)malloc(size * sizeof(KeyType));

		for (i=0; i<=pS->m_top; ++i)
			newArray[i] = pS->m_array[i];

		free(pS->m_array);
		pS->m_array = newArray;
		pS->m_capacity = size;
	}
	pS->m_array[++pS->m_top] = x;
}
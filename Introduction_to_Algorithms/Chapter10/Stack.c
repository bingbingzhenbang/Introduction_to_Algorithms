#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayStackInitial(ArrayStackPtr pS)
{
	pS->m_top = -1;
	pS->m_capacity = MAXSIZE;
	pS->m_array = (DataType *)malloc(MAXSIZE * sizeof(DataType));
}

void ArrayStackDestruct(ArrayStackPtr pS)
{
	free(pS->m_array);
}

int ArrayStackEmpty(ArrayStackPtr pS)
{
	return (pS->m_top == -1);
}

DataType ArrayStackTop(ArrayStackPtr pS)
{
	return pS->m_array[pS->m_top];
}

DataType ArrayStackPop(ArrayStackPtr pS)
{
	return pS->m_array[pS->m_top--];
}

void ArrayStackPush(ArrayStackPtr pS, DataType x)
{
	int i, size;
	DataType *newArray;
	if (pS->m_top == pS->m_capacity-1)
	{
		size = 2*pS->m_capacity+1;
		newArray = (DataType *)malloc(size * sizeof(DataType));

		for (i=0; i<=pS->m_top; ++i)
			newArray[i] = pS->m_array[i];

		free(pS->m_array);
		pS->m_array = newArray;
		pS->m_capacity = size;
	}
	pS->m_array[++pS->m_top] = x;
}

void TestArrayStack()
{
	DataType x;
	ArrayStackPtr ptr;
	ptr = (ArrayStackPtr)malloc(sizeof(ArrayStack));

	ArrayStackInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		ArrayStackPush(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!ArrayStackEmpty(ptr))
		printf("%d\n", ArrayStackPop(ptr));

	ArrayStackDestruct(ptr);
	free(ptr);
}

void LinkStackInitial(LinkStackPtr pS)
{
	LinkListInitial(pS);
}

void LinkStackDestruct(LinkStackPtr pS)
{
	LinkListDestruct(pS);
}

int LinkStackEmpty(LinkStackPtr pS)
{
	return (pS->m_count==0);
}

DataType LinkStackTop(LinkStackPtr pS)
{
	return pS->m_head->m_data;
}

DataType LinkStackPop(LinkStackPtr pS)
{
	LinkNodePtr p=pS->m_head;
	DataType data=p->m_data;
	RemoveLinkNode(pS, p);
	free(p);
	return data;
}

void LinkStackPush(LinkStackPtr pS, DataType x)
{
	FrontInsertKey(pS, x);
}

void TestLinkStack()
{
	DataType x;
	LinkStackPtr ptr;
	ptr = (LinkStackPtr)malloc(sizeof(LinkStack));

	LinkStackInitial(ptr);

	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		LinkStackPush(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	while (!LinkStackEmpty(ptr))
		printf("%d\n", LinkStackPop(ptr));

	LinkStackDestruct(ptr);
	free(ptr);
}
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Push(Stack *st, Element x)
{
	static int p = 0;
	DataType data;
	data.m_key = p;
	data.m_value = x;
	InsertItem(st, data);
	++p;
}

Element Pop(Stack *st)
{
	return PopTop(st).m_value;
}

void TestStack()
{
	time_t t;
	Stack st;
	int i;
	Element data; 
	Initial(&st, 0);
	srand((unsigned)time(&t));

	printf("in:\n");

	for (i=0; i<10; ++i)
	{
		data = rand();
		Push(&st, data);
		printf("%dth in %d\n", i, data);
	}

	printf("out:\n");

	for (i=0; i<10; ++i)
	{
		data = Pop(&st);
		printf("%dth out %d\n", i, data);
	}
}
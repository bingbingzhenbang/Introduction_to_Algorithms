#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void EnQueue(Queue *que, Element x)
{
	static int p = INT_MAX;
	DataType data;
	data.m_key = p;
	data.m_value = x;
	InsertItem(que, data);
	--p;
}

Element DeQueue(Queue *que)
{
	return PopTop(que).m_value;
}

void TestQueue()
{
	time_t t;
	Queue que;
	int i;
	Element data; 
	Initial(&que, 0);
	srand((unsigned)time(&t));

	printf("in:\n");

	for (i=0; i<10; ++i)
	{
		data = rand();
		EnQueue(&que, data);
		printf("%dth in %d\n", i, data);
	}

	printf("out:\n");

	for (i=0; i<10; ++i)
	{
		data = DeQueue(&que);
		printf("%dth out %d\n", i, data);
	}
}
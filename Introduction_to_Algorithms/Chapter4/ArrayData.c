#include "CheckArray.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static int Avoid;
static int Array[MAXNUM];

void Initial()
{
	int i;

	Avoid = (double)rand()/RAND_MAX * MAXNUM;

	for (i=0; i<Avoid; ++i)
		Array[i] = i;

	for (i=Avoid; i<MAXNUM; ++i)
		Array[i] = i+1;
}

int FindDataBit(int i, int j)
{
	return ((Array[i] >> j) & 1);
}

void PrintArrayData()
{
	int i;
	printf("Array data:\n");
	for (i=0; i<MAXNUM;)
		printf("%d\n", Array[i++]);
}

int Answer()
{
	return Avoid;
}
#include "Random.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int RandomSearch(int *array, int size, int key)
{
	int pos = -1, randPos, searchedPos = 0, i = 0;
	int *searched;

	searched = (int *)malloc(size * sizeof(int));
	for (i=0; i<size; ++i)
		*(searched + i) = 0;

	while (searchedPos < size)
	{
		randPos = (double)rand()/RAND_MAX * (size - 1);

		if (array[randPos] == key)
		{
			pos = randPos;
			break;
		}
		else if (!searched[randPos])
		{
			searched[randPos] = 1;
			++searchedPos;
		}
	}

	return pos;
}

void TestRandomSearch()
{
	time_t t;
	int *array, size, i, key = 0, pos;
	FILE *fp;

	srand((unsigned)time(&t));

	fp = fopen("input", "r");
	if (!fp)
	{
		printf("cannot open input file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	array = (int*)malloc(size * sizeof (int));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", array+i);
	fclose(fp);

	printf("input key:\n");
	scanf("%d", &key);

	while (key != -1)
	{
		pos = RandomSearch(array, size, key);
		if (pos == -1)
			printf("fail to find %d\n", key);
		else
			printf("pos = %d\n", pos);

		printf("input key:\n");
		scanf("%d", &key);
	}
}



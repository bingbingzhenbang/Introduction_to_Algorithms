#include "WaterJug.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SwapJug(Jug *a, Jug *b)
{
	Jug temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

void WaterJugPair(Jug *red, Jug *blue, int begin, int end)
{
	int i, j, p, q, mid;
	if (end - begin >= 1)
	{
		p = begin + (double)rand()/RAND_MAX * (end - begin);

		for (i=begin; i<=end; ++i)
		{
			if (blue[i].m_value == red[p].m_value)
			{
				q = i;
				break;
			}
		}

		SwapJug(&red[p], &red[end]);
		SwapJug(&blue[q], &blue[end]);

		for (i=begin-1, j=begin; j<=end-1; ++j)
		{
			if (red[j].m_value < blue[end].m_value)
				SwapJug(&red[++i], &red[j]);
		}
		SwapJug(&red[++i], &red[end]);
		mid = i;

		for (i=begin-1, j=begin; j<=end-1; ++j)
		{
			if (blue[j].m_value < red[mid].m_value)
			{
				SwapJug(&blue[++i], &blue[j]);
			}
		}
		SwapJug(&blue[++i], &blue[end]);
		mid = i;

		WaterJugPair(red, blue, begin, mid-1);
		WaterJugPair(red, blue, mid+1, end);
	}
}

void DeterminWaterJugPair(Jug *redJugs, Jug *blueJugs, int size)
{
	int i, j;
	Jug temp;
	for (i=0; i<size; ++i)
	{
		for (j=0; j<size; ++j)
		{
			if (blueJugs[j].m_value == redJugs[i].m_value)
			{
				SwapJug(&blueJugs[i], &blueJugs[j]);
				break;
			}
		}
	}
}

void TestWaterJug()
{
	int i, j, temp, size;
	int *redValues, *blueValues;
	Jug *redJugs, *blueJugs;
	time_t t;

	srand((unsigned)time(&t));

	printf("Test water jug problem!\ninput jugs number!\n");
	scanf("%d", &size);

	redValues = (int*)malloc(size * sizeof(int));
	blueValues = (int*)malloc(size * sizeof(int));
	redJugs = (Jug*)malloc(size * sizeof(Jug));
	blueJugs = (Jug*)malloc(size * sizeof(Jug));

	for (i=0; i<size; ++i)
		redValues[i] = blueValues[i] = i+1;
	
	for (i=0; i<size; ++i)
	{
		j = i + (double)rand()/RAND_MAX * (size - 1 - i);
		temp = redValues[j];
		redValues[j] = redValues[i];
		redValues[i] = temp;
	}

	for (i=0; i<size; ++i)
	{
		j = i + (double)rand()/RAND_MAX * (size - 1 - i);
		temp = blueValues[j];
		blueValues[j] = blueValues[i];
		blueValues[i] = temp;
	}

	for (i=0; i<size; ++i)
	{
		redJugs[i].m_index = blueJugs[i].m_index = i+1;
		redJugs[i].m_value = redValues[i];
		blueJugs[i].m_value = blueValues[i];
	}

	//DeterminWaterJugPair(redJugs, blueJugs, size);
	WaterJugPair(redJugs, blueJugs, 0, size-1);

	printf("Determin pair:\n");
	for (i=0; i<size; ++i)
		printf("red: Index =%3d Value =%3d\tblue: Index =%3d Value =%3d\n", redJugs[i].m_index, redJugs[i].m_value, blueJugs[i].m_index, blueJugs[i].m_value);

	free(redJugs);
	free(blueJugs);
	free(redValues);
	free(blueValues);
}
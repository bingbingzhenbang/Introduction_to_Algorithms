#ifndef WATERJUG_H
#define WATERJUG_H

typedef struct  
{
	int m_index;
	int m_value;
}Jug;

void SwapJug(Jug *a, Jug *b);

void WaterJugPair(Jug *red, Jug *blue, int begin, int end);

void DeterminWaterJugPair(Jug *redJugs, Jug *blueJugs, int size);

void TestWaterJug();

#endif // WATERJUG_H
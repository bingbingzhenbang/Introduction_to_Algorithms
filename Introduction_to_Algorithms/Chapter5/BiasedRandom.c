#include "Random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double Probable = 0.3;
static int Lower = 0;
static int Upper = 1000;
static int TestMax = 50000;

int BiasedRandom(double p)
{
	int bound, number;


	bound = Lower + p * (Upper - Lower);

	number = Lower + (double)rand()/RAND_MAX * (Upper - Lower);

	if (number <= bound)
		return 1;
	else
		return 0;
}

int ModifyBiasedRandom()
{
	int x, y;

	while (1)
	{
		x = BiasedRandom(Probable);
		y = BiasedRandom(Probable);
		if (x != y)
			return x;
	}
	return 0;
}

void TestModifyBiasedRandom()
{
	time_t t;
	int i, B1, B0, M1, M0;
	int Bresult, Mresult;
	srand((unsigned)time(&t));
	B1 = B0 = M1 = M0 = 0;
	for (i=0; i<TestMax; ++i)
	{
		Bresult = BiasedRandom(Probable);
		Mresult = ModifyBiasedRandom();

		(Bresult == 1) ? ++B1 : ++B0;
		(Mresult == 1) ? ++M1 : ++M0;
	}
	printf("in total %d test\n Biased Proba %f\n", TestMax, Probable);
	printf("Biased Random\n 1: %d\n 0: %d\n 1: proba: %f\n 0: proba: %f\n", B1, B0, (double)B1/TestMax, (double)B0/TestMax);
	printf("Modify\n 1: %d\n 0: %d\n 1: proba: %f\n 0: proba: %f\n", M1, M0, (double)M1/TestMax, (double)M0/TestMax);
}
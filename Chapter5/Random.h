#ifndef RANDOM_H
#define RANDOM_H

#define MAXNUM 100

int BiasedRandom(double p);
int ModifyBiasedRandom();
void TestModifyBiasedRandom();

void InitialArray(int size);

void PowerRandomSort();
void TestPowerRandomSort(int size);

void RandomInPlace();
void TestRandomInPlace(int size);

int RandomSearch(int *array, int size, int key);
void TestRandomSearch();

#endif // RANDOM_H
#ifndef LINEARTIMESORT_H
#define LINEARTIMESORT_H

typedef int ElementType;

void CountingSort(ElementType *outputArray, ElementType *inputArray, int size);

void InplaceCountingSort(ElementType *array, int size);

void TestLinearTimeSort();

#endif // LINEARTIMESORT_H
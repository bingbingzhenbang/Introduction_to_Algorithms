#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "LinearTimeSort.h"

void BitsSort(ElementType *array, int *bitsArray, int size);

/// compare each set of r bits in pBase notation
void RadixSort(ElementType *array, int size, int r, int pBase);

void TestRadixSort();

#endif // RADIXSORT_H
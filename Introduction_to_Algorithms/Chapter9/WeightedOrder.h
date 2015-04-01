#ifndef WEIGHTEDORDER_H
#define WEIGHTEDORDER_H

#include "Order.h"

#define ERROR (1e-10)

typedef double Weight;

typedef struct 
{
	DataType m_Value;
	Weight m_Weight;
}WeightData;

void SwapWeight(WeightData *w1, WeightData *w2);

int WeightedPartion(WeightData *array, int begin, int end);

void WeightedInsertSort(WeightData *array, int begin, int end);

WeightData WeightedSelect(int *selectedIndex, WeightData *array, int begin, int end, int nth);

WeightData WeightedValueMedian(int *selectedIndex, WeightData *array, int begin, int end);

WeightData WeightedMedian(WeightData *array, int begin, int end, double WL, double WR);

void TestWeightMedian();

#endif // WEIGHTEDORDER_H
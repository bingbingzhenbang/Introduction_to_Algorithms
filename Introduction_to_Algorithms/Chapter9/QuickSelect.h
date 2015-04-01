#ifndef QUICKSELECT_H
#define QUICKSELECT_H

#include "Order.h"

int AdditionalPartion(DataType *array, int begin, int end, int dis);

void AdditionalInsertSort(DataType *array, int begin, int end, int dis);

DataType AdditionalSelect(DataType *array, int begin, int end, int nth, int dis);

DataType QuickSelect(DataType *array, int begin, int end, int nth);

void TestQuickSelect();

#endif // QUICKSELECT_H
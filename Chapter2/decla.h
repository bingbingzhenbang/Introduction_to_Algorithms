#ifndef DECLA_H
#define DECLA_H

#define ITEMMAX INT_MAX

typedef int Item;


void InsertSort(Item *array, int size);
void RecurInsertSort(Item *array, int p, int q);

void SelectSort(Item *array, int size);
void MergeSort(Item *array, int size);
void BubbleSort(Item *array, int size);

int InversionTest(Item *array, int size);
int InversionCount(Item *array, int p, int q);

#endif
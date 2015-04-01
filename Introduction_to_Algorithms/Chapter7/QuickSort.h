#ifndef QUICKSORT_H
#define QUICKSORT_H

typedef int ElementType;

typedef struct
{
	ElementType m_Left;
	ElementType m_Right;
}Interval;

typedef Interval* IntervalPtr;

typedef struct 
{
	int m_i;
	int m_j;
}Divid;

void Swap(ElementType *d1, ElementType *d2);

void SwapInterval(IntervalPtr *ptr1, IntervalPtr *ptr2);

int Partion(ElementType *array, int begin, int end);

void QuickSort(ElementType *array, int begin, int end);

int RandomPartion(ElementType *array, int begin, int end);

void RandomQuickSort(ElementType *array, int begin, int end);

void QuickInsertSort(ElementType *array, int size, int k);

void PartialQuickSort(ElementType *array, int begin, int end, int k);

void InsertSort(ElementType *array, int size);

int HoarePartion(ElementType *array, int begin, int end);

void StoogeSort(ElementType *array, int begin, int end);

void TailQuickSort(ElementType *array, int begin, int end);

int IntervalLess(IntervalPtr ptr1, IntervalPtr ptr2);

int IntervalGreater(IntervalPtr ptr1, IntervalPtr ptr2);

Divid IntervalPartion(IntervalPtr *array, int begin, int end);

void IntervalSort(IntervalPtr *array, int begin, int end);

void TestPartion();

void TestQuickSort();

void TestIntervalSort();

#endif // QUICKSORT_H
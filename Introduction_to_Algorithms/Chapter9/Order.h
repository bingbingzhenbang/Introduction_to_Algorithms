#ifndef ORDER_H
#define ORDER_H

#define MAX(a, b) (( (a) > (b) ) ? (a) : (b))
#define MIN(a, b) (( (a) < (b) ) ? (a) : (b))

#define LEN 5

typedef int DataType;

typedef struct
{
	DataType m_Min;
	DataType m_Max;
}MPair;

typedef struct
{
	DataType m_Value;
	int m_PrevIndex;
	int m_DefeatedIndex;
}CompareNode;

typedef CompareNode* CompareNodePtr;

void Swap(DataType *d1, DataType *d2);

DataType GetMin(DataType *array, int size);
DataType GetMax(DataType *array, int size);

MPair GetMaxAndMin(DataType *array, int size);

void GetMinAndSecdondMin(DataType *array, int size, DataType *min, DataType *secondMin);

void DeterminGetMinAndSecdondMin(DataType *array, int size, DataType *Min, DataType *secondMin);

void EasyGetMinAndSecdondMin(DataType *array, int size, DataType *min, DataType *secondMin);

int Partion(DataType *array, int begin, int end);

int RandomPartion(DataType *array, int begin, int end);

DataType RandomSelect(DataType *array, int begin, int end, int i);

DataType LoopRandomSelect(DataType *array, int begin, int end, int i);

void InsertSort(DataType *array, int begin, int end);

DataType Select(DataType *array, int begin, int end, int nth);

void MidQuickSort(DataType *array, int begin, int end);

DataType GetMid(DataType *array, int begin, int end);

void DeterminKthQuantile(DataType *array, int arraysize, DataType *quantile, int quan);

void KthQuantile(DataType *array, int arraybegin, int arrayend, DataType *quantile, int quanbegin, int quanend, int len);

DataType MergeMid(DataType *X, DataType *Y, int size);

int FindMedian(DataType *X, DataType *Y, int size, int begin, int end);

void TestMaxAndMin();

void TestMinAndSecdondMin();

void TestRandomSelect();

void TestMidQuickSort();

void TestKthQuantile();

void TestMergeMid();

void TestSelect();

#endif // ORDER_H
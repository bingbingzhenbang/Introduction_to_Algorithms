#ifndef PQUEUE_H
#define PQUEUE_H

#define MAXHEAP 5

#define Parent(i) ( ((i) - 1 ) >> 1 )
#define Left(i)   ( ((i) << 1) | 1 )
#define Right(i)  ( ((i) + 1 ) << 1 )

enum HeapType
{
	Enum_MaxHeap,
	Enum_MinHeap,
	Enum_TypeCount,
};

typedef int Key;
typedef int Value;

typedef struct
{
	Key m_key;
	Value m_value;
}DataType;

typedef int(*Compare)(DataType *, DataType *);

extern Compare CompareFunction[Enum_TypeCount];

typedef struct
{
	int m_Size;
	int m_Capaity;
	int m_HeapType;
	DataType *m_Data;
}PQueue;

int Greater(DataType *d1, DataType *d2);

int Less(DataType *d1, DataType *d2);

void Swap(DataType *d1, DataType *d2);

void Initial(PQueue *ptr, int type);

PQueue* BuildPQueue(DataType *array, int size, Compare compare);

void Heapify(PQueue *ptr, int i, Compare compare);

DataType GetTop(PQueue *ptr);

DataType PopTop(PQueue *ptr);

void IncreaseKey(PQueue *ptr, int i, Key key);

void DecreaseKey(PQueue *ptr, int i, Key key);

void InsertItem(PQueue *ptr, DataType element);

void DestructData(PQueue *ptr);

void DestructPQueue(PQueue *ptr);

void TestPQueue();

#endif // PQUEUE_H
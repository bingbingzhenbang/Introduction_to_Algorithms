#ifndef HEAP_H
#define HEAP_H

#define MAXHEAP 500

#define Parent(i) ( ((i) - 1 ) >> 1 )
#define Left(i)   ( ((i) << 1) | 1 )
#define Right(i)  ( ((i) + 1 ) << 1 )

typedef int ElementType;

typedef struct
{
	int m_Size;
	int m_Capaity;
	ElementType *m_Data;
} Heap;

typedef Heap* HeapPtr;

HeapPtr BuildHeap(ElementType *array, int size);

void MaxHeapify(HeapPtr ptr, int i);

void HeapSort(ElementType *array, int size);

void DestructHeap(HeapPtr ptr);

void TestHeap();

#endif // HEAP_H
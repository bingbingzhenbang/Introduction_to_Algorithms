#ifndef FREELIST_H
#define FREELIST_H

#include "LinkedList.h"

typedef struct FreeList
{
	int m_free;
	int m_capacity;
	int *m_next;
	int *m_prev;
	DataType *m_data;
}FreeList;

extern FreeList FreeListData;

void InitializeFreeList();
int AllocateObject();
void FreeObject(int x);
void DestructFreeList();

typedef struct List 
{
	int m_count;
	int m_head;
	int m_tail;
}List;

typedef List* ListPtr;

void InitialList(ListPtr pL);
int ListSearch(ListPtr pL, DataType key);
void ListPrint(ListPtr pL);
void FrontInsert(ListPtr pL, int x);
void FrontInsertLKey(ListPtr pL, DataType x);
void BackInsert(ListPtr pL, int x);
void BackInsertLKey(ListPtr pL, DataType x);
void ListRemove(ListPtr pL, int x);
void ListRemoveAndFree(ListPtr pL, int x);
void DestructList(ListPtr pL);
void DestructListAndFree(ListPtr pL);
void SwapPointer(int i, int j);
void CompactifyList(ListPtr pL);
void TestFreeList();

#endif // FREELIST_H
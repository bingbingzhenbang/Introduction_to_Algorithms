#include "FreeList.h"
#include <stdio.h>
#include <stdlib.h>

FreeList FreeListData;

void InitializeFreeList()
{
	int i;
	FreeListData.m_free = 0;
	FreeListData.m_capacity = MAXSIZE;
	FreeListData.m_next = (int*)malloc(MAXSIZE * sizeof(int));
	FreeListData.m_prev = (int*)malloc(MAXSIZE * sizeof(int));
	FreeListData.m_data = (DataType*)malloc(MAXSIZE * sizeof(DataType));

	for (i=0; i<MAXSIZE-1; ++i)
		FreeListData.m_next[i] = i+1;
	FreeListData.m_next[MAXSIZE-1] = -1;
}

int AllocateObject()
{
	int i, next, newCap, *newNext, *newPrev;
	DataType *newData;

	if (FreeListData.m_free == -1)
	{
		newCap = 2 * FreeListData.m_capacity + 1;
		newNext = (int*)malloc(newCap * sizeof(int));
		newPrev = (int*)malloc(newCap * sizeof(int));
		newData = (DataType *)malloc(newCap * sizeof(DataType));

		for (i=0; i<FreeListData.m_capacity; ++i)
		{
			newNext[i] = FreeListData.m_next[i];
			newPrev[i] = FreeListData.m_prev[i];
			newData[i] = FreeListData.m_data[i];
		}
		for (i=FreeListData.m_capacity; i<newCap-1; ++i)
			newNext[i] = i+1;
		newNext[newCap-1] = -1;
		free(FreeListData.m_next);
		free(FreeListData.m_prev);
		free(FreeListData.m_data);
		FreeListData.m_next = newNext;
		FreeListData.m_prev = newPrev;
		FreeListData.m_data = newData;

		FreeListData.m_free = FreeListData.m_capacity;
		FreeListData.m_capacity = newCap;
	}
	next = FreeListData.m_free;
	FreeListData.m_free = FreeListData.m_next[next];

	return next;
}

void FreeObject(int x)
{
	if (x>=0 && x<FreeListData.m_capacity)
	{
		FreeListData.m_next[x] = FreeListData.m_free;
		FreeListData.m_free = x;
	}
}

void DestructFreeList()
{
	FreeListData.m_free = -1;
	FreeListData.m_capacity = 0;
	if (FreeListData.m_next)
		free(FreeListData.m_next);
	if (FreeListData.m_prev)
		free(FreeListData.m_prev);
	if (FreeListData.m_data)
		free(FreeListData.m_data);
}

void InitialList(ListPtr pL)
{
	pL->m_count = 0;
	pL->m_head = -1;
	pL->m_tail = -1;
}

int ListSearch(ListPtr pL, DataType key)
{
	int x;
	for (x=pL->m_head; x!=-1 && FreeListData.m_data[x]!=key; 
		x=FreeListData.m_next[x])
		;
	return x;
}

void ListPrint(ListPtr pL)
{
	int x;
	for (x=pL->m_head; x!=-1;
		x=FreeListData.m_next[x])
		printf("%d\n", FreeListData.m_data[x]);
}

void FrontInsert(ListPtr pL, int x)
{
	FreeListData.m_next[x] = pL->m_head;
	if (pL->m_head != -1)
		FreeListData.m_prev[pL->m_head] = x;
	FreeListData.m_prev[x] = -1;
	pL->m_head = x;
	++pL->m_count;
	if (pL->m_count==1)
		pL->m_tail = x;
}

void FrontInsertLKey(ListPtr pL, DataType key)
{
	int x;
	x = AllocateObject();
	FreeListData.m_data[x] = key;
	FrontInsert(pL, x);
}

void BackInsert(ListPtr pL, int x)
{
	if (pL->m_tail != -1)
		FreeListData.m_next[pL->m_tail] = x;
	FreeListData.m_prev[x] = pL->m_tail;
	FreeListData.m_next[x] = -1;
	pL->m_tail = x;
	++pL->m_count;
	if (pL->m_count == 1)
		pL->m_head = x;
}

void BackInsertLKey(ListPtr pL, DataType key)
{
	int x;
	x = AllocateObject();
	FreeListData.m_data[x] = key;
	BackInsert(pL, x);
}

void ListRemove(ListPtr pL, int x)
{
	if (x==pL->m_head)
		pL->m_head = FreeListData.m_next[pL->m_head];
	if (x==pL->m_tail)
		pL->m_tail = FreeListData.m_prev[pL->m_tail];

	if (FreeListData.m_prev[x] != -1)
		FreeListData.m_next[FreeListData.m_prev[x]] = FreeListData.m_next[x];
	if (FreeListData.m_next[x] != -1)
		FreeListData.m_prev[FreeListData.m_next[x]] = FreeListData.m_prev[x];

	--pL->m_count;
}

void ListRemoveAndFree(ListPtr pL, int x)
{
	int y;
	if (x>=0 && x<FreeListData.m_capacity)
	{
		y = FreeListData.m_free-1;
		if (x==FreeListData.m_free-1)
		{
			ListRemove(pL, x);
		}
		else
		{
			//Remove the Node
			if (x==pL->m_head)
				pL->m_head = FreeListData.m_next[pL->m_head];
			if (x==pL->m_tail)
				pL->m_tail = FreeListData.m_prev[pL->m_tail];

			if (FreeListData.m_prev[x] != -1)
				FreeListData.m_next[FreeListData.m_prev[x]] = FreeListData.m_next[x];
			if (FreeListData.m_next[x] != -1)
				FreeListData.m_prev[FreeListData.m_next[x]] = FreeListData.m_prev[x];

			FreeListData.m_data[x] = FreeListData.m_data[y];
			FreeListData.m_prev[x] = FreeListData.m_prev[y];
			FreeListData.m_next[x] = FreeListData.m_next[y];

			if (FreeListData.m_prev[x] != -1)
				FreeListData.m_next[FreeListData.m_prev[x]] = x;
			if (FreeListData.m_next[x] != -1)
				FreeListData.m_prev[FreeListData.m_next[x]] = x;

			if (y==pL->m_head)
				pL->m_head = x;
			if (y==pL->m_tail)
				pL->m_tail = x;

			--pL->m_count;
		}
		FreeListData.m_next[y] = y+1;
		--FreeListData.m_free;
	}
}

void DestructList(ListPtr pL)
{
	int p, q;
	for (p=pL->m_head; p!=-1; p=q)
	{
		q=FreeListData.m_next[p];
		FreeObject(p);
	}
	pL->m_count = 0;
	pL->m_head = -1;
	pL->m_tail = -1;
}

void DestructListAndFree(ListPtr pL)
{
	int p;
	pL->m_count = 0;
	pL->m_head = -1;
	pL->m_tail = -1;
	for (p=FreeListData.m_free-1; p>=0; --p)
		FreeListData.m_next[p] = p+1;
	FreeListData.m_free = 0;
}

void SwapPointer(int i, int j)
{
	DataType tempData;
	int temp;

	if (FreeListData.m_next[i] != -1)
		FreeListData.m_prev[FreeListData.m_next[i]] = j;

	if (FreeListData.m_prev[i] != -1)
		FreeListData.m_next[FreeListData.m_prev[i]] = j;

	if (FreeListData.m_next[j] != -1)
		FreeListData.m_prev[FreeListData.m_next[j]] = i;

	if (FreeListData.m_prev[j] != -1)
		FreeListData.m_next[FreeListData.m_prev[j]] = i;

	tempData = FreeListData.m_data[i];
	FreeListData.m_data[i] = FreeListData.m_data[j];
	FreeListData.m_data[j] = tempData;

	temp = FreeListData.m_prev[i];
	FreeListData.m_prev[i] = FreeListData.m_prev[j];
	FreeListData.m_prev[j] = temp;

	temp = FreeListData.m_next[i];
	FreeListData.m_next[i] = FreeListData.m_next[j];
	FreeListData.m_next[j] = temp;
}

void CompactifyList(ListPtr pL)
{
	int x, begin=0;
	for (x=pL->m_head; x!=-1; x=FreeListData.m_next[x])
	{
		if (x!=begin)
		{
			SwapPointer(x, begin);
			if (x==pL->m_head)
				pL->m_head = begin;
			if (x==pL->m_tail)
				pL->m_tail = begin;
			++begin;
		}
	}
	FreeListData.m_free = begin;
}

void TestFreeList()
{
	ListPtr lA, lB;
	int key, x;
	InitializeFreeList();
	lA = (ListPtr)malloc(sizeof(List));
	//lB = (ListPtr)malloc(sizeof(List));

	InitialList(lA);
	//InitialList(lB);

	printf("Back insert LA:\n");
	printf("input key\n");
	scanf("%d", &key);
	while (key!=-1)
	{
		BackInsertLKey(lA, key);
		printf("input x\n");
		scanf("%d", &key);
	}

	//printf("Back insert LB:\n");
	//printf("input key\n");
	//scanf("%d", &key);
	//while (key!=-1)
	//{
	//	BackInsertLKey(lB, key);
	//	printf("input x\n");
	//	scanf("%d", &key);
	//}

	printf("Front insert LA:\n");
	printf("input key\n");
	scanf("%d", &key);
	while (key!=-1)
	{
		FrontInsertLKey(lA, key);
		printf("input x\n");
		scanf("%d", &key);
	}

	//printf("Front insert LB:\n");
	//printf("input key\n");
	//scanf("%d", &key);
	//while (key!=-1)
	//{
	//	FrontInsertLKey(lB, key);
	//	printf("input x\n");
	//	scanf("%d", &key);
	//}

	printf("All in LA:\n");
	ListPrint(lA);
	//printf("All in LB:\n");
	//ListPrint(lB);

	printf("input searched key in LA:\n");
	scanf("%d", &key);
	x = ListSearch(lA, key);
	if (x!=-1)
	{
		printf("%d\n", FreeListData.m_data[x]);
		ListRemoveAndFree(lA, x);
		printf("After delete:\n");
		ListPrint(lA);
		printf("m_free:%d\n", FreeListData.m_free);
		printf("Front insert LA:\n");
		printf("input key\n");
		scanf("%d", &key);
		while (key!=-1)
		{
			FrontInsertLKey(lA, key);
			printf("m_free:%d\n", FreeListData.m_free);
			printf("input x\n");
			scanf("%d", &key);
		}
	}
	else
		printf("not found!\n");

	//printf("input searched key in LB:\n");
	//scanf("%d", &key);
	//x = ListSearch(lB, key);
	//if (x!=-1)
	//{
	//	printf("%d\n", FreeListData.m_data[x]);
	//	ListRemove(lB, x);
	//	printf("After delete:\n");
	//	ListPrint(lB);
	//}
	//else
	//	printf("not found!\n");

	DestructListAndFree(lA);
	free(lA);
	//free(lB);
	DestructFreeList();
}
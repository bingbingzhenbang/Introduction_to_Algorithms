#include "DirectTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int KeyToIndex(KeyType key)
{
	return key;
}

void DirectTableInitial(DirectTablePtr ptr)
{
	ptr->m_table = (int *)malloc(DIRECTTABLESIZE * sizeof(int));
	ArrayStackInitial(&ptr->m_stack);
}

void DirectTableDestruct(DirectTablePtr ptr)
{
	free(ptr->m_table);
	ArrayStackDestruct(&ptr->m_stack);
}

int DirectTableSearch(DirectTablePtr ptr, KeyType key, HashFunction pHash)
{
	int index = ptr->m_table[pHash(key)];
	if (!(index>=0 && index<=ptr->m_stack.m_top && ptr->m_stack.m_array[index]==key))
		index = -1;
	return index;
}

int DirectTableInsert(DirectTablePtr ptr, KeyType key, HashFunction pHash)
{
	ArrayStackPush(&ptr->m_stack, key);
	ptr->m_table[pHash(key)] = ptr->m_stack.m_top;
	return ptr->m_stack.m_top;
}

int DirectTableDelete(DirectTablePtr ptr, KeyType key, HashFunction pHash)
{
	int index = DirectTableSearch(ptr, key, pHash);
	if (index != -1)
	{
		if (index != ptr->m_stack.m_top)
		{
			ptr->m_stack.m_array[index] = ptr->m_stack.m_array[ptr->m_stack.m_top];
			ptr->m_table[pHash(ptr->m_stack.m_array[index])] = index;
		}
		ptr->m_table[pHash(key)] = -1;
		--ptr->m_stack.m_top;
	}
	return index;
}

void TestDirectTable()
{
	DirectTable testTable;
	time_t t1;
	KeyType x;
	int i, n=10;
	srand((unsigned)time(&t1));
	DirectTableInitial(&testTable);
	for (i=0; i<n; ++i)
	{
		x = rand() % DIRECTTABLESIZE;
		printf("%d\n", x);
		DirectTableInsert(&testTable, x, KeyToIndex);
	}
	printf("input search key:\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		if (DirectTableSearch(&testTable, x, KeyToIndex) != -1)
		{
			i = DirectTableDelete(&testTable, x, KeyToIndex);
			printf("deleted index = %d\n", i);
		}
		else
			printf("Not found!\n");
		printf("input search key:\n");
		scanf("%d", &x);
	}
	DirectTableDestruct(&testTable);
	return;
}
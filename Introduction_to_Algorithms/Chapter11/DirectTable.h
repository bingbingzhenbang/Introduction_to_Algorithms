#ifndef DIRECTTABLE_H
#define DIRECTTABLE_H

#include "ArrayStack.h"

#define DIRECTTABLESIZE 100000

typedef struct DirectTable
{
	int *m_table;
	ArrayStack m_stack;
}DirectTable;

typedef DirectTable* DirectTablePtr;

int KeyToIndex(KeyType key);

void DirectTableInitial(DirectTablePtr ptr);
void DirectTableDestruct(DirectTablePtr ptr);
int DirectTableSearch(DirectTablePtr ptr, KeyType key, HashFunction pHash);
int DirectTableInsert(DirectTablePtr ptr, KeyType key, HashFunction pHash);
int DirectTableDelete(DirectTablePtr ptr, KeyType key, HashFunction pHash);
void TestDirectTable();

#endif // DIRECTTABLE_H
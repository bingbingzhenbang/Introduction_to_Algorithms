#ifndef SLOTLISTTABLE_H
#define SLOTLISTTABLE_H

#include "HashDef.h"

#define SLOTLISTSIZE 100

typedef struct SlotNode
{
	KeyType m_key;
	int m_flag;      // 0 free, 1 in use
	int m_prev;
	int m_next;
}SlotNode;

int SlotTableFunction(KeyType key);

void TestSlotListTable();

#endif // SLOTLISTTABLE_H
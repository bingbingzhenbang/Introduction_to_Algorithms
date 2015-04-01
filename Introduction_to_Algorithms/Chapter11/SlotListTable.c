#include "SlotListTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SlotTableFunction(KeyType key)
{
	return key % SLOTLISTSIZE;
}

void TestSlotListTable()
{
	printf("Test SlotList Table.\n");
	printf("End.\n");
}
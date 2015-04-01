#ifndef MERGELINKSORT_H
#define MERGELINKSORT_H

#include "PQueue.h"

#define ENDNUM -1

typedef struct LinkNode
{
	Key m_Key;
	struct LinkNode *m_Next;
}LinkNode;

typedef LinkNode* LinkNodePtr;

void MergeLinkSort(Key *outputArray, int totalSize, LinkNodePtr *ptrList, int listSize, int size);

void TestMergeLinkSort();

#endif // MERGELINKSORT_H
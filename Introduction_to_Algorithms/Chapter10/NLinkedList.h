#ifndef NLINKEDLIST_H
#define NLINKEDLIST_H

#include "LinkedList.h"

#define WORDLEN 8

typedef struct NLinkNode
{
	DataType m_data;
	unsigned int m_np : sizeof(struct NLinkNode*) * WORDLEN;
}NLinkNode;
typedef NLinkNode* NLinkNodePtr;

typedef struct NLinkList
{
	int m_count;
	NLinkNodePtr m_head;
	NLinkNodePtr m_tail;
}NLinkList;
typedef NLinkList* NLinkListPtr;

void NLinkListInitial(NLinkListPtr pL);
NLinkNodePtr NLinkSearch(NLinkListPtr pL, DataType key);
void NLinkListPrint(NLinkListPtr pL);

void FrontInsertNLinkNode(NLinkListPtr pL, NLinkNodePtr x);
void FrontInsertNKey(NLinkListPtr pL, DataType key);

void BackInsertNLinkNode(NLinkListPtr pL, NLinkNodePtr x);
void BackInsertNKey(NLinkListPtr pL, DataType key);

void RemoveNLinkNode(NLinkListPtr pL, NLinkNodePtr x);
void NLinkListDestruct(NLinkListPtr pL);

void TestNLinkList();

#endif // NLINKEDLIST_H
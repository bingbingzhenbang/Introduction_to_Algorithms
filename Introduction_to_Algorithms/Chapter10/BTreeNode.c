#include "BTreeNode.h"
#include <stdio.h>
#include <stdlib.h>

void PrintNode(BTreeNodePtr ptr)
{
	printf("key = %3d count = %3d\n", ptr->m_data, ptr->m_count);
}

BTreeNodePtr MakeNode(DataType key)
{
	BTreeNodePtr ptr;
	ptr = (BTreeNodePtr)malloc(sizeof(BTreeNode));
	ptr->m_data = key;
	ptr->m_count = 1;
	ptr->m_parent = 0;
	ptr->m_left = 0;
	ptr->m_right = 0;
	return ptr;
}

void BTreeListInitial(BTreeListPtr pBL)
{
	pBL->m_count = 0;
	pBL->m_head = 0;
	pBL->m_tail = 0;
}

void FrontInsertBTreeNode(BTreeListPtr pBL, BTreeNodePtr ptr)
{
	BTreeListNodePtr x = (BTreeListNodePtr)malloc(sizeof(BTreeListNode));
	x->m_nodePtr = ptr;
	FrontInsertBTreeListNode(pBL, x);
}

void FrontInsertBTreeListNode(BTreeListPtr pBL, BTreeListNodePtr ptr)
{
	ptr->m_next = pBL->m_head;
	pBL->m_head = ptr;
	++pBL->m_count;
	if (pBL->m_count == 1)
		pBL->m_tail = ptr;
}

BTreeListNodePtr FrontRemoveBTreeNode(BTreeListPtr pBL)
{
	BTreeListNodePtr pNL = pBL->m_head;
	pBL->m_head = pNL->m_next;
	--pBL->m_count;
	if (pBL->m_count == 0)
		pBL->m_tail = 0;
	return pNL;
}

void BackInsertBTreeNode(BTreeListPtr pBL, BTreeNodePtr ptr)
{
	BTreeListNodePtr x = (BTreeListNodePtr)malloc(sizeof(BTreeListNode));
	x->m_nodePtr = ptr;
	BackInsertBTreeListNode(pBL, x);
}

void BackInsertBTreeListNode(BTreeListPtr pBL, BTreeListNodePtr ptr)
{
	ptr->m_next = 0;
	if (pBL->m_tail)
		pBL->m_tail->m_next = ptr;
	pBL->m_tail = ptr;
	++pBL->m_count;
	if (pBL->m_count == 1)
		pBL->m_head = ptr;
}

void BTreeListDestruct(BTreeListPtr pBL)
{
	BTreeListNodePtr p, q;
	for (p=pBL->m_head; p != 0; p = q)
	{
		q = p->m_next;
		free(p);
	}
	pBL->m_count = 0;
	pBL->m_head = 0;
	pBL->m_tail = 0;
}

void BTreeStackInitial(BTreeStackPtr pS)
{
	BTreeListInitial(pS);
}

void BTreeStackDestruct(BTreeStackPtr pS)
{
	BTreeListDestruct(pS);
}

int BTreeStackEmpty(BTreeStackPtr pS)
{
	return (pS->m_count == 0);
}

BTreeNodePtr BTreeStackTop(BTreeStackPtr pS)
{
	return pS->m_head->m_nodePtr;
}

BTreeListNodePtr BTreeStackListTop(BTreeStackPtr pS)
{
	return pS->m_head;
}

BTreeNodePtr BTreeStackPop(BTreeStackPtr pS)
{
	BTreeListNodePtr pLN = FrontRemoveBTreeNode(pS);
	BTreeNodePtr ptr = pLN->m_nodePtr;
	free(pLN);
	return ptr;
}

void BTreeStackPush(BTreeStackPtr pS, BTreeNodePtr ptr)
{
	FrontInsertBTreeNode(pS, ptr);
}

void BTreeQueueInitial(BTreeQueuePtr pQ)
{
	BTreeListInitial(pQ);
}

void BTreeQueueDestruct(BTreeQueuePtr pQ)
{
	BTreeListDestruct(pQ);
}

int BTreeQueueEmpty(BTreeQueuePtr pQ)
{
	return (pQ->m_count == 0);
}

BTreeNodePtr BTreeQueueFront(BTreeQueuePtr pQ)
{
	return pQ->m_head->m_nodePtr;
}

void BTreeQueueEnqueue(BTreeQueuePtr pQ, BTreeNodePtr ptr)
{
	BackInsertBTreeNode(pQ, ptr);
}

BTreeNodePtr BTreeQueueDequeue(BTreeQueuePtr pQ)
{
	BTreeListNodePtr pLN = FrontRemoveBTreeNode(pQ);
	BTreeNodePtr ptr = pLN->m_nodePtr;
	free(pLN);
	return ptr;
}
#include "NLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void NLinkListInitial(NLinkListPtr pL)
{
	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

NLinkNodePtr NLinkSearch(NLinkListPtr pL, DataType key)
{
	NLinkNodePtr x, p, lastNode=0;
	for (x=pL->m_head; x!=0 && x->m_data!=key; 
		p=x, x=(NLinkNodePtr)(p->m_np ^ (unsigned int)lastNode), lastNode=p)
		;
	return x;
}

void NLinkListPrint(NLinkListPtr pL)
{
	NLinkNodePtr x, p, lastNode=0;
	for (x=pL->m_head; x!=0; 
		p=x, x=(NLinkNodePtr)(p->m_np ^ (unsigned int)lastNode), lastNode=p)
		printf("%d\n", x->m_data);
}

void FrontInsertNLinkNode(NLinkListPtr pL, NLinkNodePtr x)
{
	unsigned int prev=0, next=0;
	x->m_np = 0;
	x->m_np = x->m_np ^ (unsigned int)pL->m_head;
	if (pL->m_head)
	{
		next = prev ^ pL->m_head->m_np;
		pL->m_head->m_np = (unsigned int)x ^ next;
	}
	pL->m_head = x;
	++pL->m_count;
	if (pL->m_count==1)
		pL->m_tail = x;
}

void FrontInsertNKey(NLinkListPtr pL, DataType key)
{
	NLinkNodePtr x=(NLinkNodePtr)malloc(sizeof(NLinkNode));
	x->m_data = key;
	FrontInsertNLinkNode(pL, x);
}

void BackInsertNLinkNode(NLinkListPtr pL, NLinkNodePtr x)
{
	unsigned int prev=0, next=0;
	x->m_np = 0;
	x->m_np = x->m_np ^ (unsigned int)pL->m_tail;
	if (pL->m_tail)
	{
		prev = next ^ pL->m_tail->m_np;
		pL->m_tail->m_np = prev ^ (unsigned int)x;
	}
	pL->m_tail = x;
	++pL->m_count;
	if (pL->m_count==1)
		pL->m_head = x;
}

void BackInsertNKey(NLinkListPtr pL, DataType key)
{
	NLinkNodePtr x=(NLinkNodePtr)malloc(sizeof(NLinkNode));
	x->m_data = key;
	BackInsertNLinkNode(pL, x);
}

void RemoveNLinkNode(NLinkListPtr pL, NLinkNodePtr x)
{
	unsigned int firstPrev=0, lastNext=0, third=0, beforeLast=0, afterNext=0;
	NLinkNodePtr firstNode, secondNode, thirdNode, p, q, lastNode=0, nextNode=0;
	if (x==pL->m_head)
	{
		secondNode = (NLinkNodePtr)(pL->m_head->m_np ^ firstPrev);
		if (secondNode)
		{
			third = secondNode->m_np ^ (unsigned int)pL->m_head;
			secondNode->m_np = firstPrev ^ third;
		}
		pL->m_head = secondNode;
	}
	if (x==pL->m_tail)
	{
		secondNode = (NLinkNodePtr)(pL->m_tail->m_np ^ lastNext);
		if (secondNode)
		{
			third = secondNode->m_np ^ (unsigned int)pL->m_tail;
			secondNode->m_np = lastNext ^ third;
		}
		pL->m_tail = secondNode;
	}

	for (p=pL->m_head; p!=0 && p!=x; 
		q=p, p=(NLinkNodePtr)(q->m_np ^ (unsigned int)lastNode), lastNode=q)
		;

	nextNode = (NLinkNodePtr)((unsigned int)lastNode ^ p->m_np);

	beforeLast = lastNode->m_np ^ (unsigned int)p;
	lastNode->m_np = beforeLast ^ (unsigned int)nextNode;

	afterNext = nextNode->m_np ^ (unsigned int)p;
	nextNode->m_np = afterNext ^ (unsigned int)lastNode;

	--pL->m_count;
}

void NLinkListDestruct(NLinkListPtr pL)
{
	NLinkNodePtr x, p, q, lastNode=0;
	for (x=pL->m_head; x!=0; 
		x=q)
	{
		p=x;
		q=(NLinkNodePtr)(p->m_np ^ (unsigned int)lastNode);
		lastNode=p;
		free(x);
	}

	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

void TestNLinkList()
{
	DataType x;
	NLinkListPtr ptr;
	NLinkNodePtr p;
	ptr=(NLinkListPtr)malloc(sizeof(NLinkList));
	NLinkListInitial(ptr);

	printf("Test NLinkList:\n");
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		BackInsertNKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		FrontInsertNKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	NLinkListPrint(ptr);

	printf("input searched key:\n");
	scanf("%d", &x);
	p = NLinkSearch(ptr, x);
	if (p)
	{
		printf("%d\n", p->m_data);
		RemoveNLinkNode(ptr, p);
		printf("After delete:\n");
		NLinkListPrint(ptr);
	}

	NLinkListDestruct(ptr);
	free(ptr);
}
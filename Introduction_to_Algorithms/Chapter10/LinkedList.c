#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void LinkListInitial(LinkListPtr pL)
{
	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

LinkNodePtr LinkSearch(LinkListPtr pL, DataType key)
{
	LinkNodePtr x;
	for (x=pL->m_head; x!=0 && x->m_data!=key; x=x->m_next)
		;
	return x;
}

void FrontInsertLinkNode(LinkListPtr pL, LinkNodePtr x)
{
	x->m_next = pL->m_head;
	pL->m_head = x;
	++pL->m_count;
	if (pL->m_count == 1)
		pL->m_tail = x;
}

void FrontInsertKey(LinkListPtr pL, DataType key)
{
	LinkNodePtr x = (LinkNodePtr)malloc(sizeof(LinkNode));
	x->m_data = key;
	FrontInsertLinkNode(pL, x);
}

void BackInsertLinkNode(LinkListPtr pL, LinkNodePtr x)
{
	if (pL->m_tail)
		pL->m_tail->m_next = x;
	x->m_next = 0;
	pL->m_tail = x;
	++pL->m_count;
	if (pL->m_count == 1)
		pL->m_head = x;
}

void BackInsertKey(LinkListPtr pL, DataType key)
{
	LinkNodePtr x = (LinkNodePtr)malloc(sizeof(LinkNode));
	x->m_data = key;
	BackInsertLinkNode(pL, x);
}

void RemoveLinkNode(LinkListPtr pL, LinkNodePtr x)
{
	LinkNodePtr p;
	if (x!=pL->m_head)
	{
		for (p=pL->m_head; p!=0 && p->m_next!=x; p=p->m_next)
			;
		if (p)
			p->m_next = x->m_next;
	}
	else
		pL->m_head = pL->m_head->m_next;

	--pL->m_count;
}

void LinkListDestruct(LinkListPtr pL)
{
	LinkNodePtr p, q;
	for (p=pL->m_head; p!=0; p=q)
	{
		q=p->m_next;
		free(p);
	}
	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

void LinkListReverse(LinkListPtr pL)
{
	LinkNodePtr p, q, t;
	if (pL->m_head != NULL)
	{
		for (p=pL->m_head, q=p->m_next; p!=0 && q!=0;)
		{
			t = q->m_next;
			q->m_next = p;
			if (p==pL->m_head)
			{
				p->m_next = 0;
				pL->m_tail = p;
			}
			if (t==0)
				pL->m_head = q;
			p = q;
			q = t;
		}
	}
}

void TestLinkList()
{
	DataType x;
	LinkListPtr ptr;
	LinkNodePtr p;
	ptr=(LinkListPtr)malloc(sizeof(LinkList));
	LinkListInitial(ptr);

	printf("Test LinkList:\n");
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		FrontInsertKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		BackInsertKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	for (p=ptr->m_head; p!=0; p=p->m_next)
		printf("%d\n", p->m_data);

	printf("input searched key:\n");
	scanf("%d", &x);
	p = LinkSearch(ptr, x);
	if (p)
	{
		printf("%d\n", p->m_data);
		RemoveLinkNode(ptr, p);
		printf("After delete:\n");
		for (p=ptr->m_head; p!=0; p=p->m_next)
			printf("%d\n", p->m_data);
	}
	else
		printf("not found!\n");

	LinkListReverse(ptr);
	printf("After reverse:\n");
	for (p=ptr->m_head; p!=0; p=p->m_next)
		printf("%d\n", p->m_data);

	LinkListDestruct(ptr);
	free(ptr);
}

void DLinkListInitial(DLinkListPtr pL)
{
	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

DLinkNodePtr DLinkSearch(DLinkListPtr pL, DataType key)
{
	DLinkNodePtr x;
	for (x=pL->m_head; x!=0 && x->m_data!=key; x=x->m_next)
		;
	return x;
}

void FrontInsertDLinkNode(DLinkListPtr pL, DLinkNodePtr x)
{
	x->m_next = pL->m_head;
	if (pL->m_head)
		pL->m_head->m_prev = x;
	x->m_prev = 0;
	pL->m_head = x;
	++pL->m_count;
	if (pL->m_count==1)
		pL->m_tail = x;
}

void FrontInsertDKey(DLinkListPtr pL, DataType key)
{
	DLinkNodePtr x = (DLinkNodePtr)malloc(sizeof(DLinkNode));
	x->m_data = key;
	FrontInsertDLinkNode(pL, x);
}

void BackInsertDLinkNode(DLinkListPtr pL, DLinkNodePtr x)
{
	if (pL->m_tail)
		pL->m_tail->m_next = x;
	x->m_prev = pL->m_tail;
	x->m_next = 0;
	pL->m_tail = x;
	++pL->m_count;
	if (pL->m_count == 1)
		pL->m_head = x;
}

void BackInsertDKey(DLinkListPtr pL, DataType key)
{
	DLinkNodePtr x = (DLinkNodePtr)malloc(sizeof(DLinkNode));
	x->m_data = key;
	BackInsertDLinkNode(pL, x);
}

void RemoveDLinkNode(DLinkListPtr pL, DLinkNodePtr x)
{
	if (x==pL->m_head)
		pL->m_head = pL->m_head->m_next;
	if (x==pL->m_tail)
		pL->m_tail = pL->m_tail->m_prev;

	if (x->m_prev)
		x->m_prev->m_next = x->m_next;
	if (x->m_next)
		x->m_next->m_prev = x->m_prev;
	--pL->m_count;
}

void DLinkListDestruct(DLinkListPtr pL)
{
	DLinkNodePtr p, q;
	for (p=pL->m_head; p!=0; p=q)
	{
		q=p->m_next;
		free(p);
	}
	pL->m_count = 0;
	pL->m_head = 0;
	pL->m_tail = 0;
}

void TestDLinkList()
{
	DataType x;
	DLinkListPtr ptr;
	DLinkNodePtr p;
	ptr=(DLinkListPtr)malloc(sizeof(DLinkList));
	DLinkListInitial(ptr);

	printf("Test DLinkList:\n");
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		BackInsertDKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}
	printf("input x\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		FrontInsertDKey(ptr, x);
		printf("input x\n");
		scanf("%d", &x);
	}

	for (p=ptr->m_head; p!=0; p=p->m_next)
		printf("%d\n", p->m_data);

	printf("input searched key:\n");
	scanf("%d", &x);
	p = DLinkSearch(ptr, x);
	if (p)
	{
		printf("%d\n", p->m_data);
		RemoveDLinkNode(ptr, p);
		printf("After delete:\n");
		for (p=ptr->m_head; p!=0; p=p->m_next)
			printf("%d\n", p->m_data);
	}
	else
		printf("not found!\n");

	DLinkListDestruct(ptr);
	free(ptr);
}
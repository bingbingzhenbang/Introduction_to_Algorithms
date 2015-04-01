#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int NodeCount(BTreeNodePtr ptr)
{
	int cnt = 0;
	if (ptr)
		cnt = 1 + NodeCount(ptr->m_left) + NodeCount(ptr->m_right);
	return cnt;
}

BTreeNodePtr AddTree(BTreeNodePtr ptr, DataType key)
{
	if (ptr==0)
	{
		ptr = MakeNode(key);
	}
	else if (key == ptr->m_data)
		++ptr->m_count;
	else if (key < ptr->m_data)
	{
		ptr->m_left = AddTree(ptr->m_left, key);
		ptr->m_left->m_parent = ptr;
	}
	else if (key > ptr->m_data)
	{
		ptr->m_right = AddTree(ptr->m_right, key);
		ptr->m_right->m_parent = ptr;
	}
	return ptr;
}

void DestructTree(BTreeNodePtr ptr)
{
	if (ptr)
	{
		DestructTree(ptr->m_left);
		DestructTree(ptr->m_right);
		free(ptr);
	}
}

void TreeInOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	if (ptr)
	{
		TreeInOrderVisit(ptr->m_left, pVisit);
		pVisit(ptr);
		TreeInOrderVisit(ptr->m_right, pVisit);
	}
}

void TreePreOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	if (ptr)
	{
		pVisit(ptr);
		TreePreOrderVisit(ptr->m_left, pVisit);
		TreePreOrderVisit(ptr->m_right, pVisit);
	}
}

void TreePostOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	if (ptr)
	{
		TreePostOrderVisit(ptr->m_left, pVisit);
		TreePostOrderVisit(ptr->m_right, pVisit);
		pVisit(ptr);
	}
}

void TreeStackInOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	BTreeNodePtr p = ptr;
	BTreeStack pStack;
	BTreeStackInitial(&pStack);
	do 
	{
		while (p)
		{
			BTreeStackPush(&pStack, p);
			p = p->m_left;
		}
		if (!BTreeStackEmpty(&pStack))
		{
			p = BTreeStackPop(&pStack);
			pVisit(p);
			p = p->m_right;
		}
	} while (p || !BTreeStackEmpty(&pStack));
	BTreeStackDestruct(&pStack);
}

void TreeStackPreOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	BTreeNodePtr p = ptr;
	BTreeStack pStack;
	BTreeStackInitial(&pStack);
	BTreeStackPush(&pStack, 0);
	while (p)
	{
		pVisit(p);
		if (p->m_right)
			BTreeStackPush(&pStack, p->m_right);
		if (p->m_left)
			p = p->m_left;
		else
			p = BTreeStackPop(&pStack);
	}
	BTreeStackDestruct(&pStack);
}

void TreeStackPostOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	int state;
	BTreeNodePtr p = ptr;
	BTreeStack pStack;
	BTreeStackInitial(&pStack);
	do 
	{
		while (p)
		{
			BTreeStackPush(&pStack, p);
			BTreeStackListTop(&pStack)->m_tag = Left;
			p = p->m_left;
		}
		state = 1;
		while (state && !BTreeStackEmpty(&pStack))
		{
			p = BTreeStackTop(&pStack);
			switch (BTreeStackListTop(&pStack)->m_tag)
			{
			case Left:
				{
					BTreeStackListTop(&pStack)->m_tag = Right;
					state = 0;
					p = p->m_right;
				}
				break;
			case Right:
				{
					p = BTreeStackPop(&pStack);
					pVisit(p);
				}
				break;
			default:
				break;
			}
		}
	} while (!BTreeStackEmpty(&pStack));
	BTreeStackDestruct(&pStack);
}

void TreeQueueLevelOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	BTreeNodePtr p = ptr;
	BTreeQueue pQueue;
	BTreeQueueInitial(&pQueue);
	BTreeQueueEnqueue(&pQueue, p);
	while (!BTreeQueueEmpty(&pQueue))
	{
		p = BTreeQueueDequeue(&pQueue);
		pVisit(p);
		if (p->m_left)
			BTreeQueueEnqueue(&pQueue, p->m_left);
		if (p->m_right)
			BTreeQueueEnqueue(&pQueue, p->m_right);
	}
	BTreeQueueDestruct(&pQueue);
}

void TreeEasyInOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	BTreeNodePtr p = ptr;
	while (p)
	{
		if (p->m_left)
		{
			p = p->m_left;
			continue;
		}
		else
		{
			pVisit(p);
			if (p->m_right)
			{
				p = p->m_right;
				continue;
			}
			while (1)
			{
				if (p == p->m_parent->m_left)
				{
					pVisit(p->m_parent);
					if (p->m_parent->m_right)
					{
						p = p->m_parent->m_right;
						break;
					}
				}
				p = p->m_parent;
				if (p==ptr)
					return;
			}
		}
	}
	return;
}

void TestBTree()
{
	BTreeNodePtr pRoot=0;
	DataType key;
	printf("input key:\n");
	scanf("%d", &key);
	while (key != -1)
	{
		pRoot = AddTree(pRoot, key);
		printf("input key:\n");
		scanf("%d", &key);
	}
	printf("InOrder:\n");
	TreeInOrderVisit(pRoot, PrintNode);
	printf("Stack InOrder:\n");
	TreeStackInOrderVisit(pRoot, PrintNode);
	printf("Easy InOrder:\n");
	TreeEasyInOrderVisit(pRoot, PrintNode);
	printf("PreOrder:\n");
	TreePreOrderVisit(pRoot, PrintNode);
	printf("Stack PreOrder:\n");
	TreeStackPreOrderVisit(pRoot, PrintNode);
	printf("PostOrder:\n");
	TreePostOrderVisit(pRoot, PrintNode);
	printf("Stack PostOrder:\n");
	TreeStackPostOrderVisit(pRoot, PrintNode);
	printf("Level Order:\n");
	TreeQueueLevelOrderVisit(pRoot, PrintNode);
	DestructTree(pRoot);
	return;
}
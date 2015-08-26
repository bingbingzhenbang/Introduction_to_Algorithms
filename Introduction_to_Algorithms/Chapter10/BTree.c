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

//BTreeNodePtr AddTree(BTreeNodePtr ptr, DataType key)
//{
//	if (ptr==0)
//	{
//		ptr = MakeNode(key);
//	}
//	else if (key == ptr->m_data)
//		++ptr->m_count;
//	else if (key < ptr->m_data)
//	{
//		ptr->m_left = AddTree(ptr->m_left, key);
//		ptr->m_left->m_parent = ptr;
//	}
//	else if (key > ptr->m_data)
//	{
//		ptr->m_right = AddTree(ptr->m_right, key);
//		ptr->m_right->m_parent = ptr;
//	}
//	return ptr;
//}

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
				if (p == ptr)
					return;
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
			}
		}
	}
	return;
}

BTreeNodePtr TreeSearch(BTreeNodePtr ptr, DataType key)
{
	if (ptr==NULL || ptr->m_data == key)
		return ptr;
	if (key < ptr->m_data)
		return TreeSearch(ptr->m_left, key);
	else
		return TreeSearch(ptr->m_right, key);
}

BTreeNodePtr IterativeTreeSearch(BTreeNodePtr ptr, DataType key)
{
	while (ptr != NULL && ptr->m_data != key)
	{
		if (key < ptr->m_data)
			ptr = ptr->m_left;
		else
			ptr = ptr->m_right;
	}
	return ptr;
}

BTreeNodePtr TreeMinimum(BTreeNodePtr ptr)
{
	if (ptr->m_left == NULL)
		return ptr;
	else
		return TreeMinimum(ptr->m_left);
}

BTreeNodePtr TreeMaximum(BTreeNodePtr ptr)
{
	if (ptr->m_right == NULL)
		return ptr;
	else
		return TreeMaximum(ptr->m_right);
}

BTreeNodePtr IterativeTreeMinimum(BTreeNodePtr ptr)
{
	while (ptr->m_left != NULL)
		ptr = ptr->m_left;
	return ptr;
}

BTreeNodePtr IterativeTreeMaximum(BTreeNodePtr ptr)
{
	while (ptr->m_right != NULL)
		ptr = ptr->m_right;
	return ptr;
}

BTreeNodePtr TreeSuccessor(BTreeNodePtr ptr)
{
	BTreeNodePtr y;
	if (ptr->m_right != NULL)
		return IterativeTreeMinimum(ptr->m_right);

	y = ptr->m_parent;
	while (y != NULL && ptr == y->m_right)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

BTreeNodePtr TreePredecessor(BTreeNodePtr ptr)
{
	BTreeNodePtr y;
	if (ptr->m_left != NULL)
		return IterativeTreeMaximum(ptr->m_left);

	y = ptr->m_parent;
	while (y != NULL && ptr == y->m_left)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

void TreeIterativeInOrderVisit(BTreeNodePtr ptr, visit pVisit)
{
	BTreeNodePtr x = IterativeTreeMinimum(ptr);
	while (x != NULL)
	{
		pVisit(x);
		x = TreeSuccessor(x);
	}
	return;
}

void IterativeTreeInsert(BTreeNodePtr *pRoot, BTreeNodePtr z)
{
	BTreeNodePtr y = NULL, x = *pRoot;
	if (z == NULL)
		return;
	while (x != NULL)
	{
		y = x;
		if (z->m_data < x->m_data)
			x = x->m_left;
		else
			x = x->m_right;
	}
	z->m_parent = y;

	if (y == NULL)
		*pRoot = z;
	else
	{
		if (z->m_data < y->m_data)
			y->m_left = z;
		else
			y->m_right = z;
	}
}

BTreeNodePtr IterativeTreeDelete(BTreeNodePtr *pRoot, BTreeNodePtr z)
{
	BTreeNodePtr y, x;
	if (z->m_left == NULL || z->m_right == NULL)
		y = z;
	else
		y = TreeSuccessor(z);

	if (y->m_left != NULL)
		x = y->m_left;
	else
		x = y->m_right;

	if (x != NULL)
		x->m_parent = y->m_parent;

	if (y->m_parent == NULL)
		*pRoot = x;
	else
	{
		if (y == y->m_parent->m_left)
			y->m_parent->m_left = x;
		else
			y->m_parent->m_right = x;
	}

	if (z != y)
	{
		z->m_data = y->m_data;
		z->m_count = y->m_count;
	}
	return y;
}

BTreeNodePtr IterativeTreeSafeDelete(BTreeNodePtr *pRoot, BTreeNodePtr z)
{
	BTreeNodePtr y, x;
	if (z->m_left == NULL || z->m_right == NULL)
		y = z;
	else
		y = TreeSuccessor(z);

	if (y->m_left != NULL)
		x = y->m_left;
	else
		x = y->m_right;

	if (x != NULL)
		x->m_parent = y->m_parent;

	if (y->m_parent == NULL)
		*pRoot = x;
	else
	{
		if (y == y->m_parent->m_left)
			y->m_parent->m_left = x;
		else
			y->m_parent->m_right = x;
	}

	if (z != y)
	{
		y->m_parent = z->m_parent;
		y->m_left = z->m_left;
		y->m_right = z->m_right;
		if (z == z->m_parent->m_left)
			z->m_parent->m_left = y;
		else
			z->m_parent->m_right = y;
		if (y->m_left != NULL)
			y->m_left->m_parent = y;
		if (y->m_right != NULL)
			y->m_right->m_parent = y;

	}
	return z;

}

BTreeNodePtr TreeInsert(BTreeNodePtr pRoot, BTreeNodePtr ptr)
{
	if (pRoot == NULL)
		pRoot = ptr;
	else if (ptr->m_data < pRoot->m_data)
	{
		pRoot->m_left = TreeInsert(pRoot->m_left, ptr);
		pRoot->m_left->m_parent = pRoot;
	}
	else
	{
		pRoot->m_right = TreeInsert(pRoot->m_right, ptr);
		pRoot->m_right->m_parent = pRoot;
	}
	return pRoot;
}

void TestBTree()
{
	BTreeNodePtr pRoot=0, pNode=0, temp, temp1;
	DataType key;
	FILE *fp = fopen("bintree_input", "r");
	if (!fp)
	{
		printf("Cannot open input file!\n");
		return;
	}
	fscanf(fp, "%ld", &key);
	while (key != -1)
	{
		pNode = MakeNode(key);
//        IterativeTreeInsert(&pRoot, pNode);
		pRoot = TreeInsert(pRoot, pNode);
		fscanf(fp, "%ld", &key);
	}
	fclose(fp);
	printf("InOrder:\n");
	//TreeInOrderVisit(pRoot, PrintNode);
	//printf("Stack InOrder:\n");
	//TreeStackInOrderVisit(pRoot, PrintNode);
	//printf("Easy InOrder:\n");
	//TreeEasyInOrderVisit(pRoot, PrintNode);
	//printf("PreOrder:\n");
	//TreePreOrderVisit(pRoot, PrintNode);
	//printf("Stack PreOrder:\n");
	//TreeStackPreOrderVisit(pRoot, PrintNode);
	//printf("PostOrder:\n");
	//TreePostOrderVisit(pRoot, PrintNode);
	//printf("Stack PostOrder:\n");
	//TreeStackPostOrderVisit(pRoot, PrintNode);
	//printf("Level Order:\n");
	//TreeQueueLevelOrderVisit(pRoot, PrintNode);
	TreeIterativeInOrderVisit(pRoot, PrintNode);
	printf("Input the key you need to search:\n");
	scanf("%ld", &key);

	pNode = IterativeTreeSearch(pRoot, key);
	if (pNode)
	{
		temp = TreePredecessor(pNode);
		if (temp)
		{
			temp1 = IterativeTreeSafeDelete(&pRoot, temp);
			free(temp1);
		}
	}
	else
		printf("Cannot find node with key = %d\n", key);
	printf("Input the key you need to search:\n");

	printf("After delete, InOrder:\n");
	TreeIterativeInOrderVisit(pRoot, PrintNode);
	DestructTree(pRoot);
	return;
}
#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

const char *NodeColorNames[] = {"Red", "Black"};

void PrintRBTreeNode(RBTreeNodePtr ptr)
{
	printf("color = %4s key = %3d value = %3d\n", NodeColorNames[ptr->m_color], ptr->m_key, ptr->m_value);
}

RBTreeNodePtr MakeRBTreeNode(KeyType key)
{
	RBTreeNodePtr ptr;
	ptr = (RBTreeNodePtr)(malloc(sizeof(RBTreeNode)));
	ptr->m_key = key;
	ptr->m_value = 0;
	ptr->m_color = Enum_Red;
	ptr->m_parent = ptr->m_left = ptr->m_right = NULL;
	return ptr;
}

void InitializeRBTree(RBTreePtr pTree)
{
	pTree->m_null = (RBTreeNodePtr)(malloc(sizeof(RBTreeNode)));
	pTree->m_null->m_color = Enum_Black;
	pTree->m_null->m_key = pTree->m_null->m_value = 0;
	pTree->m_null->m_parent = pTree->m_null->m_left = pTree->m_null->m_right = NULL;
	pTree->m_root = pTree->m_null;
}

void DestructRBTree(RBTreePtr pTree)
{
	DestructRBSubTree(pTree, pTree->m_root);
	free(pTree->m_null);
	pTree->m_null = pTree->m_root = NULL;
}

void DestructRBSubTree(RBTreePtr pTree, RBTreeNodePtr ptr)
{
	if (ptr != pTree->m_null)
	{
		DestructRBSubTree(pTree, ptr->m_left);
		DestructRBSubTree(pTree, ptr->m_right);
		free(ptr);
	}
}

RBTreeNodePtr IterativeTreeMinimum(RBTreePtr pTree, RBTreeNodePtr ptr)
{
	while (ptr->m_left != pTree->m_null)
		ptr = ptr->m_left;
	return ptr;
}

RBTreeNodePtr IterativeTreeMaximum(RBTreePtr pTree, RBTreeNodePtr ptr)
{
	while (ptr->m_right != pTree->m_null)
		ptr = ptr->m_right;
	return ptr;
}

RBTreeNodePtr TreeSuccessor(RBTreePtr pTree, RBTreeNodePtr ptr)
{
	RBTreeNodePtr y;
	if (ptr->m_right != pTree->m_null)
		return IterativeTreeMinimum(pTree, ptr->m_right);

	y = ptr->m_parent;
	while (y != pTree->m_null && ptr == y->m_right)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

RBTreeNodePtr TreePredecessor(RBTreePtr pTree, RBTreeNodePtr ptr)
{
	RBTreeNodePtr y;
	if (ptr->m_left != pTree->m_null)
		return IterativeTreeMaximum(pTree, ptr->m_left);

	y = ptr->m_parent;
	while (y != pTree->m_null && ptr == y->m_left)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

void RBTreeInOrderVisit(RBTreePtr pTree, RBTreeNodePtr ptr, rbvisit pVisit)
{
	if (ptr != pTree->m_null)
	{
		RBTreeInOrderVisit(pTree, ptr->m_left, pVisit);
		pVisit(ptr);
		RBTreeInOrderVisit(pTree, ptr->m_right, pVisit);
	}
}

void LeftRotate(RBTreePtr pTree, RBTreeNodePtr x)
{
	RBTreeNodePtr y = x->m_right;
	x->m_right = y->m_left;
	if (y->m_left != pTree->m_null)
		y->m_left->m_parent = x;
	y->m_parent = x->m_parent;
	if (x->m_parent == pTree->m_null)
	{
		pTree->m_root = y;
	}
	else
	{
		if (x == x->m_parent->m_left)
			x->m_parent->m_left = y;
		else
			x->m_parent->m_right = y;
	}
	y->m_left = x;
	x->m_parent = y;
}

void RightRotate(RBTreePtr pTree, RBTreeNodePtr y)
{
	RBTreeNodePtr x = y->m_left;
	y->m_left = x->m_right;
	if (x->m_right != pTree->m_null)
		x->m_right->m_parent = y;
	x->m_parent = y->m_parent;
	if (y->m_parent == pTree->m_null)
	{
		pTree->m_root = x;
	}
	else
	{
		if (y == y->m_parent->m_left)
			y->m_parent->m_left = x;
		else
			y->m_parent->m_right = x;
	}
	x->m_right = y;
	y->m_parent = x;
}

void RBTreeInsert(RBTreePtr pTree, RBTreeNodePtr z)
{
	RBTreeNodePtr y = pTree->m_null, x = pTree->m_root;
	while (x != pTree->m_null)
	{
		y = x;
		if (z->m_key < x->m_key)
			x = x->m_left;
		else
			x = x->m_right;
	}
	z->m_parent = y;

	if (y == pTree->m_null)
	{
		pTree->m_root = z;
	}
	else
	{
		if (z->m_key < y->m_key)
			y->m_left = z;
		else
			y->m_right = z;
	}
	z->m_left = pTree->m_null;
	z->m_right = pTree->m_null;
	z->m_color = Enum_Red;
	RBTreeInsertFixup(pTree, z);
}

void RBTreeInsertFixup(RBTreePtr pTree, RBTreeNodePtr z)
{
	RBTreeNodePtr y;
	while (z->m_parent->m_color == Enum_Red)
	{
		if (z->m_parent == z->m_parent->m_parent->m_left)
		{
			y = z->m_parent->m_parent->m_right;
			if (y->m_color == Enum_Red)
			{
				z->m_parent->m_color = Enum_Black;
				y->m_color = Enum_Black;
				z->m_parent->m_parent->m_color = Enum_Red;
				z = z->m_parent->m_parent;
			}
			else if (z == z->m_parent->m_right)
			{
				z = z->m_parent;
				LeftRotate(pTree, z);
			}
			z->m_parent->m_color = Enum_Black;
			z->m_parent->m_parent->m_color = Enum_Red;
			RightRotate(pTree, z->m_parent->m_parent);
		}
		else
		{

		}
	}
	pTree->m_root->m_color = Enum_Black;
}

void RBTreeDelete(RBTreePtr pTree, RBTreeNodePtr z)
{
	RBTreeDeleteFixup(pTree, z);
}

void RBTreeDeleteFixup(RBTreePtr pTree, RBTreeNodePtr z)
{

}

void TestRBTree()
{
	RBTree tree; RBTreeNodePtr pNode; KeyType key;
	FILE *fp = fopen("rbtree_input", "r");
	if (!fp)
	{
		printf("Cannot open input file!\n");
		return;
	}
	fscanf(fp, "%ld", &key);
	InitializeRBTree(&tree);
	while (key != -1)
	{
		pNode = MakeRBTreeNode(key);
		RBTreeInsert(&tree, pNode);
		fscanf(fp, "%ld", &key);
	}
	RBTreeInOrderVisit(&tree, tree.m_root, PrintRBTreeNode);
	DestructRBTree(&tree);
}
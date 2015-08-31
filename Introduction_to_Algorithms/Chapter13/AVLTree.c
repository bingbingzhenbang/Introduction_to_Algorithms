#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))

void PrintAVLTreeNode(AVLTreeNodePtr ptr)
{
	printf("height = %3d key = %3d value = %3d height = %3d\n", ptr->m_height, ptr->m_key, ptr->m_value);
}

AVLTreeNodePtr MakeAVLTreeNode(KeyType key)
{
	AVLTreeNodePtr ptr;
	ptr = (AVLTreeNodePtr)(malloc(sizeof(AVLTreeNode)));
	ptr->m_key = key;
	ptr->m_value = 0;
	ptr->m_height = 0;
	ptr->m_parent = ptr->m_left = ptr->m_right = NULL;
	return ptr;
}

int AVLTreeNodeHeight(AVLTreeNodePtr ptr)
{
	return (ptr == NULL) ? -1 : ptr->m_height;
}

void InitializeAVLTree(AVLTreePtr pTree)
{
	pTree->m_root = NULL;
}

void DestructAVLSubTree(AVLTreeNodePtr ptr)
{
	if (ptr != NULL)
	{
		DestructAVLSubTree(ptr->m_left);
		DestructAVLSubTree(ptr->m_right);
		free(ptr);
	}
}

AVLTreeNodePtr IterativeAVLTreeMinimum(AVLTreeNodePtr ptr)
{
	while (ptr->m_left != NULL)
		ptr = ptr->m_left;
	return ptr;
}

AVLTreeNodePtr IterativeAVLTreeMaximum(AVLTreeNodePtr ptr)
{
	while (ptr->m_right != NULL)
		ptr = ptr->m_right;
	return ptr;
}

AVLTreeNodePtr AVLTreeSuccessor(AVLTreeNodePtr ptr)
{
	AVLTreeNodePtr y;
	if (ptr->m_right != NULL)
		return IterativeAVLTreeMinimum(ptr->m_right);

	y = ptr->m_parent;
	while (y != NULL && ptr == y->m_right)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

AVLTreeNodePtr AVLTreePredecessor(AVLTreeNodePtr ptr)
{
	AVLTreeNodePtr y;
	if (ptr->m_left != NULL)
		return IterativeAVLTreeMaximum(ptr->m_left);

	y = ptr->m_parent;
	while (y != NULL && ptr == y->m_left)
	{
		ptr = y;
		y = y->m_parent;
	}
	return y;
}

void AVLTreeInOrderVisit(AVLTreeNodePtr ptr, avlvisit pVisit)
{
	if (ptr != NULL)
	{
		AVLTreeInOrderVisit(ptr->m_left, pVisit);
		pVisit(ptr);
		AVLTreeInOrderVisit(ptr->m_right, pVisit);
	}
}

AVLTreeNodePtr IterativeAVLTreeSearch(AVLTreeNodePtr ptr, KeyType key)
{
	while (ptr != NULL && ptr->m_key != key)
	{
		if (key < ptr->m_key)
			ptr = ptr->m_left;
		else
			ptr = ptr->m_right;
	}
	return ptr;
}

void AVLLeftRotate(AVLTreePtr pTree, AVLTreeNodePtr x)
{
	AVLTreeNodePtr y = x->m_right;
	x->m_right = y->m_left;
	if (y->m_left != NULL)
		y->m_left->m_parent = x;
	y->m_parent = x->m_parent;
	if (x->m_parent == NULL)
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

void AVLRightRotate(AVLTreePtr pTree, AVLTreeNodePtr y)
{
	AVLTreeNodePtr x = y->m_left;
	y->m_left = x->m_right;
	if (x->m_right != NULL)
		x->m_right->m_parent = y;
	x->m_parent = y->m_parent;
	if (y->m_parent == NULL)
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

void AVLBalance(AVLTreePtr pTree, AVLTreeNodePtr x)
{
	int Lh = AVLTreeNodeHeight(x->m_left), Rh = AVLTreeNodeHeight(x->m_right);
	if (abs(Lh - Rh) <= 1)
		return;
	else if (Lh - Rh == 2)
	{

	}
	else if (Rh - Lh == 2)
	{

	}
	else
	{
		printf("Invalid AVL tree!\n");
	}
}

AVLTreeNodePtr AVLTreeInsert(AVLTreePtr pTree, AVLTreeNodePtr x, AVLTreeNodePtr z)
{
	AVLTreeNodePtr y = NULL;
	if (x == NULL)
	{
		z->m_parent = NULL;
		z->m_left = NULL;
		z->m_right = NULL;
		x = z;
		if (pTree->m_root == NULL)
			pTree->m_root = x;
	}
	else if (z->m_key < x->m_key)
	{
		x->m_left = AVLTreeInsert(pTree, x->m_left, z);
		x->m_left->m_parent = x;
	} 
	else
	{
		x->m_right = AVLTreeInsert(pTree, x->m_right, z);
		x->m_right->m_parent = x;
	}
	AVLBalance(pTree, x);
	x->m_height = max( AVLTreeNodeHeight(x->m_left), AVLTreeNodeHeight(x->m_right) ) + 1;
	return x;
}

AVLTreeNodePtr AVLTreeDelete(AVLTreePtr pTree, AVLTreeNodePtr z)
{
	AVLTreeNodePtr y = NULL, x = NULL;
	if (z->m_left == NULL || z->m_right == NULL)
		y = z;
	else
		y = AVLTreeSuccessor(z);

	if (y->m_left != NULL)
		x = y->m_left;
	else
		x = y->m_right;

	if (x != NULL)
		x->m_parent = y->m_parent;

	if (y->m_parent == NULL)
		pTree->m_root = x;
	else
	{
		if (y == y->m_parent->m_left)
			y->m_parent->m_left = x;
		else
			y->m_parent->m_right = x;
	}

	if (y != z)
	{
		z->m_key = y->m_key;
		z->m_value = y->m_value;
	}
	return y;
}

void TestAVLTree()
{
	AVLTree tree; AVLTreeNodePtr pNode; KeyType key;
	FILE *fp = fopen("avltree_input", "r");
	if (!fp)
	{
		printf("Cannot open input file!\n");
		return;
	}
	fscanf(fp, "%ld", &key);
	InitializeAVLTree(&tree);
	while (key != -1)
	{
		pNode = MakeAVLTreeNode(key);
		AVLTreeInsert(&tree, tree.m_root, pNode);
		fscanf(fp, "%ld", &key);
	}
	fclose(fp);
	AVLTreeInOrderVisit(tree.m_root, PrintAVLTreeNode);
	printf("Input the key you want to delete:\n");
	scanf("%ld", &key);
	while (key != -1)
	{
		pNode = IterativeAVLTreeSearch(tree.m_root, key);
		if (pNode != NULL)
		{
			AVLTreeDelete(&tree, pNode);
		}
		if (tree.m_root == NULL)
			break;
		scanf("%ld", &key);
	}
	DestructAVLSubTree(tree.m_root);
}
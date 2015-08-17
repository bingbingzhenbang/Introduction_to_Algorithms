#include "RBTree.h"
#include <stdio.h>

const char *NodeColorNames[] = {"Red", "Black"};

void PrintRBTreeNode(RBTreeNodePtr ptr)
{
	printf("color = %5s key = %3d count = %3d\n", NodeColorNames[ptr->m_color], ptr->m_key, ptr->m_value);
}

void TestRBTree()
{
	RBTreeNode node;
	node.m_color = Enum_Black;
	node.m_key = 1;
	node.m_value = 1;
	node.m_parent = node.m_left = node.m_right = NULL;
	PrintRBTreeNode(&node);
}
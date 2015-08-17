#ifndef RBTREE_H
#define RBTREE_H

typedef enum NodeColor
{
	Enum_Red,
	Enum_Black,
	Enum_ColorCount,
}NodeColor;

typedef int KeyType;
typedef int ValueType;

typedef struct RBTreeNode
{
	KeyType m_key;
	ValueType m_value;
	NodeColor m_color;
	struct RBTreeNode *m_parent;
	struct RBTreeNode *m_left;
	struct RBTreeNode *m_right;
}RBTreeNode;

typedef RBTreeNode *RBTreeNodePtr;
typedef void (*rbvisit)(RBTreeNodePtr ptr);


void TestRBTree();

#endif // RBTREE_H
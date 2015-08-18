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

typedef struct RBTree
{
	RBTreeNodePtr m_root;
	RBTreeNodePtr m_null;
}RBTree;

typedef RBTree *RBTreePtr;

void InitializeRBTree(RBTreePtr pTree);
void DestructRBTree(RBTreePtr pTree);

RBTreeNodePtr IterativeTreeMinimum(RBTreePtr pTree, RBTreeNodePtr ptr);
RBTreeNodePtr IterativeTreeMaximum(RBTreePtr pTree, RBTreeNodePtr ptr);

RBTreeNodePtr TreeSuccessor(RBTreePtr pTree, RBTreeNodePtr ptr);
RBTreeNodePtr TreePredecessor(RBTreePtr pTree, RBTreeNodePtr ptr);

void LeftRotate(RBTreePtr pTree, RBTreeNodePtr x);
void RightRotate(RBTreePtr pTree, RBTreeNodePtr y);

void TestRBTree();

#endif // RBTREE_H
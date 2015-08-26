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

RBTreeNodePtr MakeRBTreeNode(KeyType key);

typedef struct RBTree
{
	RBTreeNodePtr m_null;
	RBTreeNodePtr m_root;
}RBTree;

typedef RBTree *RBTreePtr;

void InitializeRBTree(RBTreePtr pTree);
void DestructRBTree(RBTreePtr pTree);
void DestructRBSubTree(RBTreePtr pTree, RBTreeNodePtr ptr);

RBTreeNodePtr IterativeRBTreeMinimum(RBTreePtr pTree, RBTreeNodePtr ptr);
RBTreeNodePtr IterativeRBTreeMaximum(RBTreePtr pTree, RBTreeNodePtr ptr);

RBTreeNodePtr RBTreeSuccessor(RBTreePtr pTree, RBTreeNodePtr ptr);
RBTreeNodePtr RBTreePredecessor(RBTreePtr pTree, RBTreeNodePtr ptr);

void RBTreeInOrderVisit(RBTreePtr pTree, RBTreeNodePtr ptr, rbvisit pVisit);
RBTreeNodePtr IterativeRBTreeSearch(RBTreePtr pTree, RBTreeNodePtr ptr, KeyType key);

void LeftRotate(RBTreePtr pTree, RBTreeNodePtr x);
void RightRotate(RBTreePtr pTree, RBTreeNodePtr y);

void RBTreeInsert(RBTreePtr pTree, RBTreeNodePtr z);
void RBTreeInsertFixup(RBTreePtr pTree, RBTreeNodePtr z);

RBTreeNodePtr RBTreeDelete(RBTreePtr pTree, RBTreeNodePtr z);
void RBTreeDeleteFixup(RBTreePtr pTree, RBTreeNodePtr x);

void TestRBTree();

#endif // RBTREE_H
#ifndef AVLTREE_H
#define AVLTREE_H

typedef int KeyType;
typedef int ValueType;

typedef struct AVLTreeNode
{
	KeyType m_key;
	ValueType m_value;
	int m_height;
	struct AVLTreeNode *m_parent;
	struct AVLTreeNode *m_left;
	struct AVLTreeNode *m_right;
}AVLTreeNode;

typedef AVLTreeNode *AVLTreeNodePtr;

typedef void (*avlvisit)(AVLTreeNodePtr ptr);

AVLTreeNodePtr MakeAVLTreeNode(KeyType key);
int AVLTreeNodeHeight(AVLTreeNodePtr ptr);

typedef struct AVLTree
{
	AVLTreeNodePtr m_root;
}AVLTree;

typedef AVLTree *AVLTreePtr;

void InitializeAVLTree(AVLTreePtr pTree);
void DestructAVLSubTree(AVLTreeNodePtr ptr);

AVLTreeNodePtr IterativeAVLTreeMinimum(AVLTreeNodePtr ptr);
AVLTreeNodePtr IterativeAVLTreeMaximum(AVLTreeNodePtr ptr);

AVLTreeNodePtr AVLTreeSuccessor(AVLTreeNodePtr ptr);
AVLTreeNodePtr AVLTreePredecessor(AVLTreeNodePtr ptr);

void AVLTreeInOrderVisit(AVLTreeNodePtr ptr, avlvisit pVisit);
AVLTreeNodePtr IterativeAVLTreeSearch(AVLTreeNodePtr ptr, KeyType key);

void AVLLeftRotate(AVLTreePtr pTree, AVLTreeNodePtr x);
void AVLRightRotate(AVLTreePtr pTree, AVLTreeNodePtr y);

int AVLBalance(AVLTreePtr pTree, AVLTreeNodePtr x);

AVLTreeNodePtr AVLTreeInsert(AVLTreePtr pTree, AVLTreeNodePtr x, AVLTreeNodePtr z);

AVLTreeNodePtr AVLTreeDelete(AVLTreePtr pTree, AVLTreeNodePtr z);

void TestAVLTree();

#endif // AVLTREE_H
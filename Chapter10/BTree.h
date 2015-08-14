#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"

int NodeCount(BTreeNodePtr ptr);

BTreeNodePtr AddTree(BTreeNodePtr ptr, DataType key);
void DestructTree(BTreeNodePtr ptr);
void TreeInOrderVisit(BTreeNodePtr ptr, visit pVisit);
void TreePreOrderVisit(BTreeNodePtr ptr, visit pVisit);
void TreePostOrderVisit(BTreeNodePtr ptr, visit pVisit);

void TreeStackInOrderVisit(BTreeNodePtr ptr, visit pVisit);
void TreeStackPreOrderVisit(BTreeNodePtr ptr, visit pVisit);
void TreeStackPostOrderVisit(BTreeNodePtr ptr, visit pVisit);
void TreeQueueLevelOrderVisit(BTreeNodePtr ptr, visit pVisit);

void TreeEasyInOrderVisit(BTreeNodePtr ptr, visit pVisit);

BTreeNodePtr TreeSearch(BTreeNodePtr ptr, DataType key);
BTreeNodePtr IterativeTreeSearch(BTreeNodePtr ptr, DataType key);

BTreeNodePtr TreeMinimum(BTreeNodePtr ptr);
BTreeNodePtr TreeMaximum(BTreeNodePtr ptr);
BTreeNodePtr IterativeTreeMinimum(BTreeNodePtr ptr);
BTreeNodePtr IterativeTreeMaximum(BTreeNodePtr ptr);

BTreeNodePtr TreeSuccessor(BTreeNodePtr ptr);
BTreeNodePtr TreePredecessor(BTreeNodePtr ptr);

void TestBTree();

#endif // BTREE_H
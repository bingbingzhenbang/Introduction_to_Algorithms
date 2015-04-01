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

void TestBTree();

#endif // BTREE_H
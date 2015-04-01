#ifndef BTREEHEAP_H
#define BTREEHEAP_H

#include "BTree.h"

typedef BTreeNode BTreeHeap;
typedef BTreeNodePtr BTreeHeapPtr;

void SwapNodeData(BTreeHeapPtr p1, BTreeHeapPtr p2);
void MaxHeapify(BTreeHeapPtr ptr);
void GetNoneLeafNodes(BTreeStackPtr pStack, BTreeHeapPtr root);
void InsertNode(BTreeHeapPtr root, BTreeHeapPtr pNode);
void InsertKey(BTreeHeapPtr root, DataType key);
DataType ExtractMax(BTreeHeapPtr root);

void HeapSort(DataType *output, DataType *input, int size);
void TestBTreeHeap();

#endif // BTREEHEAP_H
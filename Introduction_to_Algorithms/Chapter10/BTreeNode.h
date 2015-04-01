#ifndef BTREENODE_H
#define BTREENODE_H

#include "LinkedList.h"

typedef struct BTreeNode
{
	DataType m_data;
	int m_count;
	struct BTreeNode *m_parent;
	struct BTreeNode *m_left;
	struct BTreeNode *m_right;
}BTreeNode;

typedef BTreeNode* BTreeNodePtr;
typedef void (*visit)(BTreeNodePtr ptr);

typedef enum NodeTag
{
	Left,
	Right,
}NodeTag;

typedef struct BTreeListNode
{
	NodeTag m_tag;
	BTreeNodePtr m_nodePtr;
	struct BTreeListNode *m_next;
}BTreeListNode;

typedef BTreeListNode* BTreeListNodePtr;

typedef struct BTreeList
{
	int m_count;
	BTreeListNodePtr m_head;
	BTreeListNodePtr m_tail;
}BTreeList;

typedef BTreeList* BTreeListPtr;

void PrintNode(BTreeNodePtr ptr);
BTreeNodePtr MakeNode(DataType key);

void BTreeListInitial(BTreeListPtr pBL);
void FrontInsertBTreeNode(BTreeListPtr pBL, BTreeNodePtr ptr);
void FrontInsertBTreeListNode(BTreeListPtr pBL, BTreeListNodePtr ptr);
BTreeListNodePtr FrontRemoveBTreeNode(BTreeListPtr pBL);
void BackInsertBTreeNode(BTreeListPtr pBL, BTreeNodePtr ptr);
void BackInsertBTreeListNode(BTreeListPtr pBL, BTreeListNodePtr ptr);
void BTreeListDestruct(BTreeListPtr pBL);

typedef BTreeList BTreeStack;
typedef BTreeListPtr BTreeStackPtr;

void BTreeStackInitial(BTreeStackPtr pS);
void BTreeStackDestruct(BTreeStackPtr pS);
int BTreeStackEmpty(BTreeStackPtr pS);
BTreeNodePtr BTreeStackTop(BTreeStackPtr pS);
BTreeListNodePtr BTreeStackListTop(BTreeStackPtr pS);
BTreeNodePtr BTreeStackPop(BTreeStackPtr pS);
void BTreeStackPush(BTreeStackPtr pS, BTreeNodePtr ptr);

typedef BTreeList BTreeQueue;
typedef BTreeListPtr BTreeQueuePtr;

void BTreeQueueInitial(BTreeQueuePtr pQ);
void BTreeQueueDestruct(BTreeQueuePtr pQ);
int BTreeQueueEmpty(BTreeQueuePtr pQ);
BTreeNodePtr BTreeQueueFront(BTreeQueuePtr pQ);
void BTreeQueueEnqueue(BTreeQueuePtr pQ, BTreeNodePtr ptr);
BTreeNodePtr BTreeQueueDequeue(BTreeQueuePtr pQ);

#endif // BTREENODE_H
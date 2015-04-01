#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAXSIZE 5
typedef int DataType;

typedef struct LinkNode
{
	DataType m_data;
	struct LinkNode *m_next;
}LinkNode;
typedef LinkNode* LinkNodePtr;

typedef struct LinkList
{
	int m_count;
	LinkNodePtr m_head;
	LinkNodePtr m_tail;
}LinkList;
typedef LinkList* LinkListPtr;

typedef struct DLinkNode
{
	DataType m_data;
	struct DLinkNode *m_prev;
	struct DLinkNode *m_next;
}DLinkNode;
typedef DLinkNode* DLinkNodePtr;

typedef struct DLinkList
{
	int m_count;
	DLinkNodePtr m_head;
	DLinkNodePtr m_tail;
}DLinkList;
typedef DLinkList* DLinkListPtr;

void LinkListInitial(LinkListPtr pL);
LinkNodePtr LinkSearch(LinkListPtr pL, DataType key);

void FrontInsertLinkNode(LinkListPtr pL, LinkNodePtr x);
void FrontInsertKey(LinkListPtr pL, DataType key);

void BackInsertLinkNode(LinkListPtr pL, LinkNodePtr x);
void BackInsertKey(LinkListPtr pL, DataType key);

void RemoveLinkNode(LinkListPtr pL, LinkNodePtr x);
void LinkListDestruct(LinkListPtr pL);

void LinkListReverse(LinkListPtr pL);

void TestLinkList();

void DLinkListInitial(DLinkListPtr pL);
DLinkNodePtr DLinkSearch(DLinkListPtr pL, DataType key);

void FrontInsertDLinkNode(DLinkListPtr pL, DLinkNodePtr x);
void FrontInsertDKey(DLinkListPtr pL, DataType key);

void BackInsertDLinkNode(DLinkListPtr pL, DLinkNodePtr x);
void BackInsertDKey(DLinkListPtr pL, DataType key);

void RemoveDLinkNode(DLinkListPtr pL, DLinkNodePtr x);
void DLinkListDestruct(DLinkListPtr pL);

void TestDLinkList();

#endif // LINKEDLIST_H
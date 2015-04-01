#include "BTreeHeap.h"
#include <stdio.h>
#include <stdlib.h>

void SwapNodeData(BTreeHeapPtr p1, BTreeHeapPtr p2)
{
	DataType tempData;
	int tempCnt;

	tempData = p1->m_data;
	p1->m_data = p2->m_data;
	p2->m_data = tempData;

	tempCnt = p1->m_count;
	p1->m_count = p2->m_count;
	p2->m_count = tempCnt;
}

void MaxHeapify(BTreeHeapPtr ptr)
{
	BTreeHeapPtr L, R, maxNode;
	if (ptr)
	{
		L = ptr->m_left;
		R = ptr->m_right;
		maxNode = ptr;
		if (L && L->m_data > ptr->m_data)
			maxNode = L;
		if (R && R->m_data > maxNode->m_data)
			maxNode = R;
		if (maxNode != ptr)
		{
			SwapNodeData(ptr, maxNode);
			MaxHeapify(maxNode);
		}
	}
}

void GetNoneLeafNodes(BTreeStackPtr pStack, BTreeHeapPtr root)
{
	BTreeQueue qQueue;
	BTreeHeapPtr p = root;
	BTreeQueueInitial(&qQueue);
	if (root)
	{
		BTreeQueueEnqueue(&qQueue, p);
		while (!BTreeQueueEmpty(&qQueue))
		{
			p = BTreeQueueFront(&qQueue);
			if (p->m_left || p->m_right)
				BTreeStackPush(pStack, p);

			p = BTreeQueueDequeue(&qQueue);
			if (p->m_left)
				BTreeQueueEnqueue(&qQueue, p->m_left);
			if (p->m_right)
				BTreeQueueEnqueue(&qQueue, p->m_right);
		}
	}
	BTreeQueueDestruct(&qQueue);
	return;
}

void InsertNode(BTreeHeapPtr root, BTreeHeapPtr pNode)
{
	BTreeQueue qQueue;
	BTreeHeapPtr p = root;
	BTreeQueueInitial(&qQueue);
	if (root)
	{
		BTreeQueueEnqueue(&qQueue, p);
		while (!BTreeQueueEmpty(&qQueue))
		{
			p = BTreeQueueFront(&qQueue);
			if (!p->m_left)
			{
				p->m_left = pNode;
				pNode->m_parent = p;
				break;
			}
			if (!p->m_right)
			{
				p->m_right = pNode;
				pNode->m_parent = p;
				break;
			}
			p = BTreeQueueDequeue(&qQueue);
			if (p->m_left)
				BTreeQueueEnqueue(&qQueue, p->m_left);
			if (p->m_right)
				BTreeQueueEnqueue(&qQueue, p->m_right);
		}
	}
	BTreeQueueDestruct(&qQueue);

	p = pNode;
	while (p->m_parent && p->m_parent->m_data < p->m_data)
	{
		SwapNodeData(p, p->m_parent);
		p = p->m_parent;
	}
	return;
}

void InsertKey(BTreeHeapPtr root, DataType key)
{
	BTreeHeapPtr pNode = MakeNode(key);
	InsertNode(root, pNode);
}

DataType ExtractMax(BTreeHeapPtr root)
{
	DataType data = root->m_data;
	BTreeQueue qQueue;
	BTreeHeapPtr p = root;
	BTreeQueueInitial(&qQueue);
	if (root)
	{
		BTreeQueueEnqueue(&qQueue, p);
		while (!BTreeQueueEmpty(&qQueue))
		{
			p = BTreeQueueDequeue(&qQueue);
			if (p->m_left)
				BTreeQueueEnqueue(&qQueue, p->m_left);
			if (p->m_right)
				BTreeQueueEnqueue(&qQueue, p->m_right);
		}
		if (p && p!=root)
		{
			SwapNodeData(root, p);
			if (p == p->m_parent->m_left)
				p->m_parent->m_left = 0;
			else if (p == p->m_parent->m_right)
				p->m_parent->m_right = 0;
			free(p);
			MaxHeapify(root);
		}
	}
	BTreeQueueDestruct(&qQueue);
	return data;
}

void HeapSort(DataType *output, DataType *input, int size)
{
	int i;
	BTreeHeapPtr pHeap=0;
	pHeap = MakeNode(input[0]);

	for (i=1; i<size; ++i)
		InsertKey(pHeap, input[i]);
	for (i=size-1; i>0; --i)
		output[i] = ExtractMax(pHeap);
	output[0] = pHeap->m_data;

	free(pHeap);
}

void TestBTreeHeap()
{
	FILE *fp = fopen("input", "r");
	int i, size;
	DataType *input, *output;
	if (fp == NULL)
	{
		printf("cannot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	input = (DataType *)malloc(size * sizeof(DataType));
	output = (DataType *)malloc(size * sizeof(DataType));

	for (i=0; i<size; ++i)
		fscanf(fp, "%d", input+i);
	HeapSort(output, input, size);
	for (i=0; i<size; ++i)
		printf("%d\n", output[i]);

	free(input);
	free(output);
	fclose(fp);
}
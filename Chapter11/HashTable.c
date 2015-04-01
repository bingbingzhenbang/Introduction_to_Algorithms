#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DivisionFunction(KeyType key)
{
	return key % HASHTABLESIZE;
}

void HashTableInitial(HashTablePtr pHT)
{
	int i;
	for (i=0; i < HASHTABLESIZE; ++i)
		(*pHT)[i] = 0;
}

void HashTableDestruct(HashTablePtr pHT)
{
	int i;
	DLinkNodePtr p, q;
	for (i=0; i < HASHTABLESIZE; ++i)
	{
		for (p=(*pHT)[i]; p!=0; p=q)
		{
			q = p->m_next;
			free(p);
		}
		(*pHT)[i]=0;
	}
}

DLinkNodePtr HashTableSearch(HashTablePtr pHT, KeyType key, HashFunction pHash)
{
	DLinkNodePtr ptr;
	for (ptr=(*pHT)[pHash(key)]; ptr!=0 && ptr->m_key != key; ptr=ptr->m_next)
		;
	return ptr;
}

DLinkNodePtr HashTableInsert(HashTablePtr pHT, KeyType key, HashFunction pHash)
{
	DLinkNodePtr pNode = (DLinkNodePtr)malloc(sizeof(DLinkNode));
	DLinkNodePtr pHead = (*pHT)[pHash(key)];
	pNode->m_key = key;
	pNode->m_prev = 0;
	pNode->m_next = 0;
	if (pHead)
	{
		pHead->m_prev = pNode;
		pNode->m_next = pHead;
	}
	(*pHT)[pHash(key)] = pNode;
	return pNode;
}

DLinkNodePtr HashTableRemoveNode(HashTablePtr pHT, DLinkNodePtr ptr, HashFunction pHash)
{
	if (ptr == (*pHT)[pHash(ptr->m_key)])
		(*pHT)[pHash(ptr->m_key)] = ptr->m_next;
	if (ptr->m_next)
		ptr->m_next->m_prev = ptr->m_prev;
	if (ptr->m_prev)
		ptr->m_prev->m_next = ptr->m_next;
	return ptr;
}

DLinkNodePtr HashTableRemoveKey(HashTablePtr pHT, KeyType key, HashFunction pHash)
{
	DLinkNodePtr p;
	p = HashTableSearch(pHT, key, pHash);
	if (p)
		p = HashTableRemoveNode(pHT, p, pHash);
	return p;
}

void TestHashTable()
{
	HashTable table;
	DLinkNodePtr p;
	KeyType x;
	FILE *fp = fopen("input", "r");
	HashTableInitial(&table);
	fscanf(fp,"%d", &x);
	while (x!=-1)
	{
		HashTableInsert(&table, x, DivisionFunction);
		fscanf(fp,"%d", &x);
	}
	printf("input key!\n");
	scanf("%d", &x);
	while (x!=-1)
	{
		p = HashTableRemoveKey(&table, x, DivisionFunction);
		if (p)
		{
			printf("p key:\n%d\n", p->m_key);
			free(p);
		}
		else
			printf("Not Found!\n");
		printf("input key!\n");
		scanf("%d", &x);
	}
	fclose(fp);
	HashTableDestruct(&table);
	return;
}
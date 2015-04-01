#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"

#define HASHTABLESIZE 9

typedef DLinkNodePtr HashTable[HASHTABLESIZE];

typedef HashTable* HashTablePtr;

int DivisionFunction(KeyType key);
void HashTableInitial(HashTablePtr pHT);
void HashTableDestruct(HashTablePtr pHT);
DLinkNodePtr HashTableSearch(HashTablePtr pHT, KeyType key, HashFunction pHash);
DLinkNodePtr HashTableInsert(HashTablePtr pHT, KeyType key, HashFunction pHash);
DLinkNodePtr HashTableRemoveNode(HashTablePtr pHT, DLinkNodePtr ptr, HashFunction pHash);
DLinkNodePtr HashTableRemoveKey(HashTablePtr pHT, KeyType key, HashFunction pHash);
void TestHashTable();

#endif // HASHTABLE_H
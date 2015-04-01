#ifndef BUCKETSORT_H
#define BUCKETSORT_H

typedef double DataType;

typedef struct BucketNode
{
	DataType m_value;
	struct BucketNode *m_next;
}BucketNode;

typedef BucketNode* BucketNodePtr;

void BucketSort(DataType *array, int size);

void TestBucketSort();

#endif // BUCKETSORT_H
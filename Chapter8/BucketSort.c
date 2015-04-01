#include "BucketSort.h"
#include <stdio.h>
#include <stdlib.h>

void BucketSort(DataType *array, int size)
{
	int i, j;
	BucketNodePtr *bucketArray;
	BucketNodePtr p, q, r;

	bucketArray = (BucketNodePtr *)malloc(size * sizeof(BucketNodePtr));
	for (i=0; i<size; ++i)
		bucketArray[i] = NULL;

	for (i=0; i<size; ++i)
	{
		j = size * array[i];
		p = bucketArray[j];
		q = NULL;

		r = (BucketNodePtr)malloc(sizeof(BucketNode));
		r->m_value = array[i];
		r->m_next = NULL;

		while (p != NULL && p->m_value<=array[i])
		{
			q = p;
			p = p->m_next;
		}

		if (q != NULL)
		{
			q->m_next = r;
			r->m_next = p;
		}
		else
		{
			r->m_next = p;
			bucketArray[j] = r;
		}
	}

	j=0;
	for (i=0; i<size; i++)
	{
		p = bucketArray[i];
		while (p!=NULL)
		{
			array[j++] = p->m_value;
			p = p->m_next;
		}
	}

	for (i=0; i<size; ++i)
	{
		p = bucketArray[i];
		while (p != NULL)
		{
			q = p->m_next;
			free(p);
			p = q;
		}
	}
	free(bucketArray);
}

void TestBucketSort()
{
	int i, size;
	DataType *array;
	FILE *fp = fopen("bucket_sort_input", "r");
	printf("Test bucket time sort!\n");
	if (fp == NULL)
	{
		printf("cannot open file!\n");
		return;
	}

	fscanf(fp, "%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		fscanf(fp, "%lf", array + i);

	BucketSort(array, size);
	
	for (i=0; i<size; ++i)
		printf("%f\n", array[i]);

	fclose(fp);
	free(array);
}
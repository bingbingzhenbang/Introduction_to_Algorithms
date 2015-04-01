#include <stdio.h>
#include <stdlib.h>
#include "decla.h"

int main()
{
	FILE *fp;
	int size, i, cnt1, cnt2;
	Item *array;

	fp = fopen("sort_input", "r");
	if (fp==NULL)
	{
		printf("cannot open sort_input\n");
		return -1;
	}

	fscanf(fp, "%d", &size);
	if (size<0)
	{
		printf("invalid array size!\n");
		return -1;
	}
	array = (Item*)malloc(size * sizeof (Item));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", array+i);
	fclose(fp);

	cnt1 = InversionTest(array, size);
	cnt2 = InversionCount(array, 0, size - 1);
	printf("answer %d pairs \n%d pairs of inversion in array\n", cnt1, cnt2);
	//fp = fopen("sort_output", "w");
	//fprintf(fp, "%d\n", size);
	//for (i=0; i<size; ++i)
	//	fprintf(fp, "%d ", *(array+i));
	//fclose(fp);
	free(array);

	return 0;
}
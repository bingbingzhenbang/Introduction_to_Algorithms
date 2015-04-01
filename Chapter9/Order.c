#include "Order.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(DataType *d1, DataType *d2)
{
	DataType temp;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

DataType GetMin(DataType *array, int size)
{
	int i;
	DataType mini = array[0];
	for (i=1; i<size; ++i)
	{
		if (array[i] < mini)
			mini = array[i];
	}
	return mini;
}

DataType GetMax(DataType *array, int size)
{
	int i;
	DataType maxi = array[0];
	for (i=1; i<size; ++i)
	{
		if (array[i] > maxi)
			maxi = array[i];
	}
	return maxi;
}

MPair GetMaxAndMin(DataType *array, int size)
{
	MPair pair;
	DataType tempMin, tempMax;
	int i, begin;
	if (size%2==1)
	{
		pair.m_Min = pair.m_Max = array[0];
		begin = 1;
	}
	else
	{
		pair.m_Min = MIN(array[0], array[1]);
		pair.m_Max = MAX(array[0], array[1]);
		begin = 2;
	}
	for (i=begin; i<size-1; i += 2)
	{
		tempMin = MIN(array[i], array[i+1]);
		tempMax = MAX(array[i], array[i+1]);
		pair.m_Min = MIN(pair.m_Min, tempMin);
		pair.m_Max = MAX(pair.m_Max, tempMax);
	}

	return pair;
}

void GetMinAndSecdondMin(DataType *array, int size, DataType *min, DataType *secondMin)
{
	int i, j, levelBegin, levelEnd, levelSize, comparedCnt=0, totalCnt=2*size-1;
	CompareNodePtr compareList = (CompareNodePtr)malloc(totalCnt * sizeof(CompareNode));
	DataType tempMin;

	for (i=0; i<size; ++i)
	{
		compareList[comparedCnt].m_Value = array[i];
		compareList[comparedCnt].m_PrevIndex = -1;
		compareList[comparedCnt].m_DefeatedIndex = -1;
		++comparedCnt;
	}

	levelBegin = 0;

	while (comparedCnt < totalCnt)
	{
		levelEnd = comparedCnt-1;
		levelSize = levelEnd - levelBegin + 1;

		if (levelSize %2 == 0)
		{
			for (i=levelBegin; i<=levelEnd-1; i += 2)
			{
				if (compareList[i].m_Value < compareList[i+1].m_Value)
				{
					compareList[comparedCnt].m_Value = compareList[i].m_Value;
					compareList[comparedCnt].m_PrevIndex = i;
					compareList[comparedCnt].m_DefeatedIndex = i+1;
					++comparedCnt;
				}
				else if (compareList[i].m_Value > compareList[i+1].m_Value)
				{
					compareList[comparedCnt].m_Value = compareList[i+1].m_Value;
					compareList[comparedCnt].m_PrevIndex = i+1;
					compareList[comparedCnt].m_DefeatedIndex = i;
					++comparedCnt;
				}
			}
			levelBegin = levelEnd + 1;
		}
		else
		{
			for (i=levelBegin; i<=levelEnd-2; i += 2)
			{
				if (compareList[i].m_Value < compareList[i+1].m_Value)
				{
					compareList[comparedCnt].m_Value = compareList[i].m_Value;
					compareList[comparedCnt].m_PrevIndex = i;
					compareList[comparedCnt].m_DefeatedIndex = i+1;
					++comparedCnt;
				}
				else if (compareList[i].m_Value > compareList[i+1].m_Value)
				{
					compareList[comparedCnt].m_Value = compareList[i+1].m_Value;
					compareList[comparedCnt].m_PrevIndex = i+1;
					compareList[comparedCnt].m_DefeatedIndex = i;
					++comparedCnt;
				}
			}
			levelBegin = levelEnd;
		}
	}

	*min = compareList[totalCnt-1].m_Value;

	tempMin=compareList[compareList[totalCnt-1].m_DefeatedIndex].m_Value;

	for (i=compareList[totalCnt-1].m_PrevIndex, j=compareList[i].m_DefeatedIndex; 
		j != -1; i=compareList[i].m_PrevIndex, 	j=compareList[i].m_DefeatedIndex)
	{
		if (compareList[j].m_Value < tempMin)
			tempMin = compareList[j].m_Value;
	}

	*secondMin = tempMin;

	free(compareList);
}

void DeterminGetMinAndSecdondMin(DataType *array, int size, DataType *Min, DataType *secondMin)
{
	int i, j, k;
	DataType key;
	for (i=0; i<2; ++i)
	{
		k = i;
		key = array[i];
		for (j=i+1; j<size; ++j)
		{
			if (array[j] < array[k])
				k = j;
		}
		array[i] = array[k];
		array[k] = key;
	}
	*Min = array[0];
	*secondMin = array[1];
}

void EasyGetMinAndSecdondMin(DataType *array, int size, DataType *min, DataType *secondMin)
{
	DataType Min, SecondMin;
	int i;

	if (array[0] < array[1])
	{
		Min = array[0];
		SecondMin = array[1];
	}
	else
	{
		Min = array[1];
		SecondMin = array[0];
	}

	for (i=2; i<size; ++i)
	{
		if (array[i] < Min)
		{
			SecondMin = Min;
			Min = array[i];
		}
		else if (array[i] < SecondMin)
			SecondMin = array[i];
	}

	*min = Min;
	*secondMin = SecondMin;
}

int Partion(DataType *array, int begin, int end)
{
	int i, j;
	DataType x;

	x = array[end];

	for (i=begin-1, j=begin; j<=end-1; ++j)
	{
		if (array[j] <= x)
			Swap(&array[++i], &array[j]);
	}
	Swap(&array[++i], &array[end]);

	return i;
}

int RandomPartion(DataType *array, int begin, int end)
{
	int i, j, k;
	DataType x;
	k = begin + (double)rand()/RAND_MAX * (end - begin);

	Swap(&array[k], &array[end]);
	
	x = array[end];

	for (i=begin-1, j=begin; j<=end-1; ++j)
	{
		if (array[j] <= x)
			Swap(&array[++i], &array[j]);
	}
	Swap(&array[++i], &array[end]);

	return i;
}

DataType RandomSelect(DataType *array, int begin, int end, int i)
{
	int q, k;
	if (begin == end)
		return array[begin];

	q = RandomPartion(array, begin, end);
	k = q - begin + 1;

	if (k==i)
		return array[q];
	else if (i<k)
		return RandomSelect(array, begin, q-1, i);
	else
		return RandomSelect(array, q+1, end, i-k);
}

DataType LoopRandomSelect(DataType *array, int begin, int end, int i)
{
	int q, k;

	while (begin<end)
	{
		q = RandomPartion(array, begin, end);
		k = q - begin + 1;

		if (k==i)
			return array[q];
		else if (i<k)
			end = q-1;
		else
		{
			begin = q+1;
			i = i-k;
		}
	}
	return array[begin];
}

void InsertSort(DataType *array, int begin, int end)
{
	int i, j;
	DataType key;
	for (j=begin+1; j<=end; ++j)
	{
		key = array[j];
		for (i=j-1; i>=0 && array[i]>key; --i)
			array[i+1] = array[i];
		array[i+1] = key;
	}
}

DataType Select(DataType *array, int begin, int end, int nth)
{
	DataType midData = 0, *midArray;
	int size, midSize, i, k, q, midBegin, choose;

	while (begin < end)
	{
		size = end - begin + 1;

		if (size % LEN == 0)
			midSize = size/LEN;
		else
			midSize = size/LEN + 1;

		midArray = (DataType *)malloc(midSize * sizeof(DataType));

		for (i=0, midBegin=begin, choose=begin+LEN/2; i<midSize-1; ++i, midBegin += LEN, choose += LEN)
		{
			InsertSort(array, midBegin, midBegin+LEN-1);
			midArray[i] = array[choose];
		}
		InsertSort(array, midBegin, end);
		midArray[i] = array[midBegin + (end-midBegin)/2];

		midData = Select(midArray, 0, midSize-1, (midSize+1)/2);
		free(midArray);

		for (i=begin; i<=end && array[i]!=midData; ++i)
			;

		Swap(&array[i], &array[end]);

		q = Partion(array, begin, end);
		k = q - begin + 1;

		if (k==nth)
			return array[q];
		else if (nth<k)
			end = q-1;
		else
		{
			begin = q+1;
			nth -= k;
		}
	}
	return array[begin];
}

void MidQuickSort(DataType *array, int begin, int end)
{
	int q, i;
	DataType x;
	if (begin < end)
	{
		i = (end - begin + 1)/2;
		x = Select(array, begin, end, i);
		q = begin + i-1;
		MidQuickSort(array, begin, q-1);
		MidQuickSort(array, q+1, end);
	}
}

DataType GetMid(DataType *array, int begin, int end)
{
	int i = (end - begin)/2 + 1;
	return Select(array, begin, end, i);
}

void KthQuantile(DataType *array, int begin, int end, DataType *quantile, int quanbegin, int quanend, int len)
{
	int quanMid = (quanend - quanbegin)/2 + quanbegin;
	int j = (quanMid + 1) * len;
	if (begin < end && quanbegin <= quanend)
	{
		quantile[quanMid] = Select(array, begin, end, j-begin);
		KthQuantile(array, begin, j-1, quantile, quanbegin, quanMid-1, len);
		KthQuantile(array, j+1, end, quantile, quanMid+1, quanend, len);
	}
}

void DeterminKthQuantile(DataType *array, int arraysize, DataType *quantile, int quan)
{
	int i, j;
	int len = (double)arraysize/quan;
	for (i=0, j=len; i<quan-1; ++i, j += len)
		quantile[i] = Select(array, 0, arraysize-1, j);
}

DataType MergeMid(DataType *X, DataType *Y, int size)
{
	DataType a = 0;

	int k;

	if ((k=FindMedian(X, Y, size, 0, size-1))!=-1)
		a = X[k];
	else
	{
		k=FindMedian(Y, X, size, 0, size-1);
		a = Y[k];
	}

	return a;
}

int FindMedian(DataType *X, DataType *Y, int size, int begin, int end)
{
	int k = -1;
	int low = begin, high = end;
	while (low <= high)
	{
		k = (low + high) / 2;
		if (k==size-1 && X[k]<=Y[0])
			return k;
		else
		{
			if (Y[size-k-2] <= X[k] && X[k] <= Y[size-k-1])
				return k;
			else if (X[k] > Y[size-k-1])
				high = k-1;
			else
				low = k+1;
		}
	}
	return -1;
}

void TestMaxAndMin()
{
	FILE *fp = fopen("input", "r");
	int i, size;
	DataType *array;
	DataType minu, maxi;
	MPair pair;
	printf("Test order statistics!\n");
	if (fp == NULL)
	{
		printf("cannot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", array+i);

	minu = GetMin(array, size);
	maxi = GetMax(array, size);

	pair = GetMaxAndMin(array, size);

	printf("max = %d\nmin = %d\nmax = %d\tmin = %d\n", maxi, minu, pair.m_Max, pair.m_Min);

	free(array);
	fclose(fp);
}

void TestMinAndSecdondMin()
{
	FILE *fp = fopen("input", "r");
	int i, size;
	DataType *array;
	DataType mini, secmini;
	printf("Test order statistics!\n");
	if (fp == NULL)
	{
		printf("cannot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", array+i);

	mini = 0; secmini = 0;

	DeterminGetMinAndSecdondMin(array, size, &mini, &secmini);

	printf("min = %3d\tsecond min = %3d\n", mini, secmini);

	mini = 0; secmini = 0;

	GetMinAndSecdondMin(array, size, &mini, &secmini);

	printf("min = %3d\tsecond min = %3d\n", mini, secmini);

	mini = 0; secmini = 0;

	EasyGetMinAndSecdondMin(array, size, &mini, &secmini);

	printf("min = %3d\tsecond min = %3d\n", mini, secmini);

	free(array);
	fclose(fp);
}

void TestRandomSelect()
{
	time_t t;
	int i, k, size;
	DataType *array;
	DataType mini;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");
	printf("input size:\n");
	scanf("%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		array[i] = i+1;

	for (i=0; i<size; ++i)
	{
		k = i + (double)rand()/RAND_MAX * (size - 1 - i);
		Swap(&array[i], &array[k]);
	}

	printf("input i:\n");
	scanf("%d", &i);

	mini = RandomSelect(array, 0, size-1, i);

	printf("%d th smallest = %d\n", i, mini);

	mini = -1;

	mini = LoopRandomSelect(array, 0, size-1, i);

	printf("%d th smallest = %d\n", i, mini);

	free(array);
}

void TestMidQuickSort()
{
	time_t t;
	int i, k, size;
	DataType *array;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");
	printf("input size:\n");
	scanf("%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		array[i] = i+1;

	for (i=0; i<size; ++i)
	{
		k = i + (double)rand()/RAND_MAX * (size - 1 - i);
		Swap(&array[i], &array[k]);
	}

	printf("Before sort:\n");
	for (i=0; i<size; ++i)
		printf("%d\n", array[i]);

	MidQuickSort(array, 0, size-1);
	printf("After sort:\n");
	for (i=0; i<size; ++i)
		printf("%d\n", array[i]);

	free(array);
}

void TestKthQuantile()
{
	time_t t;
	int i, k, size, quan, len;
	DataType *array, *quantiles;
	DataType mid;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");
	printf("input size:\n");
	scanf("%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		array[i] = i+1;

	printf("input quantile:\n");
	scanf("%d", &quan);
	quantiles = (DataType *)malloc((quan - 1) * sizeof(DataType));
	for (i=0; i<quan-1; ++i)
		quantiles[i] = 0;

	for (i=0; i<size; ++i)
	{
		k = i + (double)rand()/RAND_MAX * (size - 1 - i);
		Swap(&array[i], &array[k]);
	}

	mid = GetMid(array, 0, size-1);
	printf("Mid = %d:\n", mid);
	printf("\n");

	DeterminKthQuantile(array, size, quantiles, quan);
	for (i=0; i<quan-1; ++i)
		printf("%d\n", quantiles[i]);
	printf("\n");

	for (i=0; i<quan-1; ++i)
		quantiles[i] = 0;

	len = (double)size/quan;
	KthQuantile(array, 0, size-1, quantiles, 0, quan-2, len);
	for (i=0; i<quan-1; ++i)
		printf("%d\n", quantiles[i]);

	free(array);
	free(quantiles);
}

void TestMergeMid()
{
	FILE *fp = fopen("mid_input", "r");
	int i, size;
	DataType *x, *y;
	DataType mid;
	printf("Test order statistics!\n");
	if (fp == NULL)
	{
		printf("cannot open file!\n");
		return;
	}
	fscanf(fp, "%d", &size);
	x = (DataType *)malloc(size * sizeof(DataType));
	y = (DataType *)malloc(size * sizeof(DataType));
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", x+i);
	for (i=0; i<size; ++i)
		fscanf(fp, "%d", y+i);

	mid = MergeMid(x, y, size);

	printf("Mid=%d\n", mid);

	printf("X\n");
	for (i=0; i<size; ++i)
		printf("%d\n", x[i]);
	printf("Y\n");
	for (i=0; i<size; ++i)
		printf("%d\n", y[i]);

	free(x);
	free(y);
	fclose(fp);
}

void TestSelect()
{
	time_t t;
	int i, k, size, nth;
	DataType *array, data;
	srand((unsigned)time(&t));

	printf("Test order statistics!\n");
	printf("input size:\n");
	scanf("%d", &size);
	array = (DataType *)malloc(size * sizeof(DataType));

	printf("input nth, -1 to end:\n");
	scanf("%d", &nth);
	while (nth != -1)
	{
		for (i=0; i<size; ++i)
			array[i] = i+1;
		for (i=0; i<size; ++i)
		{
			k = i + (double)rand()/RAND_MAX * (size - 1 - i);
			Swap(&array[i], &array[k]);
		}

		data = Select(array, 0, size-1, nth);

		printf("%d th\t%d\n", nth, data);
		printf("input nth, -1 to end:\n");
		scanf("%d", &nth);
	}
	free(array);
}
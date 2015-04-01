#include "CheckArray.h"
#include <stdlib.h>
#include <math.h>

static int AllData[MAXNUM + 1];

int CheckData()
{
	int maxBit = log((double)MAXNUM)/log(2.0) + 1;
	int i, j, k, cntData, cntAllData, dataIndexNum, allDataIndexNum;
	int tempDataIndexNum, tempAllDataIndexNum;
	int *dataIndex, *allDataIndex, *tempDataIndex, *tempAllDataIndex;
	int result;

	for (i=0; i<MAXNUM+1; ++i)
		AllData[i] = i;

	dataIndexNum = MAXNUM;
	allDataIndexNum = MAXNUM+1;
	dataIndex = (int*)malloc(dataIndexNum*sizeof(int));
	allDataIndex = (int*)malloc(allDataIndexNum*sizeof(int));
	for (i=0; i<dataIndexNum; ++i)
		dataIndex[i] = i;
	for (i=0; i<allDataIndexNum; ++i)
		allDataIndex[i] = i;

	for (j=1; j<=maxBit && allDataIndexNum>1; ++j)
	{
		cntData = 0;
		cntAllData = 0;

		for (i=0; i<dataIndexNum; ++i)
		{
			if (FindDataBit(dataIndex[i], j))
				++cntData;
		}

		for (i=0; i<allDataIndexNum; ++i)
		{
			if ((AllData[allDataIndex[i]] >> j) & 1)
				++cntAllData;
		}
		
		if (cntData == cntAllData)   //the j-th bit of the abscent value is zero
		{
			tempDataIndexNum = dataIndexNum - cntData;
			tempAllDataIndexNum = allDataIndexNum - cntAllData;

			tempDataIndex = (int*)malloc(tempDataIndexNum * sizeof(int));
			tempAllDataIndex = (int*)malloc(tempAllDataIndexNum * sizeof(int));

			for (i=0, k=0; i<dataIndexNum; ++i)
			{
				if (!FindDataBit(dataIndex[i], j))   // if not zero
					tempDataIndex[k++] = dataIndex[i];
			}

			for (i=0, k=0; i<allDataIndexNum; ++i)
			{
				if (!((AllData[allDataIndex[i]] >> j) & 1))
					tempAllDataIndex[k++] = allDataIndex[i];
			}

			dataIndexNum = tempDataIndexNum;
			allDataIndexNum = tempAllDataIndexNum;
			free(dataIndex);
			free(allDataIndex);

			dataIndex = tempDataIndex;
			allDataIndex = tempAllDataIndex;
		}
		else  //the j-th bit of the abscent value is zero
		{
			tempDataIndexNum = cntData;
			tempAllDataIndexNum = cntAllData;

			tempDataIndex = (int*)malloc(tempDataIndexNum * sizeof(int));
			tempAllDataIndex = (int*)malloc(tempAllDataIndexNum * sizeof(int));

			for (i=0, k=0; i<dataIndexNum; ++i)
			{
				if (FindDataBit(dataIndex[i], j))   // if not zero
					tempDataIndex[k++] = dataIndex[i];
			}

			for (i=0, k=0; i<allDataIndexNum; ++i)
			{
				if ((AllData[allDataIndex[i]] >> j) & 1)
					tempAllDataIndex[k++] = allDataIndex[i];
			}

			dataIndexNum = tempDataIndexNum;
			allDataIndexNum = tempAllDataIndexNum;
			free(dataIndex);
			free(allDataIndex);

			dataIndex = tempDataIndex;
			allDataIndex = tempAllDataIndex;
		}
	}
	result = AllData[allDataIndex[0]];

	free(dataIndex);
	free(allDataIndex);

	return result;
}
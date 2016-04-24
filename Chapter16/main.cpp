#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testActivitySelectionProblem();
void testKnapsack();
void testMaximizePayoff();
void testHuffmanCodes();
void testCoinChange();

int main()
{
	//testActivitySelectionProblem();
	//testKnapsack();
	//testMaximizePayoff();
	//testHuffmanCodes();
	testCoinChange();
	_CrtDumpMemoryLeaks();
	return 0;
}
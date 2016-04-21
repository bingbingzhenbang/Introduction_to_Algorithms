#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testActivitySelectionProblem();
void testKnapsack();
void testMaximizePayoff();
void testHuffmanCodes();

int main()
{
	//testActivitySelectionProblem();
	//testKnapsack();
	//testMaximizePayoff();
	testHuffmanCodes();
	_CrtDumpMemoryLeaks();
	return 0;
}
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Test.h"

int main()
{
	//testAdjacencylistGraph();
	//testAdjacencymatrixGraph();
	//testBFS();
	//testBFSTraverse();
	//testDFS();
	//testTopologicalSort();
	//testStronglyConnectedComponents();
	testComponentGraph();
	_CrtDumpMemoryLeaks();
	return 0;
}
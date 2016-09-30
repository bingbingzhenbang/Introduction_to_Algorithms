#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testLinkedlistDisjointSet();

int main()
{
	testLinkedlistDisjointSet();
	_CrtDumpMemoryLeaks();
	return 0;
}
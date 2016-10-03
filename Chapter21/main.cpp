#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testLinkedlistDisjointSet();
void testArrayDisjointSet();

int main()
{
	testLinkedlistDisjointSet();
	testArrayDisjointSet();
	_CrtDumpMemoryLeaks();
	return 0;
}
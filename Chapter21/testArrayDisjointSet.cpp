#include "ArrayDisjointSet.h"
#include <iostream>

using namespace std;

void testArrayDisjointSet()
{
	const int N = 16;
	ArrayDisjointSet s(N);
	for (int i = 0; i < N - 1; i += 2)
		s.Union(i, i + 1);
	for (int i = 0; i < N - 3; i += 4)
		s.Union(i, i + 2);
	s.Union(0, 4);
	s.Union(10, 12);
	cout << "testArrayDisjointSet :" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (s.FindSet(i) == s.FindSet(1))
			cout << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < N; ++i)
	{
		if (s.FindSet(i) == s.FindSet(8))
			cout << i + 1 << " ";
	}
	cout << endl;
}
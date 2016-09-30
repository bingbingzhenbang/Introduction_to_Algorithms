#include "LinkedlistDisjointSet.h"
#include <vector>
#include <iostream>

using namespace std;

void testLinkedlistDisjointSet()
{
	const int N = 16;
	vector<int> data(N);
	vector< shared_ptr<DisjointSetListElement<int> > > allsets;
	for (int i = 0; i < N; ++i)
	{
		data[i] = i;
		allsets.push_back(shared_ptr< DisjointSetListElement<int> >(new DisjointSetListElement<int>(i)));
	}
	for (int i = 0; i < N; ++i)
		MakeLinkedlistDisjointSet(allsets[i]);
	for (int i = 0; i < N - 1; i += 2)
		UnionLinkedlistDisjointSet(allsets[i], allsets[i + 1]);
	for (int i = 0; i < N - 3; i += 4)
		UnionLinkedlistDisjointSet(allsets[i], allsets[i + 2]);
	UnionLinkedlistDisjointSet(allsets[0], allsets[4]);
	UnionLinkedlistDisjointSet(allsets[10], allsets[12]);
	//Union(allsets[0], allsets[9]);
	shared_ptr< LinkedlistDisjointSet<int> > s1 = FindLinkedlistDisjointSet(allsets[1]);
	for (auto itr = s1->m_list.begin(); itr != s1->m_list.end(); ++itr)
		cout << (*itr)->m_object + 1 << " ";
	cout << endl;
	shared_ptr< LinkedlistDisjointSet<int> > s2 = FindLinkedlistDisjointSet(allsets[8]);
	for (auto itr = s2->m_list.begin(); itr != s2->m_list.end(); ++itr)
		cout << (*itr)->m_object + 1 << " ";
	cout << endl;
}
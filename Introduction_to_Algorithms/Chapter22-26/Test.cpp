#include "Test.h"
#include "Graph.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

void testAdjacencylistGraph()
{
	vector< vector<int> > m1 = { { 0, 1, 0, 0, 1 }, { 1, 0, 1, 1, 1 }, { 0, 1, 0, 1, 0 }, { 0, 1, 1, 0, 1 }, { 1, 1, 0, 1, 0 } };
	AdjacencylistGraph g1(m1, false);
	vector< vector<int> > m2 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	AdjacencylistGraph g2(m2, true);
	AdjacencylistGraph g3 = g2.Transpose();
	AdjacencylistGraph g4 = g2.ToUndirected();
	AdjacencylistGraph g5 = g3.ToUndirected();
	AdjacencylistGraph g6 = g3.Square();
}

void testAdjacencymatrixGraph()
{
	vector< vector<int> > m1 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	AdjacencymatrixGraph g1(m1, true);
	AdjacencymatrixGraph g2 = g1.Transpose();
	AdjacencylistGraph g3(g2.GetMatrixRef(), true);
	AdjacencymatrixGraph g4 = g2.Square();
	vector< vector<int> > m2 = { { 0, 0, 0, 0 }, { 1, 0, 1, 0 }, { 1, 0, 0, 1 }, { 1, 0, 0, 0 } };
	AdjacencymatrixGraph g5(m2, true);
	bool rt0 = g4.BruteUniversalSinkExist();
	bool rt1 = g4.UniversalSinkExist();
	bool rt2 = g5.BruteUniversalSinkExist();
	bool rt3 = g5.UniversalSinkExist();
}

void testBFS()
{
	vector< vector<int> > m1 = { { 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 1, 0, 1, 0, 1 },
	{ 0, 0, 0, 1, 0, 0, 1, 0 }
	};
	AdjacencylistGraph g1(m1, false);
	vector<int> parent, distance;
	g1.BFS(parent, distance, 1);
	//g1.BFS(parent, distance, 3);
	//vector< vector<int> > m2 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	//AdjacencylistGraph g2(m2, true);
	//g2.BFS(parent, distance, 2);
	vector<int> mparent, mdistance;
	AdjacencymatrixGraph g3(m1, false);
	g3.BFS(mparent, mdistance, 1);
	//AdjacencymatrixGraph g4(m2, true);
	//g4.BFS(mparent, mdistance, 2);
	if (parent == mparent && distance == mdistance)
		cout << "Correct !" << endl;
	else
		cout << "Error !" << endl;
}

void testBFSTraverse()
{
	vector< vector<int> > m1 = { { 0, 1, 1, 0, 0, 0 },
	{ 1, 0, 0, 1, 1, 0 },
	{ 1, 0, 0, 0, 1, 1 },
	{ 0, 1, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 0 }
	};
	AdjacencylistGraph g1(m1, false);
	vector<int> path;
	//g1.BFSTraverse(path, 0);
}

void testDFS()
{
	//vector< vector<int> > m1 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	vector< vector<int> > m1 = {
//     0  1  2  3  4  5  6  7  8  9 
/*0*/{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
/*1*/{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
/*2*/{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
/*3*/{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
/*4*/{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
/*5*/{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
/*6*/{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
/*7*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
/*8*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/*9*/{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }
	};
	AdjacencylistGraph g1(m1, true);
	vector<int> parent1, d1, f1, parent2, d2, f2;
	g1.DFS(parent1, d1, f1);
	g1.StackDFS(parent2, d2, f2);
	if (parent1 == parent2 && d1 == d2 && f1 == f2)
		cout << "Correct !" << endl;
	else
		cout << "Error !" << endl;
}

void testTopologicalSort()
{
	vector< vector<int> > m1 = {
		//     0  1  2  3  4  5  6  7  8  9 10 11 12 13 
		/*0*/{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
		/*1*/{ 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		/*2*/{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0 },
		/*3*/{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		/*4*/{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		/*5*/{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
		/*6*/{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*7*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*8*/{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		/*9*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
	   /*10*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	   /*11*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
       /*12*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	   /*13*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	AdjacencylistGraph g1(m1, true);
	list<int> rt1 = g1.TopologicalSort();
	//int num = g1.PathsNumber(3, 9);
	//num = g1.PathsNumber(3, 13);
	list<int> rt2 = g1.QueueTopologicalSort();
	for (auto itr = rt2.begin(); itr != rt2.end(); ++itr)
	{
		cout << (char)('m' + *itr) << " ";
	}
	cout << endl;
}

void testStronglyConnectedComponents()
{
	vector< vector<int> > m1 = {
		//     0  1  2  3  4  5  6  7   
		/*0*/{ 0, 1, 0, 0, 0, 0, 0, 0 },
		/*1*/{ 0, 0, 1, 0, 1, 1, 0, 0 },
		/*2*/{ 0, 0, 0, 1, 0, 0, 1, 0 },
		/*3*/{ 0, 0, 1, 0, 0, 0, 0, 1 },
		/*4*/{ 1, 0, 0, 0, 0, 1, 0, 0 },
		/*5*/{ 0, 0, 0, 0, 0, 0, 1, 0 },
		/*6*/{ 0, 0, 0, 0, 0, 1, 0, 1 },
		/*7*/{ 0, 0, 0, 0, 0, 0, 0, 1 },
	};
	AdjacencylistGraph g1(m1, true);
	vector<int> parent = g1.StronglyConnectedComponents();
}
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <limits.h>

enum EnumNodeColor
{
	EnumNodeColor_white,
	EnumNodeColor_gray,
	EnumNodeColor_black,
};

struct Edge;

struct Vertex
{
	std::list<Edge> m_edges;
};

struct Edge
{
	int m_start;
	int m_end;
	int m_weight;
	Edge(int start = -1, int end = -1, int weight = INT_MAX)
		: m_start(start), m_end(end), m_weight(weight){}
};

inline bool operator==(const Edge &left, const Edge &right)
{
	return (left.m_start == right.m_start) && (left.m_end == right.m_end);
}

inline bool operator<(const Edge &left, const Edge &right)
{
	if (left.m_start == right.m_start)
		return left.m_end < right.m_end;
	return left.m_start < right.m_start;
}

inline bool WeightLess(const Edge &left, const Edge &right)
{
	if (left.m_weight == right.m_weight)
		return left < right;
	return left.m_weight < right.m_weight;
}

class AdjacencylistGraph
{
private:
	bool m_directed;
	std::vector<Vertex> m_vertexes;
public:
	AdjacencylistGraph();
	AdjacencylistGraph(const std::vector< std::vector<int> > &matrix, bool directed);
	AdjacencylistGraph Transpose();
	AdjacencylistGraph ToUndirected();
	AdjacencylistGraph Square();
	void BFS(std::vector<int> &parent, std::vector<int> &distance, int s);
	//void BFSTraverse(std::vector<int> &path, int s);
	void DFS(std::vector<int> &parent, std::vector<int> &d, std::vector<int> &f, const std::vector<int> &assigned_order = std::vector<int>());
	void DFSVisit(std::vector<int> &parent, std::vector<int> &d, std::vector<int> &f, int &time, std::vector<int> &colors, int u);
	void StackDFS(std::vector<int> &parent, std::vector<int> &d, std::vector<int> &f);
	std::list<int> TopologicalSort();
	int PathsNumber(int s, int t);
	std::list<int> QueueTopologicalSort();
	int StronglyConnectedComponents(std::vector<int> &parent, std::vector<int> &scc);
	AdjacencylistGraph ComponentGraph();
	std::list<int> EulerTour();
	void EulerVisit(int v, std::vector<Vertex> &vertexes, std::list< std::pair< int, std::list<int>::iterator > > &L, std::list<int> &T, std::list<int>::iterator insert_begin);
	std::vector<Edge> MSTKruskalByLinkedlistDisjointSet();
	std::vector<Edge> MSTKruskalByArrayDisjointSet();
	std::vector<Edge> MSTPrim(int r);
	void InitializeSingleSource(int s, std::vector<int> &parent, std::vector<int> &d);
	void RelaxEdge(std::list<Edge>::iterator &itr, std::vector<int> &parent, std::vector<int> &d);
	bool BellmanFord(int s, std::vector<int> &parent, std::vector<int> &d);
	void DagShortestPaths(int s, std::vector<int> &parent, std::vector<int> &d);
	void Dijkstra(int s, std::vector<int> &parent, std::vector<int> &d);
};

class AdjacencymatrixGraph
{
private:
	bool m_directed;
	std::vector< std::vector<int> > m_matrix;
private:
	bool IsNodeSink(int k);
public:
	AdjacencymatrixGraph();
	AdjacencymatrixGraph(const std::vector< std::vector<int> > &matrix, bool directed);
	std::vector< std::vector<int> >& GetMatrixRef();
	AdjacencymatrixGraph Transpose();
	AdjacencymatrixGraph Square();
	bool BruteUniversalSinkExist();
	bool UniversalSinkExist();
	void BFS(std::vector<int> &parent, std::vector<int> &distance, int s);
};

#endif // GRAPH_H
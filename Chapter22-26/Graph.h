#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

enum EnumNodeColor
{
	EnumNodeColor_white,
	EnumNodeColor_gray,
	EnumNodeColor_black,
};

struct Edge;

struct Vertex
{
	EnumNodeColor m_color;
	std::list<Edge> m_edges;
	Vertex()
		: m_color(EnumNodeColor_white){}
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
	void BFS(int s);
};

class AdjacencymatrixGraph
{
private:
	bool m_directed;
	std::vector< std::vector<int> > m_matrix;
public:
	AdjacencymatrixGraph();
	AdjacencymatrixGraph(const std::vector< std::vector<int> > &matrix, bool directed);
	std::vector< std::vector<int> >& GetMatrixRef();
	AdjacencymatrixGraph Transpose();
	AdjacencymatrixGraph Square();
};

void testAdjacencylistGraph();
void testAdjacencymatrixGraph();
void testBFS();

#endif // GRAPH_H
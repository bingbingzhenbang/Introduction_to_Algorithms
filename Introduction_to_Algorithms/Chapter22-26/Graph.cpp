#include "Graph.h"
#include <algorithm>

using namespace std;

AdjacencylistGraph::AdjacencylistGraph()
: m_directed(false)
{

}

AdjacencylistGraph::AdjacencylistGraph(const std::vector< std::vector<int> > &matrix, bool directed)
: m_vertexes(matrix.size()), m_directed(directed)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			if (matrix[i][j] != 0)
				m_vertexes[i].m_edges.push_back(Edge(i, j, matrix[i][j]));
		}
	}
}

AdjacencylistGraph AdjacencylistGraph::Transpose()
{
	if (m_directed)
	{
		AdjacencylistGraph g;
		g.m_directed = m_directed;
		g.m_vertexes.resize(m_vertexes.size());
		for (int i = 0; i < m_vertexes.size(); ++i)
		{
			g.m_vertexes[i].m_color = m_vertexes[i].m_color;
			for (auto itr = m_vertexes[i].m_edges.begin(); itr != m_vertexes[i].m_edges.end(); ++itr)
				g.m_vertexes[itr->m_end].m_edges.push_back(Edge(itr->m_end, itr->m_start, itr->m_weight));
		}
		return g;
	}
	else
		return *this;
}

AdjacencylistGraph AdjacencylistGraph::ToUndirected()
{
	if (m_directed)
	{
		AdjacencylistGraph g;
		g.m_directed = false;
		g.m_vertexes.resize(m_vertexes.size());
		for (int i = 0; i < m_vertexes.size(); ++i)
		{
			g.m_vertexes[i].m_color = m_vertexes[i].m_color;
			for (auto itr = m_vertexes[i].m_edges.begin(); itr != m_vertexes[i].m_edges.end(); ++itr)
			{
				if (itr->m_start == itr->m_end)
					continue;
				if (find(g.m_vertexes[i].m_edges.begin(), g.m_vertexes[i].m_edges.end(), *itr) == g.m_vertexes[i].m_edges.end())
					g.m_vertexes[i].m_edges.push_back(*itr);
				if (find(g.m_vertexes[itr->m_end].m_edges.begin(), g.m_vertexes[itr->m_end].m_edges.end(), Edge(itr->m_end, itr->m_start, itr->m_weight)) == g.m_vertexes[itr->m_end].m_edges.end())
					g.m_vertexes[itr->m_end].m_edges.push_back(Edge(itr->m_end, itr->m_start, itr->m_weight));
			}
		}
		return g;
	}
	else
		return *this;
}

AdjacencylistGraph AdjacencylistGraph::Square()
{
	AdjacencylistGraph g;
	if (m_directed)
	{

	}
	return g;
}

void AdjacencylistGraph::BFS(int s)
{

}

AdjacencymatrixGraph::AdjacencymatrixGraph()
: m_directed(false)
{

}

AdjacencymatrixGraph::AdjacencymatrixGraph(const std::vector< std::vector<int> > &matrix, bool directed)
: m_matrix(matrix), m_directed(directed)
{

}

std::vector< std::vector<int> >& AdjacencymatrixGraph::GetMatrixRef()
{
	return m_matrix;
}

AdjacencymatrixGraph AdjacencymatrixGraph::Transpose()
{
	if (m_directed)
	{
		AdjacencymatrixGraph g;
		g.m_directed = m_directed;
		g.m_matrix.resize(m_matrix.size());
		for (int i = 0; i < g.m_matrix.size(); ++i)
		{
			g.m_matrix[i].resize(m_matrix.size());
			for (int j = 0; j < g.m_matrix[i].size(); ++j)
				g.m_matrix[i][j] = m_matrix[j][i];
		}
		return g;
	}
	else
		return *this;
}

AdjacencymatrixGraph AdjacencymatrixGraph::Square()
{
	AdjacencymatrixGraph g;
	if (m_directed)
	{
		g.m_directed = m_directed;
		int size = m_matrix.size();
		g.m_matrix.resize(size);
		for (int i = 0; i < size; ++i)
		{
			g.m_matrix[i].resize(size);
			for (int j = 0; j < size; ++j)
			{
				for (int k = 0; k < size; ++k)
				{
					if (m_matrix[i][k] && m_matrix[k][j])
					{
						g.m_matrix[i][j] = 1;
						break;
					}
				}
			}
		}
	}
	return g;
}

void testAdjacencylistGraph()
{
	vector< vector<int> > m1 = { { 0, 1, 0, 0, 1 }, { 1, 0, 1, 1, 1 }, { 0, 1, 0, 1, 0 }, { 0, 1, 1, 0, 1 }, { 1, 1, 0, 1, 0 } };
	AdjacencylistGraph g1(m1, false);
	vector< vector<int> > m2 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	AdjacencylistGraph g2(m2, true);
	AdjacencylistGraph g3 = g2.Transpose();
	AdjacencylistGraph g4 = g2.ToUndirected();
	AdjacencylistGraph g5 = g3.ToUndirected();
}

void testAdjacencymatrixGraph()
{
	vector< vector<int> > m1 = { { 0, 1, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 }, { 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 1 } };
	AdjacencymatrixGraph g1(m1, true);
	AdjacencymatrixGraph g2 = g1.Transpose();
	AdjacencylistGraph g3(g2.GetMatrixRef(), true);
	AdjacencymatrixGraph g4 = g1.Square();
}

void testBFS()
{

}
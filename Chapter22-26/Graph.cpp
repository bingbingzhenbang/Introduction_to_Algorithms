#include "Graph.h"
#include <algorithm>
#include <set>
#include <queue>

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
		g.m_directed = m_directed;
		g.m_vertexes.resize(m_vertexes.size());
		for (int i = 0; i < g.m_vertexes.size(); ++i)
		{
			set<Edge> edges;
			for (auto itr = m_vertexes[i].m_edges.begin(); itr != m_vertexes[i].m_edges.end(); ++itr)
				edges.insert(m_vertexes[itr->m_end].m_edges.begin(), m_vertexes[itr->m_end].m_edges.end());
			for (auto itr = edges.begin(); itr != edges.end(); ++itr)
				g.m_vertexes[i].m_edges.push_back(Edge(i, itr->m_end, itr->m_weight));
		}
	}
	return g;
}

void AdjacencylistGraph::BFS(std::vector<int> &parent, std::vector<int> &distance, int s)
{
	vector<int> colors(m_vertexes.size(), EnumNodeColor_white);
	parent = vector<int>(m_vertexes.size(), -1);
	distance = vector<int>(m_vertexes.size(), INT_MAX);
	colors[s] = EnumNodeColor_gray;
	distance[s] = 0;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		colors[u] = EnumNodeColor_black;
		for (auto itr = m_vertexes[u].m_edges.begin(); itr != m_vertexes[u].m_edges.end(); ++itr)
		{
			int v = itr->m_end;
			if (colors[v] == EnumNodeColor_white)
			{
				colors[v] = EnumNodeColor_gray;
				parent[v] = u;
				distance[v] = distance[u] + 1;
				Q.push(v);
			}
		}
	}
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

bool AdjacencymatrixGraph::BruteUniversalSinkExist()
{
	if (m_directed)
	{
		for (int j = 0; j < m_matrix.size(); ++j)
		{
			int sum = 0;
			for (int i = 0; i < m_matrix.size(); ++i)
			{
				if (m_matrix[i][j])
					++sum;
			}
			if (sum == m_matrix.size() - 1)
				return true;
		}
		return false;
	}
	else
		return false;
}

bool AdjacencymatrixGraph::IsNodeSink(int k)
{
	if (m_directed)
	{
		for (int j = 0; j < m_matrix.size(); ++j)
		{
			if (m_matrix[k][j])
				return false;
		}
		for (int i = 0; i < m_matrix.size(); ++i)
		{
			if (i == k)
				continue;
			if (m_matrix[i][k] == 0)
				return false;
		}
		return true;
	}
	return false;
}

bool AdjacencymatrixGraph::UniversalSinkExist()
{
	if (m_directed)
	{
		int i = 0, j = 0;
		while (i < m_matrix.size() && j < m_matrix.size())
		{
			if (m_matrix[i][j])
				++i;
			else
				++j;
		}
		if (i >= m_matrix.size())
			return false;
		else
			return IsNodeSink(i);
	}
	else
		return false;
}

void AdjacencymatrixGraph::BFS(std::vector<int> &parent, std::vector<int> &distance, int s)
{
	vector<int> colors(m_matrix.size(), EnumNodeColor_white);
	parent = vector<int>(m_matrix.size(), -1);
	distance = vector<int>(m_matrix.size(), INT_MAX);
	colors[s] = EnumNodeColor_gray;
	parent[s] = -1;
	distance[s] = 0;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		colors[u] = EnumNodeColor_black;
		for (int j = 0; j < m_matrix.size(); ++j)
		{
			if (m_matrix[u][j] && colors[j] == EnumNodeColor_white)
			{
				colors[j] = EnumNodeColor_gray;
				parent[j] = u;
				distance[j] = distance[u] + 1;
				Q.push(j);
			}
		}
	}
}
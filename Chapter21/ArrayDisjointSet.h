#ifndef ARRAYDISJOINT_H
#define ARRAYDISJOINT_H

#include <vector>

using std::vector;

class ArrayDisjointSet
{
private:
	vector<int> m_data;
public:
	ArrayDisjointSet(int N);
	int FindSet(int i);
	void Union(int x, int y);
};

ArrayDisjointSet::ArrayDisjointSet(int N)
: m_data(N)
{
	for (int i = 0; i < m_data.size(); ++i)
		m_data[i] = i;
}

int ArrayDisjointSet::FindSet(int i)
{
	if (i < 0 || i >= m_data.size())
		return -1;
	if (i != m_data[i])
		m_data[i] = FindSet(m_data[i]);
	return m_data[i];
}

void ArrayDisjointSet::Union(int x, int y)
{
	if (x < 0 || x >= m_data.size() || y < 0 || y >= m_data.size())
		return;
	int px = FindSet(x), py = FindSet(y);
	if (px != py)
		m_data[py] = px;
}

#endif // ARRAYDISJOINT_H
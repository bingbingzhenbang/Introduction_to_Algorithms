#include "PrimMinHeap.h"
#include <algorithm>

#define Parent(i) ( ((i) - 1 ) >> 1 )
#define Left(i)   ( ((i) << 1) | 1 )
#define Right(i)  ( ((i) + 1 ) << 1 )

using namespace std;

PrimMinHeap::PrimMinHeap(const vector<VertexKey> &keys)
: m_HeapData(keys), m_IndexInHeap(keys.size())
{
	for (int i = 0; i < m_IndexInHeap.size(); ++i)
		m_IndexInHeap[i] = m_HeapData[i].m_VertexIndex;
	for (int i = m_HeapData.size() / 2 - 1; i >= 0; --i)
		MinHeapify(i);
}

void PrimMinHeap::HeapElementSwap(int i, int j)
{
	int i_vertex_index = m_HeapData[i].m_VertexIndex;
	int j_vertex_index = m_HeapData[j].m_VertexIndex;
	m_IndexInHeap[i_vertex_index] = j;
	m_IndexInHeap[j_vertex_index] = i;
	swap(m_HeapData[i], m_HeapData[j]);
}

void PrimMinHeap::MinHeapify(int i)
{
	if (i < 0 || i >= m_HeapData.size())
		return;
	int smallest = i, L = Left(i), R = Right(i);
	if (L >= 0 && L < m_HeapData.size() && m_HeapData[L] < m_HeapData[i])
		smallest = L;
	if (R >= 0 && R < m_HeapData.size() && m_HeapData[R] < m_HeapData[smallest])
		smallest = R;
	if (smallest == i)
		return;
	HeapElementSwap(i, smallest);
	MinHeapify(smallest);
}

bool PrimMinHeap::IsEmpty() const
{
	return m_HeapData.empty();
}

VertexKey PrimMinHeap::GetTop() const
{
	return m_HeapData[0];
}

VertexKey PrimMinHeap::ExtractMin()
{
	VertexKey rt = m_HeapData[0];
	HeapElementSwap(0, m_HeapData.size() - 1);
	m_IndexInHeap[m_HeapData.back().m_VertexIndex] = -1;
	m_HeapData.pop_back();
	MinHeapify(0);
	return rt;
}

int PrimMinHeap::DecreaseKey(int i, int key)
{
	if (key >= m_HeapData[i].m_Key)
		return -1;
	m_HeapData[i].m_Key = key;
	while (i > 0 && m_HeapData[Parent(i)].m_Key >= m_HeapData[i].m_Key)
	{
		HeapElementSwap(i, Parent(i));
		i = Parent(i);
	}
	return 0;
}
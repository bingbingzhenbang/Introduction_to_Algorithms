#ifndef PRIMHEAP_H
#define PRIMHEAP_H

#include <vector>
#include <functional>
#include <utility>

#define Parent(i) ( ((i) - 1 ) >> 1 )
#define Left(i)   ( ((i) << 1) | 1 )
#define Right(i)  ( ((i) + 1 ) << 1 )

using std::vector;
using std::less;
using std::greater;
using std::swap;

struct VertexKey
{
	int m_VertexIndex;
	int m_Key;
	VertexKey(int index, int k) : m_VertexIndex(index), m_Key(k){}
};

struct VertexKeyLess
{
	bool operator()(const VertexKey &l, const VertexKey &r) const
	{
		if (l.m_Key == r.m_Key)
			return l.m_VertexIndex < r.m_VertexIndex;
		return l.m_Key < r.m_Key;
	}
};

struct VertexKeyGreater
{
	bool operator()(const VertexKey &l, const VertexKey &r) const
	{
		if (l.m_Key == r.m_Key)
			return l.m_VertexIndex > r.m_VertexIndex;
		return l.m_Key > r.m_Key;
	}
};

template <class KeyCompare = VertexKeyLess, class IntCompare = less<int> >
struct PrimHeap
{
	vector<VertexKey> m_HeapData;
	vector<int> m_IndexInHeap;
	PrimHeap(const vector<VertexKey> &keys);
	void HeapElementSwap(int i, int j);
	void Heapify(int i);
	bool IsEmpty() const;
	VertexKey GetTop() const;
	VertexKey ExtractTop();
	int ModifyKey(int i, int key);
};

template <class KeyCompare, class IntCompare>
PrimHeap<KeyCompare, IntCompare>::PrimHeap(const vector<VertexKey> &keys)
: m_HeapData(keys), m_IndexInHeap(keys.size())
{
	for (int i = 0; i < m_IndexInHeap.size(); ++i)
		m_IndexInHeap[i] = m_HeapData[i].m_VertexIndex;
	for (int i = m_HeapData.size() / 2 - 1; i >= 0; --i)
		Heapify(i);
}

template <class KeyCompare, class IntCompare>
void PrimHeap<KeyCompare, IntCompare>::HeapElementSwap(int i, int j)
{
	int i_vertex_index = m_HeapData[i].m_VertexIndex;
	int j_vertex_index = m_HeapData[j].m_VertexIndex;
	m_IndexInHeap[i_vertex_index] = j;
	m_IndexInHeap[j_vertex_index] = i;
	swap(m_HeapData[i], m_HeapData[j]);
}

template <class KeyCompare, class IntCompare>
void PrimHeap<KeyCompare, IntCompare>::Heapify(int i)
{
	if (i < 0 || i >= m_HeapData.size())
		return;
	int target = i, L = Left(i), R = Right(i);
	if (L >= 0 && L < m_HeapData.size() && KeyCompare()(m_HeapData[L], m_HeapData[i]))
		target = L;
	if (R >= 0 && R < m_HeapData.size() && KeyCompare()(m_HeapData[R], m_HeapData[target]))
		target = R;
	if (target == i)
		return;
	HeapElementSwap(i, target);
	Heapify(target);
}

template <class KeyCompare, class IntCompare>
bool PrimHeap<KeyCompare, IntCompare>::IsEmpty() const
{
	return m_HeapData.empty();
}

template <class KeyCompare, class IntCompare>
VertexKey PrimHeap<KeyCompare, IntCompare>::GetTop() const
{
	return m_HeapData[0];
}

template <class KeyCompare, class IntCompare>
VertexKey PrimHeap<KeyCompare, IntCompare>::ExtractTop()
{
	VertexKey rt = m_HeapData[0];
	HeapElementSwap(0, m_HeapData.size() - 1);
	m_IndexInHeap[m_HeapData.back().m_VertexIndex] = -1;
	m_HeapData.pop_back();
	Heapify(0);
	return rt;
}

template <class KeyCompare, class IntCompare>
int PrimHeap<KeyCompare, IntCompare>::ModifyKey(int i, int key)
{
	if (!IntCompare()(key, m_HeapData[i].m_Key))
		return -1;
	m_HeapData[i].m_Key = key;
	while (i > 0 && !IntCompare()(m_HeapData[Parent(i)].m_Key, m_HeapData[i].m_Key))
	{
		HeapElementSwap(i, Parent(i));
		i = Parent(i);
	}
	return 0;
}

typedef PrimHeap<VertexKeyLess, less<int> > PrimMinHeap;
typedef PrimHeap<VertexKeyGreater, greater<int> > PrimMaxHeap;

#endif // PRIMHEAP_H
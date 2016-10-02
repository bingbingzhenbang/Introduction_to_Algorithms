#ifndef PRIMMINHEAP_H
#define PRIMMINHEAP_H

#include <vector>

using std::vector;

struct VertexKey
{
	int m_VertexIndex;
	int m_Key;
	VertexKey(int index, int k) : m_VertexIndex(index), m_Key(k){}
};

inline bool operator<(const VertexKey &l, const VertexKey &r)
{
	if (l.m_Key == r.m_Key)
		return l.m_VertexIndex < r.m_VertexIndex;
	return l.m_Key < r.m_Key;
}

struct PrimMinHeap
{
	vector<VertexKey> m_HeapData;
	vector<int> m_IndexInHeap;
	PrimMinHeap(const vector<VertexKey> &keys);
	void HeapElementSwap(int i, int j);
	void MinHeapify(int i);
	bool IsEmpty() const;
	VertexKey GetTop() const;
	VertexKey ExtractMin();
	int DecreaseKey(int i, int key);
};

#endif // PRIMMINHEAP_H
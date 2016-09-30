#ifndef LINKEDLISTDISJOINTSET_H
#define LINKEDLISTDISJOINTSET_H

#include <list>
#include <memory>

using std::list;
using std::shared_ptr;

template <typename T>
struct LinkedlistDisjointSet;

template <typename T>
struct DisjointSetListElement
{
	T m_object;
	shared_ptr< LinkedlistDisjointSet<T> > m_setptr;
	DisjointSetListElement(T object) : m_object(object), m_setptr(0){}
};

template <typename T>
struct LinkedlistDisjointSet
{
	list< DisjointSetListElement<T>* > m_list;
};

template <typename T>
shared_ptr< LinkedlistDisjointSet<T> > MakeLinkedlistDisjointSet(shared_ptr< DisjointSetListElement<T> > x)
{
	shared_ptr<LinkedlistDisjointSet<T> > s(new LinkedlistDisjointSet<T>());
	s->m_list.push_back(x.get());
	x->m_setptr = s;
	return s;
}

template <typename T>
shared_ptr< LinkedlistDisjointSet<T> > FindLinkedlistDisjointSet(shared_ptr< DisjointSetListElement<T> > x)
{
	return x->m_setptr;
}

template <typename T>
shared_ptr< LinkedlistDisjointSet<T> > UnionLinkedlistDisjointSet(shared_ptr< DisjointSetListElement<T> > x, shared_ptr< DisjointSetListElement<T> > y)
{
	shared_ptr< LinkedlistDisjointSet<T> > sx = FindLinkedlistDisjointSet(x);
	shared_ptr< LinkedlistDisjointSet<T> > sy = FindLinkedlistDisjointSet(y);
	if (sx == sy)
		return sx;
	if (sx->m_list.size() < sy->m_list.size())
		swap(sx, sy);
	for (auto itr = sy->m_list.begin(); itr != sy->m_list.end(); ++itr)
		(*itr)->m_setptr = sx;
	sx->m_list.insert(sx->m_list.end(), sy->m_list.begin(), sy->m_list.end());
	sy->m_list.erase(sy->m_list.begin(), sy->m_list.end());
	return sx;
}

#endif // LINKEDLISTDISJOINTSET_H
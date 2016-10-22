#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <tuple>

using std::sqrt;
using std::tuple;

struct Point
{
	double m_x;
	double m_y;
	size_t m_index;
};

typedef tuple<Point, Point, double> PointDistance;

inline bool XLess(const Point &l, const Point &r)
{
	if (l.m_x == r.m_x)
		return l.m_y < r.m_y;
	return l.m_x < r.m_x;
}

inline bool YLess(const Point &l, const Point &r)
{
	if (l.m_y == r.m_y)
		return l.m_x < r.m_x;
	return l.m_y < r.m_y;
}

inline double Distance(const Point &l, const Point &r)
{
	return sqrt((l.m_x - r.m_x) * (l.m_x - r.m_x) + (l.m_y - r.m_y) * (l.m_y - r.m_y));
}

#endif // POINT_H
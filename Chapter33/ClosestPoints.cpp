#include "Point.h"
#include <vector>
#include <limits>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;

PointDistance BruteForceClosetPoints(const vector<Point> &points)
{
	double delta = numeric_limits<double>::max();
	size_t p1 = -1, p2 = -1;
	for (size_t i = 0; i < points.size(); ++i)
	{
		for (size_t j = i + 1; j < points.size(); ++j)
		{
			double temp = Distance(points[i], points[j]);
			if (temp < delta)
			{
				delta = temp;
				p1 = i;
				p2 = j;
			}
		}
	}
	return make_tuple(points[p1], points[p2], delta);
}

PointDistance RecursiveClosetPoints(const vector<Point> &pointsX, const vector<Point> &pointsY)
{
	assert(pointsX.size() == pointsY.size());
	if (pointsX.size() <= 3)
		return BruteForceClosetPoints(pointsX);
	return make_tuple(Point(), Point(), 0.0);
}

PointDistance ClosetPoints(const vector<Point> &points)
{
	vector<Point> pointsX(points), pointsY(points);
	sort(pointsX.begin(), pointsX.end(), XLess);
	sort(pointsY.begin(), pointsY.end(), YLess);
	return RecursiveClosetPoints(pointsX, pointsY);
}

void testClosestPoints()
{
	const size_t N = 2500;
	const double low = 0.5;
	const double high = 1000000000;
	default_random_engine e1;
	//default_random_engine e1(time(0));
	uniform_real_distribution<double> u1(low, high);
	vector<Point> points(N);
	for (size_t i = 0; i < N; ++i)
	{
		points[i].m_x = u1(e1);
		points[i].m_y = u1(e1);
	}
	PointDistance rt1 = BruteForceClosetPoints(points);
	PointDistance rt2 = ClosetPoints(points);
	if (rt1 == rt2)
		cout << "Same !" << endl;
	else
		cout << "Not Same !" << endl;
}
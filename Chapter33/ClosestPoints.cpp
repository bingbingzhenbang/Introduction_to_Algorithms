#include "Point.h"
#include <vector>
#include <limits>
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

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
	size_t mid = pointsX.size() / 2;
	vector<Point> pointsXL(pointsX.begin(), pointsX.begin() + mid), pointsYL;
	vector<Point> pointsXR(pointsX.begin() + mid, pointsX.end()), pointsYR;
	unordered_set<size_t> leftindexes;
	for (auto itr = pointsXL.begin(); itr != pointsXL.end(); ++itr)
		leftindexes.insert(itr->m_index);
	for (auto itr1 = pointsY.begin(); itr1 != pointsY.end(); ++itr1)
	{
		auto itr2 = leftindexes.find(itr1->m_index);
		if (itr2 != leftindexes.end())
			pointsYL.push_back(*itr1);
		else
			pointsYR.push_back(*itr1);
	}
	PointDistance leftresult = RecursiveClosetPoints(pointsXL, pointsYL);
	PointDistance rightresult = RecursiveClosetPoints(pointsXR, pointsYR);
	double leftdelta = get<2>(leftresult), rightdelta = get<2>(rightresult), delta = 0.0;
	Point p1, p2;
	if (leftdelta < rightdelta)
	{
		p1 = get<0>(leftresult);
		p2 = get<1>(leftresult);
		delta = leftdelta;
	}
	else
	{
		p1 = get<0>(rightresult);
		p2 = get<1>(rightresult);
		delta = rightdelta;
	}
	double midline = 0.0;
	if (pointsX.size() % 2)
		midline = pointsX[mid].m_x;
	else
		midline = (pointsX[mid - 1].m_x + pointsX[mid].m_x) / 2;
	vector<Point> pointsY1;
	for (auto itr = pointsY.begin(); itr != pointsY.end(); ++itr)
	{
		if (itr->m_x >= midline - delta && itr->m_x <= midline + delta)
			pointsY1.push_back(*itr);
	}
	double delta1 = numeric_limits<double>::max();
	size_t p11 = -1, p12 = -1;
	for (size_t i = 0; i < pointsY1.size(); ++i)
	{
		for (size_t j = i + 1; j < pointsY1.size() && j < i + 8; ++j)
		{
			double temp = Distance(pointsY1[i], pointsY1[j]);
			if (temp < delta1)
			{
				delta1 = temp;
				p11 = i;
				p12 = j;		}
		}
	}
	if (delta < delta1)
		return make_tuple(p1, p2, delta);
	else
		return make_tuple(pointsY1[p11], pointsY1[p12], delta1);
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
	const size_t N = 100000;
	const double low = 0.5;
	const double high = 1000000000;
	//default_random_engine e1;
	default_random_engine e1(time(0));
	uniform_real_distribution<double> u1(low, high);
	vector<Point> points(N);
	for (size_t i = 0; i < N; ++i)
	{
		points[i].m_x = u1(e1);
		points[i].m_y = u1(e1);
		points[i].m_index = i;
	}
	auto t1 = high_resolution_clock::now();
	PointDistance rt1 = BruteForceClosetPoints(points);
	auto t2 = high_resolution_clock::now();
	PointDistance rt2 = ClosetPoints(points);
	auto t3 = high_resolution_clock::now();
	size_t index11 = min(get<0>(rt1).m_index, get<1>(rt1).m_index), index12 = max(get<0>(rt1).m_index, get<1>(rt1).m_index);
	size_t index21 = min(get<0>(rt2).m_index, get<1>(rt2).m_index), index22 = max(get<0>(rt2).m_index, get<1>(rt2).m_index);
	double delta1 = get<2>(rt1);
	double delta2 = get<2>(rt2);
	if (index11 == index21 && index12 == index22 && delta1 == delta2)
		cout << "Result Same !" << endl;
	else
		cout << "Result Not Same !" << endl;
	cout << "Brute Force Method : " << duration_cast<milliseconds>(t2 - t1).count() << " ms" << endl
		<< "Recursive Method : " << duration_cast<milliseconds>(t3 - t2).count() << " ms" << endl;
}
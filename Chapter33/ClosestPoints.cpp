#include "Point.h"
#include <vector>
#include <limits>
#include <algorithm>

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
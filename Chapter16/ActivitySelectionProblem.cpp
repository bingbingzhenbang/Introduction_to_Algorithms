#include <vector>
#include <algorithm>

using namespace std;

struct Activity
{
	int m_begin;
	int m_end;
};

bool operator<(const Activity &left, const Activity &right)
{
	return left.m_end < right.m_end;
}

vector<int> DPActivitySelector(const vector<Activity> &activities)
{
	vector<int> result;
	return result;
}

vector<int> RecursiveActivitySelector(const vector<Activity> &activities, int begin)
{
	vector<int> result;
	int m = begin + 1, size = activities.size();
	if (begin < size)
		result.push_back(begin + 1);
	while (m < size && activities[m].m_begin < activities[begin].m_end)
		++m;
	if (m < size)
	{
		vector<int> temp = RecursiveActivitySelector(activities, m);
		for (int i = 0; i < temp.size(); ++i)
			result.push_back(temp[i]);
	}
	return result;
}

vector<int> GreedyActivitySelector(const vector<Activity> &activities)
{
	vector<int> result;
	result.push_back(1);
	int size = activities.size(), i = 0;
	for (int m = 1; m < size; )
	{
		if (activities[m].m_begin >= activities[i].m_end)
		{
			result.push_back(m + 1);
			i = m;
		}
		else
			++m;
	}
	return result;
}

void testActivitySelectionProblem()
{
	vector<int> s = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	vector<int> f = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	vector<Activity> activities(s.size());
	for (int i = 0; i < s.size() && i < f.size(); ++i)
	{
		activities[i].m_begin = s[i];
		activities[i].m_end = f[i];
	}
	sort(activities.begin(), activities.end());

	vector<int> result;
	result = RecursiveActivitySelector(activities, 0);
	result.clear();
	result = GreedyActivitySelector(activities);
}
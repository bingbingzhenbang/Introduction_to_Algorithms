#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

struct Activity
{
	int m_begin;
	int m_end;
};

bool BeginEarlier(const Activity &left, const Activity &right)
{
	return left.m_begin < right.m_begin;
}

bool EndEarlier(const Activity &left, const Activity &right)
{
	return left.m_end < right.m_end;
}

bool DurationLess(const Activity &left, const Activity &right)
{
	return (left.m_end - left.m_begin) < (right.m_end - right.m_begin);
}

struct TimePoint
{
	int m_time;
	int m_begin_or_end;           // 1 for begin, 0 for end
	int m_activity_index;
};

bool TimePointLess(const TimePoint &left, const TimePoint &right)
{
	if (left.m_time == right.m_time)
		return left.m_begin_or_end < right.m_begin_or_end;
	return left.m_time < right.m_time;
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

vector<int> DPActivitySelector(const vector<Activity> &activities)
{
	int size = activities.size();
	vector< vector<int> > c(size, vector<int>(size, 0));
	vector< vector<int> > s(size, vector<int>(size, 0));
	for (int i = 0; i < size; ++i)
	{
		c[i][i] = 1;
		s[i][i] = i;
	}
	for (int len = 2; len <= size; ++len)
	{
		for (int i = 0; i <= size - len; ++i)
		{
			int j = i + len - 1;
			c[i][j] = 1;
			s[i][j] = i;
			if (activities[i].m_end <= activities[j].m_begin)
				c[i][j] = 2;
			if (len > 2)
			{
				int t = 0;
				for (int k = i + 1; k < j; ++k)
				{
					if (activities[k].m_begin >= activities[i].m_end && activities[k].m_end <= activities[j].m_begin)
					{
						t = c[i][k] + c[k][j] - 1;
						if (t > c[i][j])
						{
							c[i][j] = t;
							s[i][j] = k;
						}
					}
				}
			}
		}
	}
	int maxnum = c[0][size - 1];
	vector<int> result(maxnum, 1);
	int k = s[0][size - 1];
	for (int i = 1; i < c[0][size - 1] - 1; ++i)
	{
		result[i] = k + 1;
		k = s[k][size - 1];
	}
	++k;
	while (k < size)
	{
		if (activities[k].m_begin >= activities[result[maxnum - 2] - 1].m_end)
		{
			result[maxnum - 1] = k + 1;
			break;
		}
		else
			++k;
	}
	return result;
}

map< int, vector<int> > ScheduleRoom(const vector<Activity> &activities)
{
	int size = activities.size();
	vector<TimePoint> timepoints(2 * size);
	for (int i = 0; i < size; ++i)
	{
		timepoints[i].m_time = activities[i].m_begin;
		timepoints[i].m_begin_or_end = 1;
		timepoints[i].m_activity_index = i;
	}
	for (int i = 0; i < size; ++i)
	{
		timepoints[i + size].m_time = activities[i].m_end;
		timepoints[i + size].m_begin_or_end = 0;
		timepoints[i + size].m_activity_index = i;
	}
	sort(timepoints.begin(), timepoints.end(), TimePointLess);
	vector<int> activityindex_and_room(size, -1);  // room of each activity
	int currentRooms = 1;
	stack<int> free_rooms;
	free_rooms.push(0);
	map< int, vector<int> > room_and_activities;
	for (int i = 0; i < timepoints.size(); ++i)
	{
		if (timepoints[i].m_begin_or_end == 1)
		{
			int schedule_room;
			if (free_rooms.empty())
			{
				schedule_room = currentRooms;
				++currentRooms;
			}
			else
			{
				schedule_room = free_rooms.top();
				free_rooms.pop();
			}
			activityindex_and_room[timepoints[i].m_activity_index] = schedule_room;
			room_and_activities[schedule_room + 1].push_back(timepoints[i].m_activity_index + 1);
		}
		else
		{
			int room = activityindex_and_room[timepoints[i].m_activity_index];
			free_rooms.push(room);
		}
	}
	return room_and_activities;
}

void testActivitySelectionProblem()
{
	//vector<int> s = { 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	//vector<int> f = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//vector<int> s = { 1, 3, 0, 5, 3, 5, 6, 8, 11, 2, 12 };
	//vector<int> f = { 4, 5, 6, 6, 8, 9, 10, 11, 12, 13, 14 };
	vector<int> s = { 0, 1, 1, 1, 2, 3, 4, 5, 5, 5, 6 };
	vector<int> f = { 2, 3, 3, 3, 4, 5, 6, 7, 7, 7, 8 };
	vector<Activity> activities(s.size());
	for (int i = 0; i < s.size() && i < f.size(); ++i)
	{
		activities[i].m_begin = s[i];
		activities[i].m_end = f[i];
	}
	sort(activities.begin(), activities.end(), EndEarlier);

	vector<int> result;
	result = RecursiveActivitySelector(activities, 0);
	result.clear();
	result = GreedyActivitySelector(activities);
	result.clear();
	result = DPActivitySelector(activities);

	map< int, vector<int> > room_and_activities = ScheduleRoom(activities);
	for (auto itr = room_and_activities.begin(); itr != room_and_activities.end(); ++itr)
	{
		cout << "Room : " << itr->first << endl;
		vector<int> &room_activities = itr->second;
		for (int i = 0; i < room_activities.size(); ++i)
		{
			cout << room_activities[i] << " (" << activities[room_activities[i] - 1].m_begin << "," << activities[room_activities[i] - 1].m_end << ")" << endl;
		}
		cout << endl;
	}
}
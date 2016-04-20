#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int MaximizePayoff(vector<int> &A, vector<int> &B)
{
	int size = A.size(), rt = 1;
	sort(A.begin(), A.end(), less<int>());
	sort(B.begin(), B.end(), less<int>());
	for (int i = 0; i < size; ++i)
	{
		for (int j = 1; j <= B[i]; ++j)
			rt *= A[i];
	}
	return rt;
}

void testMaximizePayoff()
{
	vector<int> A = { 6, 3, 5 };
	vector<int> B = { 2, 4, 5 };
	int rt = MaximizePayoff(A, B);
}
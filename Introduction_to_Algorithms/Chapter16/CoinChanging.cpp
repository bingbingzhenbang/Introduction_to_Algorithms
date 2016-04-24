#include <vector>
#include <algorithm>

using namespace std;

int GreedyCoinChange(vector<int> &denoms, vector<int> &coins, int money)
{
	int size = coins.size(), rt = 0;
	for (int i = 0; i < size && money >= 0; ++i)
	{
		denoms[i] = money / coins[i];
		rt += denoms[i];
		money = money % coins[i];
	}
	return rt;
}

int DPCoinChange(vector<int> &denoms, vector<int> &coins, int money)
{
	int size = coins.size();
	vector<int> c(money + 1, 0);
	vector< vector<int> > s(money + 1, vector<int>(size, 0));
	for (int i = 1; i <= money; ++i)
	{
		c[i] = INT_MAX;
		int mink = -1;
		for (int k = 0; k < size; ++k)
		{
			if (i >= coins[k])
			{
				if (c[i - coins[k]] <= c[i] - 1)
				{
					c[i] = c[i - coins[k]] + 1;
					mink = k;
				}
			}
		}
		if (mink != -1)
		{
			s[i] = s[i - coins[mink]];
			++s[i][mink];
		}
	}
	denoms = s[money];
	return c[money];
}

void testCoinChange()
{
	//vector<int> coins = { 25, 10, 5, 1 };
	//int money = 70;
	//vector<int> coins = { 25, 10, 1 };
	//int money = 30;
	//vector<int> coins = { 4, 3, 1 };
	//int money = 6;
	vector<int> coins = { 186, 419, 83, 408 };
	int money = 6249;
	int size = coins.size();
	vector<int> denoms(size, 0);
	int rt1 = GreedyCoinChange(denoms, coins, money);
	int rt2 = DPCoinChange(denoms, coins, money);
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += coins[i] * denoms[i];
	}
}
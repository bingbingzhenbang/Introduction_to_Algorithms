#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
	int m_value;
	int m_weight;
};

bool UnitPriceHigher(const Item &left, const Item &right)
{
	return (double)left.m_value / left.m_weight > (double)right.m_value / right.m_weight;
}

double GreedyFractionalKnapsack(vector<Item> &items, int maxWeight)
{
	sort(items.begin(), items.end(), UnitPriceHigher);
	int currentWeight = 0;
	double maxValue = 0.0;
	for (int i = 0; i < items.size() && currentWeight < maxWeight; ++i)
	{
		int newWeight = 0;
		if (currentWeight + items[i].m_weight <= maxWeight)
			newWeight = items[i].m_weight;
		else
			newWeight = maxWeight - currentWeight;
		currentWeight += newWeight;
		maxValue += (double)newWeight * items[i].m_value / items[i].m_weight;
	}
	return maxValue;
}

int DP01Knapsack(vector<Item> &items, int maxWeight)
{
	int size = items.size();
	vector< vector<int> > c(size + 1, vector<int>(maxWeight + 1, 0));
	for (int i = 1; i <= size; ++i)
	{
		for (int w = 1; w <= maxWeight; ++w)
		{
			int wi = items[i - 1].m_weight;
			if (wi > w)
				c[i][w] = c[i - 1][w];
			else
				c[i][w] = max(items[i - 1].m_value + c[i - 1][w - wi], c[i - 1][w]);
		}
	}
	return c[size][maxWeight];
}

void testKnapsack()
{
	//int maxWeight = 50;
	//vector<int> values = { 60, 100, 120 };
	//vector<int> weights = { 10, 20, 30 };
	int maxWeight = 10;
	vector<int> values = { 6, 3, 5, 4, 6 };
	vector<int> weights = { 2, 2, 6, 5, 4 };
	//int maxWeight = 10;
	//vector<int> values = { 10, 40, 30, 50 };
	//vector<int> weights = { 5, 4, 6, 3 };
	int size = values.size();
	vector<Item> items(size);
	for (int i = 0; i < size; ++i)
	{
		items[i].m_value = values[i];
		items[i].m_weight = weights[i];
	}

	double fractional_max = GreedyFractionalKnapsack(items, maxWeight);
	int dp_01_max = DP01Knapsack(items, maxWeight);
}
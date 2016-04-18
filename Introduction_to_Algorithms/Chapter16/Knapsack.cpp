#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
	int m_value;
	int m_weight;
};

bool PriceHigher(const Item &left, const Item &right)
{
	return (double)left.m_value / left.m_weight > (double)right.m_value / right.m_weight;
}

double FractionalKnapsack(vector<Item> &items, int maxWeight)
{
	sort(items.begin(), items.end(), PriceHigher);
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

void testKnapsack()
{
	int maxWeight = 50;
	vector<int> values = { 60, 100, 120 };
	vector<int> weights = { 10, 20, 30 };
	int size = values.size();
	vector<Item> items(size);
	for (int i = 0; i < size; ++i)
	{
		items[i].m_value = values[i];
		items[i].m_weight = weights[i];
	}

	double fractional_max = FractionalKnapsack(items, maxWeight);
}
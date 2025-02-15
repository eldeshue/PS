
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <algorithm>

using Fraction = std::pair<int, int>;

struct cmp_fract
{
	bool operator()(const Fraction& f1, const Fraction& f2)
	{
		return (f1.first * f2.second) < (f2.first * f1.second);
	}
};

class Solution
{
public:
	// solution method
	vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) 
	{
		std::vector<Fraction> fractions;
		std::vector<int> result(2);
		for (int i = 0; i < arr.size() -  1; ++i)
		{
			for (int j = i + 1; j < arr.size(); ++j)
			{
				fractions.push_back(std::make_pair(arr[i], arr[j]));
			}
		}
		std::sort(fractions.begin(), fractions.end(), cmp_fract());
		result[0] = fractions[k - 1].first;
		result[1] = fractions[k - 1].second;
		return result;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
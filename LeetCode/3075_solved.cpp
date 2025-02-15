
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <algorithm>

class Solution
{
public:
	// solution method
	long long maximumHappinessSum(vector<int>& happiness, int k) {
		long long  hSum = 0;
		int decreaseVal = 0;
		sort(happiness.begin(), happiness.end(), greater<int>());
		for (int i = 0; i < k; ++i)
		{
			if (happiness[i] > decreaseVal)
			{
				hSum += happiness[i] - decreaseVal;
				decreaseVal++;
			}
		}
		return hSum;
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
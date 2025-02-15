
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <bit>
class Solution
{
public:
	// solution method
	bool canSortArray(vector<int>& nums)
	{
		const int N = nums.size();
		vector<int> bitCounts;
		transform(nums.begin(), nums.end(), std::back_inserter(bitCounts),
			[](unsigned int n)->int {return popcount(n); });
		for (int i = 0; i < N - 1; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (nums[j] < nums[i] && bitCounts[j] != bitCounts[i])
				{
					return false;
				}
			}
		}
		return true;
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}



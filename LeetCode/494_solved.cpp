
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	int findTargetSumWays(vector<int>& nums, int target)
	{
		const int N = nums.size();
		vector<vector<int>> cache(N + 1, vector<int>(2001, 0));

		cache[0][1000 + 0] = 1;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j <= 2000; ++j)
			{
				const int nextPlus = j + nums[i];
				if (nextPlus <= 2000)	// +
				{
					cache[i + 1][nextPlus] += cache[i][j];
				}
				const int nextMinus = j - nums[i];
				if (nextMinus >= 0)	// -
				{
					cache[i + 1][nextMinus] += cache[i][j];
				}
			}
		}
		return cache[N][1000 + target];
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


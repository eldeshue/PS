
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <numeric>
class Solution
{
public:
	// solution method
	using pii = pair<int, int>;
	vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
	{
		// cache
		const int N = nums.size();

		// sliding window
		vector<int> kSum(N, 0);
		kSum[k - 1] = accumulate(nums.begin(), nums.begin() + k, 0);
		for (int i = k; i < N; ++i)
		{
			kSum[i] = kSum[i - 1] - nums[i - k] + nums[i];
		}

		// first cache
		vector<vector<pii>> cache(3, vector<pii>(N, { -1, -1 }));
		cache[0][k - 1] = make_pair(kSum[0], 0);
		for (int i = k; i < N; ++i)
		{
			if (kSum[i] > cache[0][i - 1].first)
			{
				cache[0][i] = make_pair(kSum[i], i - k + 1);
			}
			else
			{
				cache[0][i] = cache[0][i - 1];
			}
		}
		// tabulation
		for (int l = 1; l < 3; ++l)
		{
			for (int i = (l + 1) * k - 1; i < N; ++i)
			{
				if (kSum[i] + cache[l - 1][i - k].first > cache[l][i - 1].first)
				{
					cache[l][i] = make_pair(kSum[i] + cache[l - 1][i - k].first,
						cache[l - 1][i - k].second);
				}
				else
				{
					cache[l][i] = cache[l][i - 1];
				}
			}

		}

		// result resolve
		vector<int> result(3);
		int maxVal = 0;
		result[2] = -1;
		for (int i = 0; i < N; ++i)
		{
			if (maxVal < cache[2][i].first)
			{
				result[2] = cache[2][i].second;
				maxVal = cache[2][i].first;
			}
		}
		for (int i = 1; i >= 0; --i)
		{
			result[i] = cache[i][result[i + 1]].second;
		}
		return result;
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



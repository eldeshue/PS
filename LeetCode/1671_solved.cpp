
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
class Solution
{
private:
	int N;
	void setLIS(const vector<int> &nums, vector<int> &lis, int start, int end)
	{
		const int step = (end - start) / abs(end - start);
		vector<int> minLastValPerLen(N, 2e9);
		minLastValPerLen[0] = -2e9;
		for (int i = start + step; i != end; i += step)
		{
			// get len
			// n2 is nums[i]
			lis[i] = lower_bound(minLastValPerLen.begin(), minLastValPerLen.end(), nums[i])
				 - minLastValPerLen.begin();
			// update
			minLastValPerLen[lis[i]] = min(minLastValPerLen[lis[i]], nums[i]);
		}
	}
public:
	// solution method
	int minimumMountainRemovals(vector<int>& nums)
	{
		N = nums.size();
		vector<int> lis(N, 1);
		vector<int> lds(N, 1);
		// lis, O(N log N), can be optimized O(N log N)
		setLIS(nums, lis, 0, N);
		// lds, reverse lis
		setLIS(nums, lds, N - 1, -1);
		// get result
		int result = 0;
		for (int i = 0; i < N; ++i)
		{
			if (lis[i] >= 2 && lds[i] >= 2)
				result = max(result, lis[i] + lds[i] - 1);
		}
		return N - result;
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



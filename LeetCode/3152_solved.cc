
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <functional>
class Solution
{
private:
public:
	// solution method
	vector<bool> isArraySpecial(vector<int> &nums, vector<vector<int>> &queries)
	{
		// prepare data structure
		auto log2 = [](const int n)
		{
			int result = 0;
			while (n > (1 << result))
			{
				result++;
			}
			return result;
		};
		const int N = nums.size();
		const int maxLevel = log2(N);
		const int offset = 1 << maxLevel;
		// segtree, is special -> true or false
		// left inclusive, right non-inclusive
		// range and calculation
		vector<bool> segTree((offset << 1) + 1, true);

		// set initial value
		for (int i = 0; i < N - 1; ++i)
		{
			segTree[i + offset] = ((nums[i] & 1) != (nums[i + 1] & 1));
		}

		// initialize
		for (int i = offset - 1; i >= 1; --i)
		{
			segTree[i] = segTree[i * 2] & segTree[i * 2 + 1];
		}

		// left include, right not include
		// recursive segtree
		function<bool(int, int, int, int, int)> rangeQuery = [&](int start, int end, int tidx, int left, int right) -> bool
		{
			if (end <= left || start >= right) // out of range
			{
				return true; // eigen value
			}
			else if (left <= start && end <= right) // fit range, collect
			{
				return segTree[tidx];
			}
			else // split
			{
				const int mid = (start + end) >> 1;
				return rangeQuery(start, mid, tidx * 2, left, right) && rangeQuery(mid, end, tidx * 2 + 1, left, right);
			}
		};

		// calculate queries
		vector<bool> result;
		for (const auto &q : queries)
		{
			result.push_back(rangeQuery(0, offset, 1, q[0], q[1]));
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}

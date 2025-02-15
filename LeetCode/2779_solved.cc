
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <queue>
class Solution
{
private:
	using Seg = pair<int, int>;

public:
	// solution method
	int maximumBeauty(vector<int> &nums, int k)
	{
		// one replacement per pos
		// range nums[i] +- k
		// max subseq
		// so the problem is finding most commonly overlapped bandwith(?) among nums
		// naive, N * K : count all possible candidate
		// n log n, range sweeping
		// n log n, lazy segtree(range update)
		//
		vector<Seg> buffer;
		transform(nums.begin(), nums.end(), back_inserter(buffer), [k](const int n)
				  { return make_pair(n - k, n + k); });
		sort(buffer.begin(), buffer.end(), less<Seg>());

		// priority queue, monotonous
		priority_queue<int, vector<int>, greater<int>> endPq;
		int result = 0;
		for (const auto &s : buffer)
		{
			// pop non overlapped seg
			while (!endPq.empty() && endPq.top() < s.first)
			{
				endPq.pop();
			}
			// enque
			endPq.push(s.second);
			// update result
			result = max(result, static_cast<int>(endPq.size()));
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

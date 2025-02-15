

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <numeric>
class Solution
{
private:
	using pii = pair<int, int>;

public:
	// solution method
	int maxTwoEvents(vector<vector<int>> &events)
	{
		// prefix sum
		const int N = events.size();
		vector<pii> startPrefixSum;
		vector<pii> endSuffixSum;
		for (const auto &e : events)
		{
			startPrefixSum.push_back(make_pair(e[0], e[2]));
			endSuffixSum.push_back(make_pair(e[1], e[2]));
		}
		sort(startPrefixSum.begin(), startPrefixSum.end(), less<pii>());
		sort(endSuffixSum.begin(), endSuffixSum.end(), [](const pii &p1, const pii &p2)
			 {
			if (p1.first == p2.first)
				return p1.second > p2.second;	// in case of same values
			return p1.first < p2.first; });
		int acc = 0;
		transform(startPrefixSum.rbegin(), startPrefixSum.rend(), startPrefixSum.rbegin(),
				  [&](const pii n)
				  {
					  acc = max(acc, n.second);
					  return make_pair(n.first, acc);
				  });
		acc = 0;
		transform(endSuffixSum.begin(), endSuffixSum.end(), endSuffixSum.begin(),
				  [&](const pii n)
				  {
					  acc = max(acc, n.second);
					  return make_pair(n.first, acc);
				  });
		int result = 0;
		int sIdx = 0, eIdx = 0;
		for (; eIdx < N; ++eIdx) // pick end
		{
			while (sIdx < N && startPrefixSum[sIdx].first <= endSuffixSum[eIdx].first) // pick start
			{
				sIdx++;
			}
			if (sIdx < N)
				result = max(result, startPrefixSum[sIdx].second + endSuffixSum[eIdx].second);
		}
		return max(result, accumulate(events.begin(), events.end(), 0, [](const int acc, const vector<int> &v)
									  { return max(acc, v[2]); }));
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

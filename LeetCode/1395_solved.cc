
/*
	prefix sum + suffix sum + meet in the middle -> O(N ^ 2)

	two segment tree -> O(N log N)
*/
#include <vector>
#include <iostream>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
	using pii = pair<int, int>;

public:
	int numTeams(vector<int> &rating)
	{
		int teamCnt = 0;
		const int N = rating.size();
		vector<pii> prefixSums(N, {0, 0});
		vector<pii> suffixSums(N, {0, 0});
		for (int c = 1; c < N; ++c) // prefix, O(N ^ 2)
		{
			for (int p = 0; p < c; ++p)
			{
				if (rating[p] < rating[c]) // first
					prefixSums[c].first++;
				else if (rating[p] > rating[c]) // second
					prefixSums[c].second++;
			}
		}
		for (int c = N - 2; c >= 0; --c) // suffix
		{
			for (int p = N - 1; p > c; --p)
			{
				if (rating[c] < rating[p])
					suffixSums[c].first++;
				else if (rating[c] > rating[p])
					suffixSums[c].second++;
			}
		}
		for (int i = 0; i < N; ++i)
		{
			teamCnt += prefixSums[i].first * suffixSums[i].first;
			teamCnt += prefixSums[i].second * suffixSums[i].second;
		}
		return teamCnt;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();

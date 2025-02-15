
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <tuple>
#include <queue>
#include <algorithm>
class Solution
{
private:
	using tiii = tuple<int, int, int>;
	struct cmp_tii	//
	{
		bool operator()(tiii const& t1, tiii const& t2) const	// binary ops
		{
			// compare range end
			if (get<1>(t1) == get<1>(t2))
			{
				return get<0>(t1) > get<0>(t2);
			}
			// compare range start
			return get<1>(t1) > get<1>(t2);
		}
	};
public:
	string shiftingLetters(string s, vector<vector<int>>& shifts) {
		// sweeping
		vector<tiii> queries;
		priority_queue <tiii, vector<tiii>, cmp_tii> pq;

		// transform range query
		transform(shifts.begin(), shifts.end(), back_inserter(queries), [](vector<int> const& vec) {
			return make_tuple(vec[0], vec[1], vec[2]);
			});

		// sweeping, update string
		sort(queries.begin(), queries.end(), [](tiii const& t1, tiii const& t2) {
			// compare range end
			if (get<0>(t1) == get<0>(t2))
			{
				return get<1>(t1) < get<1>(t2);
			}
			// compare range start
			return get<0>(t1) < get<0>(t2);
			});
		int qIdx = 0, shiftCnt = 0;
		auto shiftAlpha = [&](char const c) {
			shiftCnt %= 26;
			return 'a' + ((c - 'a') + 26 + shiftCnt) % 26;
			};
		for (int i = 0; i < s.size(); ++i)
		{
			// update shift count
			// push pq
			while (qIdx < queries.size() && get<0>(queries[qIdx]) <= i)
			{
				pq.push(queries[qIdx]);
				shiftCnt += (get<2>(queries[qIdx]) ? 1 : -1);
				qIdx++;
			}
			// pop pq
			while (!pq.empty() && get<1>(pq.top()) < i)
			{
				shiftCnt -= (get<2>(pq.top()) ? 1 : -1);
				pq.pop();
			}
			// shift alphabet
			s[i] = shiftAlpha(s[i]);
		}
		return s;
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

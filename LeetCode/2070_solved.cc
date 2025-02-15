
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
class Solution
{
private:
	using pii = pair<int, int>;

public:
	// solution method
	vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries)
	{
		vector<pii> orderedBuffer;
		for_each(items.begin(), items.end(), [&](const vector<int> &v)
				 { orderedBuffer.push_back(make_pair(v[0], v[1])); });
		sort(orderedBuffer.begin(), orderedBuffer.end());
		for (int i = 1; i < orderedBuffer.size(); ++i)
			orderedBuffer[i].second = max(orderedBuffer[i].second, orderedBuffer[i - 1].second);
		vector<int> result;
		transform(queries.begin(), queries.end(), back_inserter(result), [&](const int cost)
				  {
			auto itr = upper_bound(orderedBuffer.begin(), orderedBuffer.end(), make_pair(cost, 2000000000));
			if (itr == orderedBuffer.begin())
				return 0;
			return (--itr)->second; });
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

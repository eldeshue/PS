
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <numeric>
#include <queue>
#include <functional>
class Solution
{
private:
	using pii = pair<int, int>;	// pass, total
public:
	// solution method
	double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
	{
		const int N = classes.size();
		vector<pii> totalAndPasses(N);

		auto ratio = [](const pii p, int v)
			{
				return static_cast<double>(p.first + v) / static_cast<double>(p.second + v);
			};
		priority_queue<pii, vector<pii>, std::function<bool(const pii&, const pii&)>>
			pq(
				[&](const pii& p1, const pii& p2) -> bool
				{return (ratio(p1, 1) - ratio(p1, 0)) < (ratio(p2, 1) - ratio(p2, 0));
				});	// max heap
		for_each(classes.begin(), classes.end(),
			[&](const vector<int>& vec) {
				pq.push(make_pair(vec[0], vec[1]));
			});

		while (extraStudents--)
		{
			auto c = pq.top();
			pq.pop();
			c.first++;
			c.second++;
			pq.push(c);
		}
		double result = 0.0;
		while (!pq.empty())
		{
			result += ratio(pq.top(), 0);
			pq.pop();
		}
		return result / N;
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


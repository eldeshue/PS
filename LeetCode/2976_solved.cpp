
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
private:
	using ll = long long;
	static constexpr ll INF = 1e9;
public:
	// solution method
	long long minimumCost(string source, string target,
		vector<char>& original, vector<char>& changed, vector<int>& cost)
	{
		// floyd-warshall
		vector<vector<ll>> totalCost(26, vector<ll>(26, INF));
		const int edgeNum = original.size();
		for (int i = 0; i < edgeNum; ++i)
		{
			const int from = original[i] - 'a';
			const int to = changed[i] - 'a';
			const int& c = cost[i];
			totalCost[from][to] = std::min(totalCost[from][to], static_cast<ll>(c));
		}

		for (int mid = 0; mid < 26; ++mid)
		{
			totalCost[mid][mid] = 0;
			for (int from = 0; from < 26; ++from)
			{
				for (int to = 0; to < 26; ++to)
				{
					totalCost[from][to]
						= std::min(totalCost[from][to],
							totalCost[from][mid] + totalCost[mid][to]);
				}
			}
		}

		ll result = 0;
		for (int i = 0; i < source.size(); ++i)
		{
			const ll& minCost = totalCost[source[i] - 'a'][target[i] - 'a'];
			if (minCost == INF)
			{
				result = -1;
				break;
			}
			result += minCost;
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

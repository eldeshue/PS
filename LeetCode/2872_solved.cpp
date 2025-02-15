
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <functional>
class Solution
{
public:
	// solution method
	int maxKDivisibleComponents(int n, vector<vector<int>>& edges,
		vector<int>& values, int k)
	{
		vector<vector<int>> graph(n);
		for (const auto& e : edges)
		{
			graph[e[0]].push_back(e[1]);
			graph[e[1]].push_back(e[0]);
		}

		// dfs
		int result = 1;
		vector<bool> visited(n, false);
		function<int(const int, const int)> dfs = [&](const int curNode, const int prevSum)
			{
				// accumulate
				int curSum = (prevSum + values[curNode]) % k;
				// traverse first
				for (const int nextNode : graph[curNode])
				{
					if (!visited[nextNode])
					{
						visited[nextNode] = true;
						const int futureSum = dfs(nextNode, curSum);
						if ((futureSum - curSum) % k == 0)
						{
							result++;
						}
						else
						{
							curSum = futureSum;
						}
					}
				}
				return curSum;
			};
		visited[0] = true;
		dfs(0, 0);
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


#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
class Solution
{
private:
	using pii = pair<int, int>;
	int bfs(vector<vector<int>> &graph)
	{
		const int N = graph.size();
		vector<bool> visited(N, false);

		queue<pii> q;
		q.push(make_pair(0, 0));
		visited[0] = true;
		while (!q.empty())
		{
			const auto [curCost, curNode] = q.front();
			q.pop();
			if (curNode == N - 1)
				return curCost;
			for (const int nextNode : graph[curNode])
			{
				if (!visited[nextNode])
				{
					visited[nextNode] = true;
					q.push(make_pair(curCost + 1, nextNode));
				}
			}
		}
		return -1;
	}
public:
	// solution method
	vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries)
	{
		vector<vector<int>> graph(n);
		for (int i = 0; i < n - 1; ++i)
		{
			graph[i].push_back(i + 1);
		}

		vector<int> result;
		for (const auto &q : queries)
		{
			graph[q[0]].push_back(q[1]);
			result.push_back(bfs(graph));
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


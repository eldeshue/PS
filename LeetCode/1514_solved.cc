
#include <iostream>
#include <vector>

using namespace std;
/*
	Reversed Dijkstra
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
#include <cmath>

class Solution
{
private:
	using Node = pair<double, int>;

public:
	double maxProbability(int n, vector<vector<int>> &edges,
						  vector<double> &succProb, int start_node, int end_node)
	{
		vector<double> visited(n, -2e9);
		vector<vector<Node>> graph(n, vector<Node>());
		priority_queue<Node, vector<Node>, less<Node>> pq;

		// build graph
		for (int i = 0; i < edges.size(); ++i)
		{
			const int &node1 = edges[i][0];
			const int &node2 = edges[i][1];
			const double cost = log2(succProb[i]);

			graph[node1].push_back(make_pair(cost, node2));
			graph[node2].push_back(make_pair(cost, node1));
		}

		// Dijkstra
		visited[start_node] = 0.0;
		pq.push(make_pair(0.0, start_node));
		while (!pq.empty())
		{
			const auto [curCost, curNode] = pq.top();
			pq.pop();

			for (const auto &[edgeCost, nextNode] : graph[curNode])
			{
				const double nextCost = curCost + edgeCost;
				if (visited[nextNode] < nextCost)
				{
					visited[nextNode] = nextCost;
					pq.push(make_pair(nextCost, nextNode));
				}
			}
		}
		// return solution
		return pow(2, visited[end_node]);
	}
	// solution method
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

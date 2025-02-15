#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	신호등 + 두 번째 최단거리

	시작했을 때, 초록불 -> 홀수에 빨간불

	일단 문제에서 주어진 cost per edge는 일정함. 따라서 에지의 수를 저장하는 bfs를 써야함.

	문제의 핵심은 두 번째 최단거리 계산하기에 있음.
	두 번째 최단거리를 구하기 위해서는 두 가지 방법 중 하나를 취하게 됨.

	1. 최단 거리 + 2 : 한 번 방문한 노드를 다시 방문할 수 있으므로, 최단경로를 찾은 후 직전 노드를 재방문하면 됨.
	2. 최단 거리 + 1 : 경로 탐색 과정에서 최단경로보다 단 1 큰 경로. -> 못찾을 수 있음.
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
class Solution
{
private:
	using pii = pair<int, int>;
	void updateCost(pii &cost, int val) // 해당 노드에 도착하는데에 경유하는 에지의 개수를 저장, first가 최소, second 차소
	{
		if (cost.first > val)
		{
			cost.second = cost.first;
			cost.first = val;
		}
		else if (cost.first < val && val < cost.second)
		{
			cost.second = val;
		}
	}
	int calFinalTime(const int &freq, const int &time, const int &change) // 총 에지의 개수를 바탕으로 시간을 계산함.
	{
		int result = 0;
		for (int i = 0; i < freq - 1; ++i)
		{
			result += time;
			if ((result / change) & 1) // wait till green
			{
				result = ((result / change) + 1) * change;
			}
		}
		return result + time;
	}

public:
	// solution method
	int secondMinimum(int n, vector<vector<int>> &edges, int time, int change)
	{
		vector<pii> visited(n + 1, {2e9, 2e9});
		vector<vector<int>> graph(n + 1);
		pii &result = visited[n];

		for (const auto &e : edges) // build bidirectional graph
		{
			const int &n1 = e[0];
			const int &n2 = e[1];
			graph[n1].push_back(n2);
			graph[n2].push_back(n1);
		}
		// bfs, ensures shortest path
		queue<pii> q;
		updateCost(visited[1], 0);
		q.push(make_pair(1, 0)); // node , freq
		while (!q.empty())
		{
			const auto [curNode, curCost] = q.front();
			q.pop();
			for (const auto &nextNode : graph[curNode])
			{
				if (visited[nextNode].second == 2e9) // until finding second min
				{
					updateCost(visited[nextNode], curCost + 1);
					q.push(make_pair(nextNode, curCost + 1));
				}
			}
		}
		return calFinalTime(result.second, time, change);
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

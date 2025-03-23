
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <queue>

class Solution
{
private:
public:
	int countPaths(int n, vector<vector<int>>& roads)
	{
		using ll = long long;
		constexpr const ll MAX = 1000000007;

		using pii = pair<ll, int>;
		vector<vector<ll>> min_cost(n, vector<ll>(n, MAX * MAX));
		std::vector<std::vector<pii>> graph(n);
		for (auto const& road : roads)
		{
			int const n1 = road[0];
			int const n2 = road[1];

			graph[n1].push_back(pii(road[2], n2));
			graph[n2].push_back(pii(road[2], n1));
		}

		// n <= 200, Dijkstra
		std::vector<ll> path_cnt(n, 0);
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		min_cost[0][0] = 0;
		path_cnt[0] = 1;
		pq.push(pii(0, 0));
		while (!pq.empty())
		{
			auto const [cur_cost, cur_node] = pq.top();
			pq.pop();
			if (cur_cost > min_cost[0][cur_node])
			{
				// skip
				continue;
			}

			// found new path
			for (auto const [cost, next_node] : graph[cur_node])
			{
				ll const next_cost = cur_cost + cost;
				if (next_cost == min_cost[0][next_node])	// same cost
				{
					path_cnt[next_node] = (path_cnt[next_node] + path_cnt[cur_node]) % MAX;
				}
				else if (next_cost < min_cost[0][next_node])	// better cost
				{
					min_cost[0][next_node] = next_cost;
					pq.push(pii(next_cost, next_node));

					// path count update
					path_cnt[next_node] = path_cnt[cur_node];
				}
			}
		}
		return path_cnt[n - 1];
	}
};

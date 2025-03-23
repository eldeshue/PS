
#include <iostream>
#include <vector>
#include <queue>

/*
	similar with leetcode, 1976
 */
int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;
	using pii = std::pair<ll, int>;
	constexpr const ll MAX = 1000000009;

	int n, m, s, e;
	std::cin >> n >> m >> s >> e;
	std::vector<ll> min_cost(n + 1, MAX * MAX);
	std::vector<std::vector<pii>> graph(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int n1, n2, c;
		std::cin >> n1 >> n2 >> c;

		graph[n1].push_back(pii(c, n2));
		graph[n2].push_back(pii(c, n1));
	}

	// n <= 200, Dijkstra
	std::vector<ll> path_cnt(n + 1, 0);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
	min_cost[s] = 0;
	path_cnt[s] = 1;
	pq.push(pii(0, s));
	while (!pq.empty())
	{
		auto const [cur_cost, cur_node] = pq.top();
		pq.pop();
		if (cur_cost > min_cost[cur_node])
		{
			// skip
			continue;
		}

		// found new path
		for (auto const [cost, next_node] : graph[cur_node])
		{
			ll const next_cost = cur_cost + cost;
			if (next_cost == min_cost[next_node])	// same cost
			{
				path_cnt[next_node] = (path_cnt[next_node] + path_cnt[cur_node]) % MAX;
			}
			else if (next_cost < min_cost[next_node])	// better cost
			{
				min_cost[next_node] = next_cost;
				pq.push(pii(next_cost, next_node));

				// path count update
				path_cnt[next_node] = path_cnt[cur_node];
			}
		}
	}
	std::cout << path_cnt[e];
}

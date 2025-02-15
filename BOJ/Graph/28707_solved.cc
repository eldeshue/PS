
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <tuple>

using Edge = std::tuple<int, int, int>;
using Stat = std::pair<int, std::string>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M, l, r, c;
	std::cin >> N;
	std::string start(N, 'x');
	for (int i = 0; i < N; ++i)
	{
		std::cin >> M;
		start[i] = M;
	}
	std::cin >> M;
	std::vector<Edge> e(M, {0, 0, 0});
	for (int i = 0; i < M; ++i)
	{
		std::cin >> l >> r >> c;
		e[i] = std::make_tuple(l - 1, r - 1, c);
	}
	// Dijkstra
	std::unordered_map<std::string, int> dist;
	std::priority_queue<Stat, std::vector<Stat>, std::greater<Stat>> pq;
	dist.insert({start, 0});
	pq.push({0, start});
	while (!pq.empty())
	{
		auto [cost, str] = pq.top();
		pq.pop();
		if (dist[str] < cost) // drop useless node
			continue;
		for (const auto &[l, r, c] : e)
		{
			const int nextCost = cost + c;
			// swap
			std::swap(str[l], str[r]);
			if (dist.find(str) == dist.end() || dist[str] > nextCost) // smaller than
			{
				dist[str] = nextCost;
				pq.push({nextCost, str});
			}
			// swap
			std::swap(str[l], str[r]);
		}
	}
	// get result
	std::sort(start.begin(), start.end());
	if (dist.find(start) == dist.end())
		std::cout << -1;
	else
		std::cout << dist[start];
}

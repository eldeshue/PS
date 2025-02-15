
#include <iostream>
#include <vector>
#include <queue>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M, R, result = 0;
	std::cin >> N >> M >> R;
	std::vector<int> values(N + 1, 0);
	std::vector<std::vector<pii>> graph(N + 1);
	for (int i = 1; i <= N; ++i)
		std::cin >> values[i];
	for (int i = 0; i < R; ++i)
	{
		int n1, n2, c;
		std::cin >> n1 >> n2 >> c;
		graph[n1].push_back(std::make_pair(n2, c));
		graph[n2].push_back(std::make_pair(n1, c));
	}
	auto dijkstra = [&](int startNode)-> int
	{
		std::vector<int> totalCosts(N + 1, 2e9);
		std::priority_queue<pii, std::vector<pii>, std::greater<pii>> nextNodes;

		totalCosts[startNode] = 0;
		nextNodes.push(std::make_pair(0, startNode));
		while (!nextNodes.empty())
		{
			const auto [curCost, curNode] = nextNodes.top();
			nextNodes.pop();
			if (curCost > totalCosts[curNode])
				continue;
			for (const auto [nextNode, cost] : graph[curNode])
			{
				const int nextCost = curCost + cost;
				if (totalCosts[nextNode] > nextCost)
				{
					totalCosts[nextNode] = nextCost;
					nextNodes.push(std::make_pair(nextCost, nextNode));
				}
			}
		}
		// collect values
		int result = 0;
		for (int i = 1; i <= N; ++i)
		{
			if (totalCosts[i] <= M)
				result += values[i];
		}
		return result;
	};
	for (int start = 1; start <= N; ++start)
	{
		result = std::max(result, dijkstra(start));
	}
	std::cout << result;
}
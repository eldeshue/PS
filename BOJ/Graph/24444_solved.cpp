
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	int N, M, R;
	std::cin >> N >> M >> R;
	std::vector<std::vector<int>> graph(N + 1);
	std::vector<pii> edges(M);
	for (auto& e : edges)
		std::cin >> e.first >> e.second;

	// build graph
	std::sort(edges.begin(), edges.end());
	for (auto const& e : edges)
	{
		graph[e.second].push_back(e.first);
		graph[e.first].push_back(e.second);
	}

	// dfs, print
	std::vector<int> visited(N + 1, 0);
	std::function<void(int const)> bfs = [&](int const startNode) {
		std::queue<int> q;
		int time = 1;

		visited[startNode] = time++;
		q.push(startNode);
		while (!q.empty())
		{
			int const curNode = q.front();
			q.pop();

			for (int const nextNode : graph[curNode])
			{
				if (visited[nextNode] == 0)
				{
					visited[nextNode] = time++;
					q.push(nextNode);
				}
			}
		}
		};
	bfs(R);

	// print
	for (int i = 1; i <= N; ++i)
	{
		std::cout << visited[i] << '\n';
	}
}
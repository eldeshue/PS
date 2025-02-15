
#include <algorithm>
#include <functional>
#include <iostream>
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
	// 에지들을 노드 순서대로 정렬한 다음 연결하면
	// adj list에서 자연스레 정렬된 순서로 순회할 수 있음.
	std::sort(edges.begin(), edges.end());
	for (auto const& e : edges)
	{
		graph[e.second].push_back(e.first);	// first를 먼저 정렬했으므로, 에지의 first < second임
		graph[e.first].push_back(e.second); // 따라서 더 작은 first를 먼저 연결함
	}

	// dfs, print
	std::vector<int> visited(N + 1, 0);
	int time = 1;
	std::function<void(int const)> dfs = [&](int const curNode) {
		for (int const nextNode : graph[curNode])
		{
			if (!visited[nextNode])
			{
				visited[nextNode] = time++;
				dfs(nextNode);
			}
		}
		};
	visited[R] = time++;
	dfs(R);

	// print
	for (int i = 1; i <= N; ++i)
	{
		std::cout << visited[i] << '\n';
	}
}
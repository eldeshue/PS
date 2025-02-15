
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<bool> visited(N, false);
	std::vector<std::string> graph(N);
	for (auto& g : graph)
		std::cin >> g;
	int const edgeCnt = std::accumulate(graph.begin(), graph.end(), 0,
		[](int const acc, std::string const& str) {
			return acc + std::accumulate(str.begin(), str.end(), 0, [](int const acc, char c) {
				return acc + (c == 'Y');
				});
		}) / 2;

	auto bfs = [&](int const startNode) {
		std::queue<int> q;

		visited[startNode] = true;
		q.push(startNode);
		while (!q.empty())
		{
			int const cur = q.front();
			q.pop();
			for (int next = 0; next < N; ++next)
			{
				if (!visited[next] && graph[cur][next] == 'Y')
				{
					visited[next] = true;
					q.push(next);
				}
			}
		}
		};

	int ccCnt = 0;
	for (int i = 0; i < N; ++i)
	{
		if (!visited[i])
		{
			bfs(i);
			ccCnt++;
		}
	}

	if (N == 1)
	{
		std::cout << 0;
		return 0;
	}
	if (std::find_if(graph.begin(), graph.end(), [=](std::string const& str) {
		return (str == std::string(N, 'N'));
		}) != graph.end() || (edgeCnt < N - 1))
	{
		std::cout << -1;
	}
	else
	{
		std::cout << ccCnt - 1;
	}
}
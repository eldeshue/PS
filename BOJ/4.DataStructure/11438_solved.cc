
#include <iostream>
#include <vector>
#include <functional>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> graph(N + 1);
	for (int i = 0; i < N - 1; ++i)
	{
		int node1, node2;
		std::cin >> node1 >> node2;
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}
	// sparse table
	std::vector<std::vector<int>> parent(18, std::vector<int>(N + 1, 1)); // sparse table,
	std::vector<bool> visited(N + 1, false);
	std::vector<int> depth(N + 1, 0);
	// dfs
	std::function<void(int)> dfs = [&parent = parent[0], &visited, &graph, &dfs, &depth](int curNode)
	{
		for (const int child : graph[curNode])
		{
			if (!visited[child])
			{
				visited[child] = true;
				parent[child] = curNode;
				depth[child] = depth[curNode] + 1;
				dfs(child);
			}
		}
	};
	visited[1] = true;
	dfs(1);

	// set sparse table, 결합법칙 성립
	for (int i = 1; i < 18; ++i) // power of 2
		for (int node = 1; node <= N; ++node)
			parent[i][node] = parent[i - 1][parent[i - 1][node]];

	// query
	auto getLCA = [&](int node1, int node2)
	{
		int d1 = depth[node1];
		int d2 = depth[node2];
		if (d1 != d2)
		{
			// move deeper one up, make d1 and d2 same
			int &deeperNode = (d1 > d2) ? node1 : node2;
			int diff = std::abs(d1 - d2);
			for (int pos = 0; pos < 18; ++pos)
			{
				if (diff & (1 << pos))
				{
					deeperNode = parent[pos][deeperNode];
				}
			}
		}
		// search, lower bound, log N, jump
		if (node1 == node2)
			return node1;
		for (int pos = 17; pos >= 0; --pos)
		{
			const int nextNode1 = parent[pos][node1];
			const int nextNode2 = parent[pos][node2];
			if (nextNode1 != nextNode2)
			{
				node1 = nextNode1;
				node2 = nextNode2;
			}
		}
		return parent[0][node1];
	};
	int M;
	std::cin >> M;
	while (M--)
	{
		int node1, node2;
		std::cin >> node1 >> node2;
		std::cout << getLCA(node1, node2) << '\n';
	}
}

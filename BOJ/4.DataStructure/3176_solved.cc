

#include <iostream>
#include <vector>
#include <functional>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<pii>> graph(N + 1);
	for (int i = 0; i < N - 1; ++i)
	{
		int node1, node2, cost;
		std::cin >> node1 >> node2 >> cost;
		graph[node1].push_back(std::make_pair(node2, cost));
		graph[node2].push_back(std::make_pair(node1, cost));
	}
	// sparse table
	std::vector<std::vector<int>> parent(18, std::vector<int>(N + 1, 1));		// sparse table for node
	std::vector<std::vector<pii>> edges(18, std::vector<pii>(N + 1, {2e9, 0})); // sparse table or min, max cost
	std::vector<bool> visited(N + 1, false);
	std::vector<int> depth(N + 1, 0);
	// dfs
	std::function<void(int)> dfs = [&parent = parent[0], &visited, &graph, &dfs, &depth, &edges = edges[0]](int curNode)
	{
		for (const auto [child, cost] : graph[curNode])
		{
			if (!visited[child])
			{
				visited[child] = true;
				parent[child] = curNode;
				depth[child] = depth[curNode] + 1;
				edges[child] = std::make_pair(cost, cost); // set initial edge cost
				dfs(child);
			}
		}
	};
	visited[1] = true;
	dfs(1);

	// set sparse table, 결합법칙 성립
	for (int i = 1; i < 18; ++i) // power of 2
	{
		for (int node = 1; node <= N; ++node)
		{
			const int midNode = parent[i - 1][node];
			parent[i][node] = parent[i - 1][midNode];
			// first is minimum, second is maximum
			edges[i][node] = std::make_pair(std::min(edges[i - 1][midNode].first, edges[i - 1][node].first),
											std::max(edges[i - 1][midNode].second, edges[i - 1][node].second));
		}
	}

	// query
	auto getLCA = [&](int node1, int node2)
	{
		const int d1 = depth[node1];
		const int d2 = depth[node2];
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
		int lcaNode = node1;
		if (node1 != node2)
		{
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
			lcaNode = parent[0][node1];
		}
		// return dist
		return std::make_pair(d1 - depth[lcaNode], d2 - depth[lcaNode]);
	};
	int minCost = 2e9, maxCost = 0;
	auto updateMinMaxCost = [&](int node, int dist)
	{
		for (int pos = 0; pos < 18; ++pos)
		{
			if (dist & (1 << pos))
			{
				minCost = std::min(minCost, edges[pos][node].first);
				maxCost = std::max(maxCost, edges[pos][node].second);
				node = parent[pos][node];
			}
		}
	};
	int K;
	std::cin >> K;
	while (K--) // handle query
	{
		int node1, node2;
		std::cin >> node1 >> node2;
		// get dist from node to LCA node
		const auto [d1, d2] = getLCA(node1, node2);
		// accumulate sparse table
		minCost = 2e9, maxCost = 0;
		updateMinMaxCost(node1, d1);
		updateMinMaxCost(node2, d2);
		std::cout << minCost << ' ' << maxCost << '\n';
	}
}

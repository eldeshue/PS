
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using pii = std::pair<long long, long long>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
	std::stack<long long> st;

	long long n, m, s, e, c;
	std::cin >> n >> m;
	std::vector<long long> parent(n, -1);
	std::vector<long long> totalCost(n, 2e9);
	std::vector<std::vector<pii>> graph(n);
	for (int i = 0; i < m; ++i)
	{
		std::cin >> s >> e >> c;
		graph[s - 1].push_back(std::make_pair(e - 1, c));
	}
	std::cin >> s >> e;
	s--;
	e--;

	// Dijkstra
	totalCost[s] = 0;
	pq.push(std::make_pair(0, s));
	while (!pq.empty())
	{
		auto [curCost, curNode] = pq.top();
		pq.pop();
		if (curCost > totalCost[e])
			continue;
		for (const auto &[nextNode, cost] : graph[curNode])
		{
			long long nextCost = curCost + cost;
			if (totalCost[nextNode] > nextCost)
			{
				totalCost[nextNode] = nextCost;
				parent[nextNode] = curNode;
				pq.push(std::make_pair(nextCost, nextNode));
			}
		}
	}

	// trace parent
	long long curNode = e;
	while (curNode != -1)
	{
		st.push(curNode);
		curNode = parent[curNode];
	}

	// prlong long
	std::cout << totalCost[e] << '\n'
			  << st.size() << '\n';
	while (!st.empty())
	{
		std::cout << st.top() + 1 << ' ';
		st.pop();
	}
}


/*
	BOJ. 12012

	25172과 완벽하게 동일함.
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stack>

class UnionFind
{
private:
	int numGroup;
	mutable std::vector<int> parent;

public:
	UnionFind(int size) : parent(size, -1), numGroup(size) {};
	int getGroupNum() const { return numGroup; }
	int getMaxGroupSize() const
	{
		int result = 0;
		std::for_each(parent.begin(), parent.end(), [&](const int& val) -> void
			{if (val < 0) { result = std::max(result, std::abs(val)); } });
		return result;
	};
	int find(int node) const // pass compression, is it const?
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	bool isSameGroup(int node1, int node2) const // ???
	{
		node1 = find(node1);
		node2 = find(node2);
		return node1 == node2;
	}
	void unite(int node1, int node2) // unite by rank
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] >= parent[node2]) // node2's rank is higher
		{
			if (parent[node1] == parent[node2])	// same rank
			{
				parent[node1]--;	// rank increase
			}
			parent[node1] = node2;
		}
		else // node1's rank is higher than node2's rank
		{
			parent[node2] = node1;
		}
		numGroup--;
		return;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> graph(N + 1);
	for (int i = 0; i < M; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	std::vector<int> queries(N);
	for (auto& q : queries)
		std::cin >> q;

	// reversing query
	UnionFind uf(N + 1);
	std::stack<bool> result;
	int num_cc = 0;
	std::vector<bool> is_active(N + 1, false);
	for (auto ritr = queries.rbegin(); ritr != queries.rend(); ++ritr)	// N + 2M
	{
		int const new_node = *ritr;
		++num_cc;
		is_active[new_node] = true;
		for (auto const opponent : graph[new_node])
		{
			if (is_active[opponent] && uf.find(new_node) != uf.find(opponent))
			{
				uf.unite(new_node, opponent);
				--num_cc;
			}
		}

		// is single connected component
		result.push(num_cc == 1);
	}

	// print result
	while (!result.empty())
	{
		if (result.top())
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
		result.pop();
	}
}

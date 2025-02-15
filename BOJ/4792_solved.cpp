
#include <iostream>

#include <algorithm>
#include <vector>

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
	void unite(int node1, int node2) // unite by size
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] > parent[node2]) // node2's size is bigger
		{
			parent[node2] += parent[node1];
			parent[node1] = node2;
		}
		else // node1's size is bigger or same
		{
			parent[node1] += parent[node2];
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
	using Edge = std::pair<int, int>;

	char c;
	int n, m, k, f, t;
	while (true)
	{
		std::cin >> n >> m >> k;
		if (n == 0 && m == 0 && k == 0)
			break;

		std::vector<Edge> red, blue;
		for (int i = 0; i < m; ++i)
		{
			std::cin >> c >> f >> t;
			if (c == 'R')
				red.push_back(std::make_pair(f, t));
			else if (c == 'B')
				blue.push_back(std::make_pair(f, t));
		}

		// get blue minimum graph
		UnionFind minBlueGraph(n + 1);
		int minBlueEdgeCnt = 0;
		for (auto const e : red)
		{
			minBlueGraph.unite(e.first, e.second);
		}
		for (auto const e : blue)
		{
			minBlueEdgeCnt += !(minBlueGraph.isSameGroup(e.first, e.second));
			minBlueGraph.unite(e.first, e.second);
		}

		// get blue maximum graph
		UnionFind maxBlueGraph(n + 1);
		int maxBlueEdgeCnt = 0;
		for (auto const e : blue)
		{
			maxBlueEdgeCnt += !(maxBlueGraph.isSameGroup(e.first, e.second));
			maxBlueGraph.unite(e.first, e.second);
		}
		for (auto const e : red)
		{
			maxBlueGraph.unite(e.first, e.second);
		}

		// blue를 최소, 최대로 사용하여 구성하는 스패닝 트리에서
		// blue edge의 개수를 구하면, 그 둘 사이의 개수의 edge를 사용하여
		// 만드는 스패닝 트리는 존재한다. 즉 min blue <= k <= maxBlueCnt가 된다.
		std::cout << ((maxBlueGraph.getGroupNum() == 2)
			&& (minBlueGraph.getGroupNum() == 2)
			&& (minBlueEdgeCnt <= k)
			&& (k <= maxBlueEdgeCnt)) << '\n';
	}
}

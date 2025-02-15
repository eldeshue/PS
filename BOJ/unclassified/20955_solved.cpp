
#include <iostream>
#include <vector>
#include <algorithm>

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
	int find(int node) const
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	bool isSameGroup(int node1, int node2) const
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

	int N, M, u, v, cutCnt = 0;
	std::cin >> N >> M;
	UnionFind uf(N + 1);
	for (int i = 0; i < M; ++i)
	{
		std::cin >> u >> v;
		if (uf.find(u) == uf.find(v))
			cutCnt++;
		else
			uf.unite(u, v);
	}
	std::cout << cutCnt + uf.getGroupNum() - 2;
}

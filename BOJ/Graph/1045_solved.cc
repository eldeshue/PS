
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

/*
	MST, Kruskal

	주어진 에지들에 대하여 우선순위가 높은 에지부터 kruskal을 수행하면 문제의 답을 얻을 수 있음.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using Edge = std::pair<int, int>;

	int N, M;
	std::cin >> N >> M;
	std::vector<Edge> edges;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			char c;
			std::cin >> c;
			if (i < j && c == 'Y')
			{
				edges.push_back(std::make_pair(i, j));
			}
		}
	}

	// compare with M
	if (M < (N - 1) || edges.size() < M)
	{
		std::cout << -1;
		return 0;
	}

	// count necessary edges, kruskal + greedy
	UnionFind uf(N);
	std::vector<int> degree(N, 0);
	std::vector<bool> usedEdge(edges.size(), false);
	int connectCnt = 0;

	for (int i = 0; i < edges.size(); ++i)
	{
		if (!uf.isSameGroup(edges[i].first, edges[i].second))
		{
			uf.unite(edges[i].first, edges[i].second);
			usedEdge[i] = true;
			++degree[edges[i].first];
			++degree[edges[i].second];
			++connectCnt;
		}
	}

	if (uf.getGroupNum() != 1)
	{
		std::cout << -1;
		return 0;
	}

	// count redundant edges, greedy
	for (int i = 0; i < edges.size(); ++i)
	{
		if (connectCnt < M && !usedEdge[i])
		{
			++degree[edges[i].first];
			++degree[edges[i].second];
			++connectCnt;
		}
	}

	// print
	for (int i = 0; i < N; ++i)
	{
		std::cout << degree[i] << ' ';
	}
	return 0;
}

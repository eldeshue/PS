
#include <iostream>
#include <queue>
#include <tuple>

#include <algorithm>
#include <functional>
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

	// input
	using pii = std::pair<int, int>;
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<pii> red, blue;
	for (int i = 0; i < m; ++i)
	{
		char c;
		int n1, n2;
		std::cin >> c >> n1 >> n2;
		if (c == 'B')
			blue.push_back(std::make_pair(n1, n2));
		if (c == 'R')
			red.push_back(std::make_pair(n1, n2));
	}

	// make min blue spanning tree
	// adj matrix
	std::vector<std::vector<char>> graph(n + 1, std::vector<char>(n + 1, 0));
	UnionFind uf(n + 1);
	int blueCnt = 0;
	for (auto const [n1, n2] : red)	// red
	{
		if (!uf.isSameGroup(n1, n2))
		{
			uf.unite(n1, n2);
			graph[n1][n2] = 'R';
			graph[n2][n1] = 'R';
		}
	}
	for (auto const [n1, n2] : blue)	// blue
	{
		if (!uf.isSameGroup(n1, n2))
		{
			uf.unite(n1, n2);
			graph[n1][n2] = 'B';
			graph[n2][n1] = 'B';
			//
			++blueCnt;
		}
	}

	// dfs, replace edge
	int color = 0;
	int r1 = -1, r2 = -1;
	std::vector<int> visited(n + 1, -1);
	std::function<bool(int, int)> dfs = [&](int curNode, int goal) {
		if (curNode == goal)
		{
			return true;
		}
		bool result = false;
		for (int nextNode = 1; nextNode <= n; ++nextNode)
		{
			if (graph[curNode][nextNode] && visited[nextNode] != color)
			{
				visited[nextNode] = color;
				result = dfs(nextNode, goal);
				if (result)
				{
					if (graph[curNode][nextNode] == 'R')
					{
						r1 = curNode;
						r2 = nextNode;
					}
					break;
				}
			}
		}
		return result;
		};

	// for rest of blue edges
	for (auto const [n1, n2] : blue)	// blue
	{
		if (blueCnt >= k)
			break;
		r1 = -1;
		if (graph[n1][n2] == 0 && (visited[n1] = ++color) && dfs(n1, n2) && r1 != -1)
		{
			graph[n1][n2] = 'B';
			graph[n2][n1] = 'B';
			graph[r1][r2] = 0;
			graph[r2][r1] = 0;
			blueCnt++;
		}
	}

	// print
	if (blueCnt != k)
	{
		std::cout << 0;
		return 0;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = i + 1; j <= n; ++j)
		{
			if (graph[i][j])
				std::cout << i << ' ' << j << '\n';
		}
	}
}
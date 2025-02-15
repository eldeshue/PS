
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <vector>
#include <algorithm>
#include <numeric>
class UnionFind
{
private:
	int numGroup;
	mutable std::vector<int> parent;

public:
	UnionFind(int size) : parent(size, -1), numGroup(size) {};
	int getGroupNum() const { return numGroup; }
	int getSingleNum() const { return std::accumulate(parent.begin(), parent.end(), 0, [](int const acc, int const n) { return acc + (n == -1); }); };
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
#include <unordered_map>
class Solution
{
public:
	// solution method
	int countServers(vector<vector<int>>& grid) {
		int const N = [&]() {
			int result = 0;
			for (int r = 0; r < grid.size(); ++r)
			{
				for (int c = 0; c < grid[r].size(); ++c)
				{
					result += grid[r][c];
				}
			}
			return result;
			}();
			unordered_map<int, int> rowMap, colMap;
			UnionFind uf(N);
			int id = 0;
			for (int r = 0; r < grid.size(); ++r)
			{
				for (int c = 0; c < grid[r].size(); ++c)
				{
					if (grid[r][c])
					{
						if (rowMap.find(r) == rowMap.end())
						{
							rowMap[r] = id;
						}
						else
						{
							uf.unite(rowMap[r], id);
						}
						if (colMap.find(c) == colMap.end())
						{
							colMap[c] = id;
						}
						else
						{
							uf.unite(colMap[c], id);
						}
						id++;
					}
				}
			}
			return N - uf.getSingleNum();
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}

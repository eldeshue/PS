
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
class Solution
{
private:
	class UnionFind
	{
	private:
		int numGroup;
		mutable vector<int> parent;

	public:
		UnionFind(int size) : parent(size, -1), numGroup(size) {};
		int getGroupNum() const { return numGroup; }
		int getMaxGroupSize() const
		{
			int result = 0;
			for_each(parent.begin(), parent.end(), [&](const int& val) -> void
				{if (val < 0) { result = max(result, abs(val)); } });
			return result;
		};
		int find(int node) const // pass compression
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
public:
	// solution method
	int regionsBySlashes(vector<string>& grid)
	{
		const int width = grid.size() + 1;
		const int numVertex = width * width;
		UnionFind uf(numVertex);

		// boundary
		for (int i = 0; i < width - 1; ++i)
			uf.unite(i, i + 1);
		for (int i = 0; i < width - 1; ++i)
			uf.unite((width - 1) * width + i, (width - 1) * width + i + 1);
		for (int i = 0; i < width - 1; ++i)
			uf.unite(i * width, (i + 1) * width);
		for (int i = 0; i < width - 1; ++i)
			uf.unite(i * width + (width - 1), (i + 1) * width + (width - 1));

		// traverse graph
		int result = 1;
		for (int r = 0; r < width - 1; ++r)
		{
			for (int c = 0; c < width - 1; ++c)
			{
				int node1, node2;
				if (grid[r][c] == ' ')
					continue;
				else if (grid[r][c] == '/')	// slash
				{
					node1 = r * width + c + 1;
					node2 = (r + 1) * width + c;
				}
				else if (grid[r][c] == '\\')	// reverse slash
				{
					node1 = r * width + c;
					node2 = (r + 1) * width + c + 1;
				}
				if (uf.isSameGroup(node1, node2))
					result++;
				else
					uf.unite(node1, node2);
			}
		}
		return result;
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

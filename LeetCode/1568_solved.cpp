

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
#include <algorithm>
class Solution
{
private:
	using pii = pair<int, int>;
	static constexpr int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
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
	int cntCC(vector<vector<int>> &grid)
	{
		const int N = grid.size();
		const int M = grid[0].size();
		UnionFind uf(N * M);
		int emptyCnt = 0;

		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if (grid[r][c] == 1)
				{
					for (int i = 0; i < 4; ++i)
					{
						int nr = r + dir[i][0];
						int nc = c + dir[i][1];
						if (0 <= nr && nr < N
							&& 0 <= nc && nc < M
							&& grid[nr][nc] == 1)
						{
							uf.unite(r * M + c, nr * M + nc);
						}
					}
				}
				else
				{
					emptyCnt++;
				}
			}
		}
		return uf.getGroupNum() - emptyCnt;
	}
public:
	// solution method
	int minDays(vector<vector<int>>& grid)
	{
		const int N = grid.size();
		const int M = grid[0].size();

		if (cntCC(grid) != 1)
			return 0;
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if (grid[r][c] == 1)
				{
					grid[r][c] = 0;
					if (cntCC(grid) != 1)
					{
						return 1;
					}
					grid[r][c] = 1;
				}
			}
		}
		return 2;
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

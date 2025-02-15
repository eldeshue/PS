
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
#include <unordered_set>
#include <numeric>
class Solution
{
public:
	// solution method
	int largestIsland(vector<vector<int>>& grid)
	{
		using Point = pair<int, int>;
		const int N = grid.size();
		static constexpr const int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
		// in range
		auto inRange = [&](int const r, int const c) { return ((0 <= r) && (r < N) && (0 <= c) && (c < N)); };
		// bfs
		auto bfs = [&](int const sr, int const sc, int const curColor) {
			queue<Point> q;

			int sum = 1;
			grid[sr][sc] = curColor;
			q.push(make_pair(sr, sc));
			while (!q.empty())
			{
				auto [r, c] = q.front();
				q.pop();
				// 
				for (int d = 0; d < 4; ++d)
				{
					int const nr = r + dir[d][0];
					int const nc = c + dir[d][1];
					if (inRange(nr, nc) && grid[nr][nc] == 1)
					{
						++sum;
						grid[nr][nc] = curColor;
						q.push(make_pair(nr, nc));
					}
				}
			}
			return sum;
			};
		int color = 1;
		vector<int> islandSize(2, 0);
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < N; ++c)
			{
				if (grid[r][c] == 1)
				{
					islandSize.push_back(bfs(r, c, ++color));
				}
			}
		}

		// search max sum
		int result = accumulate(islandSize.begin(), islandSize.end(), 0, [](int const acc, int const n) {return max(acc, n); });
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < N; ++c)
			{
				if (grid[r][c] == 0)
				{
					unordered_set<int> adjIsland;
					int tempSum = 1;
					for (int d = 0; d < 4; ++d)
					{
						int nr = r + dir[d][0];
						int nc = c + dir[d][1];
						if (inRange(nr, nc) && !adjIsland.count(grid[nr][nc]))	// in range 
						{
							adjIsland.insert(grid[nr][nc]);
							tempSum += islandSize[grid[nr][nc]];
						}
					}
					result = max(result, tempSum);
				}
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


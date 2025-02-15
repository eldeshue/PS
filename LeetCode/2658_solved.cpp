
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
class Solution
{
public:
	// solution method
	int findMaxFish(vector<vector<int>>& grid) {
		int const M = grid.size();
		int const N = grid[0].size();
		auto inRange = [=](int r, int c) {
			return ((0 <= r) && (r < M) && (0 <= c) && (c < N));
			};
		auto bfs = [&](int const startRow, int const startCol) {
			static constexpr const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
			using pii = pair<int, int>;
			queue<pii> q;
			int sum = 0;

			sum += grid[startRow][startCol];
			grid[startRow][startCol] = 0;
			q.push(make_pair(startRow, startCol));
			while (!q.empty())
			{
				auto const [curRow, curCol] = q.front();
				q.pop();
				for (int d = 0; d < 4; ++d)
				{
					int const nexRow = curRow + dir[d][0];
					int const nexCol = curCol + dir[d][1];
					if (inRange(nexRow, nexCol) && grid[nexRow][nexCol])
					{
						sum += grid[nexRow][nexCol];
						grid[nexRow][nexCol] = 0;
						q.push(make_pair(nexRow, nexCol));
					}
				}
			}
			return sum;
			};
		int result = 0;
		for (int r = 0; r < M; ++r)
		{
			for (int c = 0; c < N; ++c)
			{
				if (grid[r][c])
				{
					result = max(result, bfs(r, c));
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



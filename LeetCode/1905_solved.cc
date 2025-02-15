
/*
	sub island

	기존의 아일랜드 문제의 응용. 기존의 문제가 하나의 보드에서 아일랜드가 몇개였는지를 찾았다면,
	이 문제는 거기에 더해서 어떤 점들의 집합이 온전히 다른 하나의 부분이 되는지, 즉 포함 관계를 효율적으로 찾는 문제.

	함께 bfs를 돌면 되는 문제인듯. 둘을 같은색으로 칠하면서, 둘의 색이 달라지는 부분이 있는지 확인하면 됨.

	먼저 보드 1을 칠하고, 보드 2를 칠하면서, 색이 일치하지 않는 부분이 있는지 확인하는 것.
*/
#include <iostream>
#include <vector>

using namespace std;

// #pragma GCC optimize("03")
// #pragma GCC target("avx")
// #pragma GCC target("-fsplit-loops")
#include <functional>
#include <queue>
#include <unordered_set>
class Solution
{
private:
	using Coordinate = pair<int, int>; // row, colum
	using Board = vector<vector<int>>;
	static constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
	// solution method
	int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
	{
		const int maxRow = grid1.size();
		const int maxCol = grid1[0].size();
		auto bfsCheckSomething = [maxRow, maxCol](Board &b, Coordinate start, const int color, auto check)
		{
			queue<Coordinate> q;
			bool result = true;

			b[start.first][start.second] = color;
			q.push(start);
			while (!q.empty())
			{
				const auto [curR, curC] = q.front();
				q.pop();
				for (int d = 0; d < 4; ++d)
				{
					const int nextR = curR + dir[d][0];
					const int nextC = curC + dir[d][1];
					if (((0 <= nextR && nextR < maxRow)		//
						 && (0 <= nextC && nextC < maxCol)) //
						&& b[nextR][nextC] == 1)			// not visited
					{
						b[nextR][nextC] = color;
						if (!check(nextR, nextC)) // do something
						{
							result = false;
						}
						q.push(make_pair(nextR, nextC));
					}
				}
			}
			return result;
		};

		// check 1 2
		auto checkIsland1 = [](int r, int c)
		{ return true; };
		auto checkIsland2 = [&grid1, &grid2](int r, int c)
		{ return grid1[r][c] == grid2[r][c]; };

		auto bfsIsland1 = bind(bfsCheckSomething, placeholders::_1, placeholders::_2, placeholders::_3, checkIsland1);
		auto bfsIsland2 = bind(bfsCheckSomething, placeholders::_1, placeholders::_2, placeholders::_3, checkIsland2);

		// paint island1
		int color = 2;
		for (int r = 0; r < maxRow; ++r)
		{
			for (int c = 0; c < maxCol; ++c)
			{
				if (grid1[r][c] == 1)
				{
					bfsIsland1(grid1, make_pair(r, c), color);
					color++;
				}
			}
		}

		int cnt = 0;
		// paint island2, diff
		for (int r = 0; r < maxRow; ++r)
		{
			for (int c = 0; c < maxCol; ++c)
			{
				if (grid2[r][c] == 1 && grid1[r][c] != 0)
				{
					if (bfsIsland2(grid2, make_pair(r, c), grid1[r][c]))
						cnt++;
				}
			}
		}
		return cnt;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<vector<int>> input1 = {{1, 1, 1, 0, 0}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 1, 1}};
	vector<vector<int>> input2 = {{1, 1, 1, 0, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 0, 1, 0}};
	Solution test;
	std::cout << test.countSubIslands(input1, input2);
}

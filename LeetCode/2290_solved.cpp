

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
#include <tuple>
class Solution
{
private:
	constexpr static int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
public:
	// solution method
	using tiii = tuple<int, int, int>;
	int minimumObstacles(vector<vector<int>>& grid)
	{
		const int N = grid.size();
		const int M = grid[0].size();
		vector<vector<int>> visited(N, vector<int>(M, 2e9));

		auto inRange = [&](const int r, const int c)
			{
				return (0 <= r && r < N) && (0 <= c && c < M);
			};
		priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
		pq.push(make_tuple(0, 0, 0));
		while (!pq.empty())
		{
			const auto [curCost, curRow, curCol] = pq.top();
			pq.pop();
			if (visited[curRow][curCol] < curCost)
				continue;
			for (int i = 0; i < 4; ++i)
			{
				const int nextRow = curRow + dir[i][0];
				const int nextCol = curCol + dir[i][1];
				if (inRange(nextRow, nextCol)
					&& curCost + grid[nextRow][nextCol] < visited[nextRow][nextCol])
				{
					const int nextCost = curCost + grid[nextRow][nextCol];
					visited[nextRow][nextCol] = nextCost;
					pq.push(make_tuple(nextCost, nextRow, nextCol));
				}
			}
		}
		return visited[N - 1][M - 1];
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

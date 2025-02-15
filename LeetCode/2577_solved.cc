
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
#include <tuple>
class Solution
{
private:
	constexpr static int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
	// solution method
	using tiii = tuple<int, int, int>;

	int minimumTime(vector<vector<int>> &grid)
	{
		const int N = grid.size();
		const int M = grid[0].size();
		auto inRange = [&](const int r, const int c)
		{
			return (0 <= r && r < N) && (0 <= c && c < M);
		};
		if (2 < grid[1][0] && 2 < grid[0][1]) // initial position error
		{
			return -1;
		}
		vector<vector<int>> visited(N, vector<int>(M, 2e9));

		priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
		visited[0][0] = 0;
		pq.push(make_tuple(0, 0, 0));
		while (!pq.empty())
		{
			const auto [curTime, curRow, curCol] = pq.top();
			pq.pop();
			if (visited[curRow][curCol] < curTime)
				continue;
			for (int i = 0; i < 4; ++i)
			{
				const int nextRow = curRow + dir[i][0];
				const int nextCol = curCol + dir[i][1];
				if (inRange(nextRow, nextCol))
				{
					const int nextTime = curTime + 1 + (curTime + 1 < grid[nextRow][nextCol]) * (((grid[nextRow][nextCol] - curTime) >> 1) << 1);
					if (nextTime < visited[nextRow][nextCol])
					{
						visited[nextRow][nextCol] = nextTime;
						pq.push(make_tuple(nextTime, nextRow, nextCol));
					}
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
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}

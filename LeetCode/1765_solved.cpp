
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
	static constexpr const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
public:
	using tiii = tuple<int, int, int>;
	// solution method
	vector<vector<int>> highestPeak(vector<vector<int>>& isWater)
	{
		int const N = isWater.size();
		int const M = isWater[0].size();
		queue<tiii> q;
		auto inRange = [=](int const row, int const col) {
			return ((0 <= row) && (row < N) && (0 <= col) && (col < M));
			};
		vector<vector<int>> heights(N, vector<int>(M, -1));
		for (int r = 0; r < N; ++r)
			for (int c = 0; c < M; ++c)
				if (isWater[r][c])
				{
					heights[r][c] = 0;
					q.push(make_tuple(r, c, 0));
				}
		//bfs
		while (!q.empty())
		{
			auto const [curRow, curCol, curCost] = q.front();
			q.pop();
			for (int d = 0; d < 4; ++d)
			{
				int const nextRow = curRow + dir[d][0];
				int const nextCol = curCol + dir[d][1];
				if (inRange(nextRow, nextCol)
					&& heights[nextRow][nextCol] == -1)
				{
					heights[nextRow][nextCol] = curCost + 1;
					q.push(make_tuple(nextRow, nextCol, curCost + 1));
				}
			}
		}
		return heights;
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

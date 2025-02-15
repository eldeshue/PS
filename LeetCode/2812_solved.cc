
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <queue>
using P = pair<int, int>;

class Solution
{
private:
	static constexpr int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int N;
	vector<vector<int>> safeness;
	inline bool inRange(int r, int c)
	{
		return (0 <= r && r < N) && (0 <= c && c < N);
	}
	inline void bfs(const vector<vector<int>> &grid)
	{
		queue<pair<P, int>> nextP;
		vector<vector<bool>> visited(N, vector<bool>(N, false));

		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < N; ++c)
			{
				if (grid[r][c] == 1)
				{
					visited[r][c] = true;
					safeness[r][c] = 0;
					nextP.push(make_pair(make_pair(r, c), 0));
				}
			}
		}
		while (!nextP.empty())
		{
			int curR, curC, nextCost, nextR, nextC;
			curR = nextP.front().first.first;
			curC = nextP.front().first.second;
			nextCost = nextP.front().second + 1;
			nextP.pop();
			for (int i = 0; i < 4; ++i)
			{
				nextR = curR + dir[i][0];
				nextC = curC + dir[i][1];

				if (inRange(nextR, nextC) && visited[nextR][nextC] == false && safeness[nextR][nextC] > nextCost)
				{
					visited[nextR][nextC] = true;
					safeness[nextR][nextC] = nextCost;
					nextP.push(make_pair(make_pair(nextR, nextC), nextCost));
				}
			}
		}
	}
	bool findPath(const int &minLimit) // recurse
	{
		queue<P> nextP;
		vector<vector<bool>> visited(N, vector<bool>(N, false));

		if (minLimit <= safeness[0][0])
		{
			visited[0][0] = true;
			nextP.push(make_pair(0, 0));
		}
		while (!nextP.empty())
		{
			int r = nextP.front().first;
			int c = nextP.front().second;
			nextP.pop();
			for (int i = 0; i < 4; ++i)
			{
				int nextR = r + dir[i][0];
				int nextC = c + dir[i][1];
				if (inRange(nextR, nextC) && visited[nextR][nextC] == false && minLimit <= safeness[nextR][nextC])
				{
					visited[nextR][nextC] = true;
					nextP.push(make_pair(nextR, nextC));
				}
			}
		}
		return visited[N - 1][N - 1];
	}
	inline int binarySearchMaxSafeness(int high) // ( ], search max
	{
		int mid, low = -1;
		while (low != high)
		{
			mid = (high + low + 1) >> 1;
			if (findPath(mid))
				low = mid;
			else
				high = mid - 1;
		}
		return low;
	}

public:
	// solution method
	int maximumSafenessFactor(vector<vector<int>> &grid)
	{
		N = grid.size();
		safeness = vector<vector<int>>(N, vector<int>(N, 2e9));
		// step 1. evaluate safeness of each position
		bfs(grid);
		// step 2. binary search the route of maximum safeness
		return binarySearchMaxSafeness(800);
	}
};
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}

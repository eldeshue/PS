
/*

*/

#include <iostream>
#include <vector>

using namespace std;

/*
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
*/
#include <unordered_map>
#include <set>
class Solution
{
private:
	using Table = unordered_map<int, set<int>>;
	static constexpr int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // from north, clock wise

	int getDist(int x, int y)
	{
		return x * x + y * y;
	}

public:
	// solution method,
	// N : num command, M : num obstacle
	// O(N * M * log M)
	int robotSim(vector<int> &commands, vector<vector<int>> &obstacles)
	{
		Table xyObs, yxObs;
		int curX = 0, curY = 0, d = 0, maxDist = 0;

		// set table
		for (const auto &vec : obstacles)
		{
			int x = vec[0];
			int y = vec[1];
			xyObs[x].insert(y);
			yxObs[y].insert(x);
		}
		// simulate
		for (const int cmd : commands)
		{
			if (cmd < 0) // change direction
			{
				if (cmd == -1)
					d = (d + 1) % 4;
				else
					d = (d - 1 + 4) % 4;
			}
			else // move
			{
				int nextX = curX + dir[d][0] * cmd;
				int nextY = curY + dir[d][1] * cmd;
				// detact obstacle, using upper bound and lower bound
				if (curX == nextX && xyObs.find(curX) != xyObs.end()) // obstacle in x
				{
					const set<int> &curCol = xyObs[curX];
					if (d == 0) // curY < nextY
					{
						auto nearObsY = curCol.upper_bound(curY);
						if (nearObsY != curCol.end())
						{
							nextY = min(nextY, *nearObsY - 1);
						}
					}
					else if (d == 2) // curY > nextY
					{
						auto nearObsY = curCol.lower_bound(curY);
						if (nearObsY != curCol.begin())
						{
							nearObsY--;
							nextY = max(nextY, *nearObsY + 1);
						}
					}
				}
				else if (curY == nextY && yxObs.find(curY) != yxObs.end()) // obstacle in y
				{
					const set<int> &curRow = yxObs[curY];
					if (d == 1) // curX < nextX
					{
						auto nearObsX = curRow.upper_bound(curX);
						if (nearObsX != curRow.end())
						{
							nextX = min(nextX, *nearObsX - 1);
						}
					}
					else if (d == 3) // curX > nextX
					{
						auto nearObsX = curRow.lower_bound(curX);
						if (nearObsX != curRow.begin())
						{
							nearObsX--;
							nextX = max(nextX, *nearObsX + 1);
						}
					}
				}
				// move position
				curX = nextX;
				curY = nextY;
				maxDist = std::max(maxDist, getDist(curX, curY));
				std::cout << "debug : " << curX << ' ' << curY << '\n';
			}
		}
		return maxDist;
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

	Solution test;
	vector<int> cmd{2, -1, 8, -1, 6};
	vector<vector<int>> obs{{1, 5}, {-5, -5}, {0, 4}, {-1, -1}, {4, 5}, {-5, -3}, {-2, 1}, {-2, -5}, {0, 5}, {0, -1}};
	std::cout << test.robotSim(cmd, obs);
}

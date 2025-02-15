
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <queue>

class Solution
{
private:
	static constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	static constexpr int WATER = 0;
	static constexpr int LAND = 1;
	static constexpr int VISITED = 2;

	int bfs(vector<vector<int>>& grid, int y, int x)
	{
		int result = 0;
		queue<pair<int, int>> q;

		q.push(make_pair(y, x));
		while (!q.empty())
		{
			int curY = q.front().first;
			int curX = q.front().second;
			q.pop();
			for (int i = 0; i < 4; ++i)
			{
				const int nexY = curY + dir[i][0];
				const int nexX = curX + dir[i][1];
				if (0 <= nexY && nexY < grid.size()
					&& 0 <= nexX && nexX < grid[0].size()
					&& grid[nexY][nexX] == LAND)
				{
					grid[nexY][nexX] = VISITED;
					q.push(make_pair(nexY, nexX));
				}
				else if(0 <= nexY && nexY < grid.size()
					&& 0 <= nexX && nexX < grid[0].size()
					&& grid[nexY][nexX] == VISITED)
				{
					continue;
				}
				else
				{
					result++;
				}
			}
		}
		return result;
	}
public:
	// solution method
	int islandPerimeter(vector<vector<int>>& grid)
	{
		int result = 0;

		//bfs
		for (int r = 0; r < grid.size(); ++r)
		{
			for (int c = 0; c < grid[r].size(); ++c)
			{
				if (grid[r][c] == LAND)
				{
					grid[r][c] = VISITED;
					result += bfs(grid, r, c);
				}
			}
		}
		return result;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<vector<int>> g1 = { {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0} };
	Solution test;
	std::cout << test.islandPerimeter(g1);
}
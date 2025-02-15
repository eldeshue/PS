
#include <iostream>
#include <vector>

using namespace std;

// solution class
class Solution
{
private:
	static constexpr int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	static constexpr char SEA = '0';
	static constexpr char LAND = '1';
	static constexpr char VISITED = '2';
	void dfs(vector<vector<char>>& grid, int y, int x)
	{
		for (int i = 0; i < 4; ++i)
		{
			int nexY = y + dir[i][0];
			int nexX = x + dir[i][1];
			if (0 <= nexY && nexY < grid.size()
				&& 0 <= nexX && nexX < grid[0].size()
				&& grid[nexY][nexX] == LAND)
			{
				grid[nexY][nexX] = VISITED;
				dfs(grid, nexY, nexX);
			}
		}
	}
public:
	// solution method
	int numIslands(vector<vector<char>>& grid)
	{
		int result = 0;

		for (int r = 0; r < grid.size(); ++r)
		{
			for (int c = 0; c < grid[0].size(); ++c)
			{
				if (grid[r][c] == LAND)
				{
					result++;
					grid[r][c] = VISITED;
					dfs(grid, r, c);
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

	Solution test;

}
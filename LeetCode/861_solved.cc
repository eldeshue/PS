
#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	int matrixScore(vector<vector<int>> &grid)
	{
		const int maxRow = grid.size();
		const int maxCol = grid[0].size();
		vector<int> row(maxRow, 0);
		vector<int> col(maxCol, 0);
		for (int r = 0; r < maxRow; ++r)
		{
			for (int c = 0; c < maxCol; ++c)
			{
				if (grid[r][c])
					row[r] |= (1 << (maxCol - 1 - c));
			}
		}
		// greedy, flip row to make MSB to 1
		for (int r = 0; r < maxRow; ++r)
		{
			if (grid[r][0] == 0)
			{
				row[r] = ~row[r];
			}
		}
		for (int c = 0; c < maxCol; ++c)
		{
			for (int r = 0; r < maxRow; ++r)
			{
				if (row[r] & (1 << (maxCol - 1 - c)))
					col[c]++;
			}
		}
		// greedy, flip colum to make result maximum
		for (int c = 0; c < maxCol; ++c)
		{
			if (col[c] < (maxRow >> 1))
			{
				col[c] = maxRow - col[c];
			}
		}
		// calculate result
		int result = 0;
		for (int c = 0; c < maxCol; ++c)
		{
			result += col[c] * (1 << (maxCol - 1 - c));
		}
		return result;
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

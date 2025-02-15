
/*
	 DP, tabulation.

	 �κ��� row, ���� �κ� ��ġ ������ �κ� ��ġ�� �������� �ִ밪�� ������ DP.
	 ���� row�� ���� ��, ���� ��ġ�� ���� ���� �� �� �ִ� ���� ��, �ִ밪�� ã��.
	 
	 ��, �� �κ��� ��ġ�ų� �ϸ� �ȵ�(������ ������, �̵��� ����, ���� ó���� �ʿ���.)
*/
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <memory.h>

class Solution
{
private:
	int dir[3] = {-1, 0, 1};
	int cache[70][70][70];
public:
	// solution method
	int cherryPickup(vector<vector<int>>& grid)
	{
		memset(cache, -1, sizeof(cache));
		const int MaxRow = grid.size(), MaxCol = grid[0].size();
		cache[0][0][MaxCol - 1] = grid[0][0] + grid[0][MaxCol - 1];

		// tabulation
		for (int curRow = 1; curRow < MaxRow; ++curRow)
		{
			// col left
			for (int lCol = 0; lCol < MaxCol - 1; ++lCol)
			{
				// col right
				for (int rCol = lCol + 1; rCol < MaxCol; ++rCol)
				{
					// find maximum prev status
					int prevVal = -1;
					for (int i = 0; i < 3; ++i)
					{
						for (int j = 0; j < 3; ++j)
						{
							int prevLCol = lCol + dir[i];
							int prevRCol = rCol + dir[j];
							// exception handling
							// pick same cherry twice
							// out of range 
							if (prevLCol >= prevRCol
								|| prevLCol < 0 || MaxCol <= prevLCol 
								|| prevRCol < 0 || MaxCol <= prevRCol )
								continue;
							prevVal = std::max(prevVal, 
								cache[curRow - 1][prevLCol][prevRCol]);
						}
					}
					if (prevVal == -1)
						continue;
					cache[curRow][lCol][rCol] = prevVal
						+ grid[curRow][lCol] + grid[curRow][rCol];
				}
			}
		}
		// find max value
		int result = 0;
		for (int l = 0; l < MaxCol - 1; ++l)
		{
			for (int r = l + 1; r < MaxCol; ++r)
			{
				result = max(result, cache[MaxRow - 1][l][r]);
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

	Solution *pTest = new Solution;
	vector<vector<int>> grid1 =
	{
		{1,0,0,0,0,0,1},
		{2,0,0,0,0,3,0},
		{2,0,9,0,0,0,0},
		{0,3,0,5,4,0,0},
		{1,0,2,3,0,0,6}
	};
	cout << pTest->cherryPickup(grid1);
	delete pTest;
}


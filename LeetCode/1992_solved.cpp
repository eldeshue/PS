
#include <iostream>
#include <vector>

using namespace std;

// solution class

class Solution
{
private:
	int MaxRow, MaxCol;
	void eraseLand(vector<vector<int>>& land, vector<vector<int>>& result, int startR, int startC)
	{
		const int rIdx = result.size();
		result.push_back(vector<int>(4, 0));
		result[rIdx][0] = startR;
		result[rIdx][1] = startC;
		// get colum len
		int colLen = 0;
		while ((startC + colLen) < MaxCol && land[startR][startC + colLen])
		{
			colLen++;
		}
		// get row len
		int rowLen = 0;
		while ((startR + rowLen) < MaxRow && land[startR + rowLen][startC])
		{
			rowLen++;
		}
		// erase
		for (int r = 0; r < rowLen; ++r)
		{
			for (int c = 0; c < colLen; ++c)
			{
				land[r + startR][c + startC] = 0;
			}
		}
		result[rIdx][2] = startR + rowLen - 1;
		result[rIdx][3] = startC + colLen - 1;
	}
public:
	// solution method
	vector<vector<int>> findFarmland(vector<vector<int>>& land)
	{
		vector<vector<int>> result;

		MaxRow = land.size();
		MaxCol = land[0].size();
		for (int row = 0; row < MaxRow; ++row)
		{
			for (int col = 0; col < MaxCol; ++col)
			{
				if (land[row][col])
					eraseLand(land, result, row, col);
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
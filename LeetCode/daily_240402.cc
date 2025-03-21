
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

class Solution
{
private:
	static constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	bool dfs(vector<vector<char>>& b, const string& tgt, int idx, int x, int y)
	{
		bool result = false;
		if (idx == tgt.size())	// base case
		{
			return true;
		}
		for (int i = 0; i < 4; ++i)
		{
			const int nx = x + dir[i][0];
			const int ny = y + dir[i][1];
			if (0 <= nx && nx < b.size()
                && 0 <= ny && ny < b[idx].size()
				&& b[nx][ny] == tgt[idx])	// back tracking
			{
				char temp = b[nx][ny];
				b[nx][ny] = -1;
				result |= dfs(b, tgt, idx + 1, nx, ny);
				b[nx][ny] = temp;
			}
		}
		return result;
	}
public:
	bool exist(vector<vector<char>>& board, string word)
	{
		// find first
		for (int sx = 0; sx < board.size(); ++sx)
		{
			for (int sy = 0; sy < board[sx].size(); ++sy)
			{
				if (board[sx][sy] == word[0])
				{
					board[sx][sy] = -1;
					return dfs(board, word, 1, sx, sy);
				}
			}
		}
		// no first
		return false;
    }
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}


#include <iostream>
#include <string>
#include <memory.h>

int R, C;
const int dir[3] = {-1, 0, 1};
bool board[10000][500];

bool inRange(int y, int x)
{
	return 0 <= x && x < C && 0 <= y && y < R;
}

bool dfs(int y, int x)
{
	bool result = false;

	if (x == C - 1)
		return true;
	for (int i = 0; i < 3; ++i) // greedy
	{
		if (inRange(y + dir[i], x + 1) && !board[y + dir[i]][x + 1])
		{
			board[y + dir[i]][x + 1] = true;
			result = dfs(y + dir[i], x + 1);
			if (result == true) // greedy
				return result;
		}
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));

	// input
	std::string input;
	int result = 0;
	std::cin >> R >> C;
	for (int i = 0; i < R; ++i)
	{
		std::cin >> input;
		for (int j = 0; j < C; ++j)
		{
			if (input[j] == 'x')
			{
				board[i][j] = 1;
			}
		}
	}
	// paint board, max O(R*C)
	for (int r = 0; r < R; ++r)
	{
		result += dfs(r, 0);
	}
	// output
	std::cout << result;
}

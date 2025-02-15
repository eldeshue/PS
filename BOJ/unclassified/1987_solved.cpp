// BFS, but visited using set
// bitmasking, DFS
// 모든 원소가 대문자 알파뱃으로 구성되기 때문임.
#include <iostream>
#include <tuple>
#include <queue>

int row, col;
char board[21][21];

int DFS(int x, int y, int visited, int cnt)
{
	int result = 0;
	// up
	if (x > 1)
	{
		if ((visited & (1 << (board[x - 1][y] - 'A'))) == 0) // not included
		{
			result = std::max(result, 
				DFS(x - 1, y, visited | (1 << (board[x - 1][y] - 'A')), cnt + 1));
		}
	}
	// left
	if (y > 1)
	{
		if ((visited & (1 << (board[x][y - 1] - 'A'))) == 0) // not included
		{
			result = std::max(result, 
				DFS(x, y - 1, visited | (1 << (board[x][y - 1] - 'A')), cnt + 1));
		}
	}
	// down
	if (x < row)
	{
		if ((visited & (1 << (board[x + 1][y] - 'A'))) == 0) // not included
		{
			result = std::max(result, 
				DFS(x + 1, y, visited | (1 << (board[x + 1][y] - 'A')), cnt + 1));
		}
	}
	// right
	if (y < col)
	{
		if ((visited & (1 << (board[x][y + 1] - 'A'))) == 0) // not included
		{
			result = std::max(result, 
				DFS(x, y + 1, visited | (1 << (board[x][y + 1] - 'A')), cnt + 1));
		}
	}

	if (result == 0)
	{
		return cnt;
	}
	else
	{
		return result;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> row >> col;
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			std::cin >> board[i][j];
		}
	}

	int start = 0;
	start |= (1 << (board[1][1] - 'A'));
	std::cout << DFS(1, 1, start, 1);
}
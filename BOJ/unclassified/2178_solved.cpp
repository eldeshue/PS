
#include <iostream>
#include <memory.h>
#include <tuple>
#include <queue>

short int goalX, goalY;
bool board[100][100]; // x, y

short int BFS()
{
	std::queue<std::tuple<short int, short int, short int>> Q;
	Q.push(std::make_tuple(0, 0, 1));
	board[0][0] = false; // visited
	while (!Q.empty())
	{
		int x = std::get<0>(Q.front());
		int y = std::get<1>(Q.front());
		int cnt = std::get<2>(Q.front());
		Q.pop();
		if (x == goalX && y == goalY)
		{
			return cnt;
		}
		if (x != 0)
		{
			if (board[x - 1][y])
			{
				board[x - 1][y] = false;
				Q.push(std::make_tuple(x - 1, y, cnt + 1));
			}
		}
		if (y != 0)
		{
			if (board[x][y - 1])
			{
				board[x][y - 1] = false;
				Q.push(std::make_tuple(x, y - 1, cnt + 1));
			}
		}
		if (x != goalX)
		{
			if (board[x + 1][y])
			{
				board[x + 1][y] = false;
				Q.push(std::make_tuple(x + 1, y, cnt + 1));
			}
		}
		if (y != goalY)
		{
			if (board[x][y + 1])
			{
				board[x][y + 1] = false;
				Q.push(std::make_tuple(x, y + 1, cnt + 1));
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));

	char c;
	std::cin >> goalX >> goalY;
	for (int i = 0; i < goalX; ++i)
	{
		for (int j = 0; j < goalY; ++j)
		{
			std::cin >> c;
			board[i][j] = (c - '0');
		}
	}
	goalX --;
	goalY --;

	std::cout << BFS();
}


#include <iostream>
#include <tuple>
#include <queue>

int maxX, maxY, result = 2e9;
int board[1001][1001]; // 0 : available, 1 : blocked, 2 : visited

void BFS()
{
	// x, y, count, isBreak
	std::queue<std::tuple<int, int, int, bool>> Q;
	board[1][1] = 2;
	Q.push(std::make_tuple(1, 1, 1, false));
	while (!Q.empty())
	{
		int x = std::get<0>(Q.front());
		int y = std::get<1>(Q.front());
		int curCnt = std::get<2>(Q.front());
		bool isBreak = std::get<3>(Q.front());
		Q.pop();
		//
		if (x == maxX && y == maxY)
		{
			result = std::min(result, curCnt);
		}
		// up
		if (x > 1)
		{
			if (board[x - 1][y] == 1 && !isBreak) // º®À» ¶Õ´Â´Ù.
			{
				Q.push(std::make_tuple(x - 1, y, curCnt + 1, true));
			}
			else if (board[x - 1][y] == 0) // ±×³É ºó °ø°£
			{
				board[x - 1][y] = 2;
				Q.push(std::make_tuple(x - 1, y, curCnt + 1, isBreak));
			}
		}
		// left
		if (y > 1)
		{
			if (board[x][y - 1] == 1 && !isBreak) // º®À» ¶Õ´Â´Ù.
			{
				Q.push(std::make_tuple(x, y - 1, curCnt + 1, true));
			}
			else if (board[x][y - 1] == 0) // ±×³É ºó °ø°£
			{
				board[x][y - 1] = 2;
				Q.push(std::make_tuple(x, y - 1, curCnt + 1, isBreak));
			}
		}
		// down
		if (x < maxX)
		{
			if (board[x + 1][y] == 1 && !isBreak) // º®À» ¶Õ´Â´Ù.
			{
				Q.push(std::make_tuple(x + 1, y, curCnt + 1, true));
			}
			else if (board[x + 1][y] == 0) // ±×³É ºó °ø°£
			{
				board[x + 1][y] = 2;
				Q.push(std::make_tuple(x + 1, y, curCnt + 1, isBreak));
			}
		}
		// right
		if (y < maxY)
		{
			if (board[x][y + 1] == 1 && !isBreak) // º®À» ¶Õ´Â´Ù.
			{
				Q.push(std::make_tuple(x, y + 1, curCnt + 1, true));
			}
			else if (board[x][y + 1] == 0) // ±×³É ºó °ø°£
			{
				board[x][y + 1] = 2;
				Q.push(std::make_tuple(x, y + 1, curCnt + 1, isBreak));
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char temp;
	std::cin >> maxX >> maxY;
	for (int i = 1; i <= maxX; ++i)
	{
		for (int j = 1; j <= maxY; ++j)
		{
			std::cin >> temp;
			board[i][j] = temp - '0';
		}
	}

	BFS();
	if (result == 2e9)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << result;
	}
}


#include <iostream>
#include <memory.h>

int N, target;
int board[999][999];

void recurse_pos(int val, int len, int &x, int &y)
{
	if (len == 1)
		return ;
	else if (((len * len) >= val) && (val > ((len - 2) * (len - 2))))
	{
		for (int i = 0; i < len - 1; ++i)
		{
			if (board[y][x] == val)
				return;
			else
				y++;
		}
		for (int i = 0; i < len - 1; ++i)
		{
			if (board[y][x] == val)
				return;
			else
				x++;
		}
		for (int i = 0; i < len - 1; ++i)
		{
			if (board[y][x] == val)
				return;
			else
				y--;
		}
		for (int i = 0; i < len - 1; ++i)
		{
			if (board[y][x] == val)
				return;
			else
				x--;
		}
	}
	else
		return recurse_pos(val, len - 2, ++x, ++y);
}

void recurse_paint(int start, int len)
{
	if (len == 1)
	{
		board[start][start] = 1;
		return;
	}
	int x = start, y = start;
	int val = len * len;
	for (int i = 0; i < len - 1; ++i)
		board[y++][x] = val--;
	for (int i = 0; i < len - 1; ++i)
		board[y][x++] = val--;
	for (int i = 0; i < len - 1; ++i)
		board[y--][x] = val--;
	for (int i = 0; i < len - 1; ++i)
		board[y][x--] = val--;
	return recurse_paint(start + 1, len - 2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));

	int x = 0, y = 0;
	std::cin >> N >> target;
	recurse_paint(0, N);
	recurse_pos(target, N, x, y);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << y + 1 << ' ' << x + 1 << '\n';
}

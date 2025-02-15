#include <iostream>
#include <memory.h>

int N;
int board[101][101];
int cache[101][101];		// length

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));
	memset(board, 0, sizeof(board));

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> board[i][j];
		}
	}
	for (int y = 1; y <= N; ++y)	// N ^ 3
	{
		for (int x = 1; x <= N; ++x)
		{
			//
			int last_y = 0, last_x = 0, local_max_len = 0;
			for (int i = 1; i < y; ++i)
			{
				if (local_max_len < cache[i][x])
				{
					local_max_len = cache[i][x];
					last_y = i;
					last_x = x;
				}
			}
			for (int i = 1; i < x; ++i)
			{
				if (local_max_len < cache[y][i])
				{
					local_max_len = cache[y][i];
					last_y = y;
					last_x = i;
				}
			}
			if (board[last_y][last_x] < board[y][x])
			{
				cache[y][x] = local_max_len + 1;
			}
			else
			{
				cache[y][x] = local_max_len;
			}
		}
	}
	std::cout << cache[N][N];
}
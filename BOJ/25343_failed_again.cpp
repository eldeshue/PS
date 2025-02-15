
#include <iostream>
#include <memory.h>

int board[101][101];	// last val of the lis
int lenCache[101][101];	// length of the lis

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));
	memset(lenCache, 0, sizeof(lenCache));

	int N;
	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> board[i][j];
		}
	}
	for (int cur_y = 1; cur_y <= N; ++cur_y)
	{
		for (int cur_x = 1; cur_x <= N; ++cur_x)
		{
			int max_len = 0;
			for (int y = 0; y <= cur_y; ++y)
			{
				for (int x = 0; x <= cur_x; ++x)
				{
					if (board[y][x] < board[cur_y][cur_x] 
						&& max_len < lenCache[y][x]
						&& !(x == cur_x && y == cur_y))
					{
						max_len = lenCache[y][x];
					}
				}
			}
			lenCache[cur_y][cur_x] = max_len + 1;
		}
	}
	std::cout << lenCache[N][N];
}
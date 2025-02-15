
#include <iostream>
#include <string>
#include <memory.h>

int R, C, K, cnt = 0;
char board[5][5];
int dir[8] = { -1, 0, 1, 0, 0, -1, 0, 1 };

bool in_range(int y, int x)
{
	return (0 <= y && y < R && 0 <= x && x < C);
}

void back_track(int cur_y, int cur_x, int cur_level)
{
	if (cur_level == K)
	{
		if (cur_y == 0 && cur_x == C - 1)
			cnt++;
		board[cur_y][cur_x] = '.';
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		int next_y = cur_y + dir[2 * i];
		int next_x = cur_x + dir[2 * i + 1];
		if (in_range(next_y, next_x) && board[next_y][next_x] != 'T')
		{
			board[next_y][next_x] = 'T';
			back_track(next_y, next_x, cur_level + 1);
		}
	}
	board[cur_y][cur_x] = '.';
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::cin >> R >> C >> K;
	for (int i = 0; i < R; ++i)
	{
		std::cin >> input;
		for (int j = 0; j < C; ++j)
		{
			board[i][j] = input[j];
		}
	}
	// back tracking
	board[R - 1][0] = 'T';
	back_track(R - 1, 0, 1);
	std::cout << cnt;
}

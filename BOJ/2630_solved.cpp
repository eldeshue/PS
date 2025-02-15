#include <iostream>

constexpr bool blue = 1;
constexpr bool white = 0;
int N, blue_cnt = 0, white_cnt = 0;
bool board[1 << 7][1 << 7];

void count_cut_paper(int sx, int sy, int len)
{
	// check board.
	bool is_single_color = true;
	bool color = board[sy][sx];
	for (int idx = 0; idx < len * len; ++idx)
	{
		int y = sy + idx / len;
		int x = sx + idx % len;
		if (board[y][x] != color)
		{
			is_single_color = false;
			break;
		}
	}
	if (is_single_color)
	{
		if (color == blue)
			blue_cnt++;
		else
			white_cnt++;
		return;
	}
	else // divide
	{
		int next_len = len / 2;
		count_cut_paper(sx, sy, next_len);
		count_cut_paper(sx + next_len, sy, next_len);
		count_cut_paper(sx, sy + next_len, next_len);
		count_cut_paper(sx + next_len, sy + next_len, next_len);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> board[i][j];
		}
	}
	count_cut_paper(0, 0, N);
	std::cout << white_cnt << '\n' << blue_cnt;
}
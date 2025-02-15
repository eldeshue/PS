
#include <iostream>
#include <string>
#include <memory.h>

int N, M;
int	board[1001][1001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));

	std::string tmp;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> tmp;
		for (int j = 1; j <= M; ++j)
		{
			board[i][j] = tmp[j - 1] - '0';
		}
	}
	int max_len = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			if (board[i][j] != 0)
			{
				int cur_min = board[i - 1][j - 1];
				cur_min = std::min(cur_min, board[i - 1][j]);
				cur_min = std::min(cur_min, board[i][j - 1]);
				board[i][j] = cur_min + 1;
				max_len = std::max(max_len, board[i][j]);
			}
		}
	}
	std::cout << max_len * max_len << "\n";
}
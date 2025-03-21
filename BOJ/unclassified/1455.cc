
#include <iostream>
#include <vector>

int main()
{
	int N, M;	// row, colum
	std::cin >> N >> M;
	std::vector<std::vector<int>> board(N + 1, std::vector<int>(M + 1, 0));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			// 1 or 0
			// all zero wanted
			char c;
			std::cin >> c;
			board[i][j] = c - '0';
		}
	}

	int totalFlipCount = 0;
	for (int r = N - 1; r >= 0; --r)
	{
		for (int c = M - 1; c >= 0; --c)
		{
			// if the value is not zero, flip
			// zero, odd
			// one, even
			int localFlipCount = board[r + 1][c] + board[r + 1][c + 1] + board[r][c + 1];
			if ((!board[r][c] && (localFlipCount & 1))
				|| (board[r][c] && !(localFlipCount & 1)))
			{
				totalFlipCount++;
				board[r][c] = localFlipCount + 1;
			}
			else
			{
				board[r][c] = localFlipCount;
			}
		}
	}
	std::cout << totalFlipCount;
}

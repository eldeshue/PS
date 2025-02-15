
#include <iostream>
#include <vector>

constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int memoize(const std::vector<std::vector<int>> &board,
			std::vector<std::vector<int>> &cache, int r, int c)
{
	if (cache[r][c] != -1) // cache hit
	{
		return cache[r][c];
	}
	else // cache miss
	{
		int result = 0;
		for (int i = 0; i < 4; ++i)
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (0 <= nr && nr < board.size() && 0 <= nc && nc < board.size() && board[r][c] > board[nr][nc]) // in range
			{
				result = std::max(result, memoize(board, cache, nr, nc));
			}
		}
		return cache[r][c] = result + 1;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
	std::vector<std::vector<int>> cache(N, std::vector<int>(N, -1));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			std::cin >> board[r][c];
		}
	}
	int result = 0;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			result = std::max(result, memoize(board, cache, r, c));
		}
	}
	std::cout << result;
}

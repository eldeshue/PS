
#include <iostream>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<std::vector<int>> board(N, std::vector<int>(N));
	std::vector<std::vector<int>> cache(N, std::vector<int>(N, 0));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			std::cin >> board[r][c];
		}
	}
	// search and update
	int result = 0;
	for (int curRow = 0; curRow < N; ++curRow)
	{
		for (int curCol = 0; curCol < N; ++curCol)
		{
			for (int r = 0; r <= curRow; ++r)
			{
				for (int c = 0; c <= curCol; ++c)
				{
					if (board[curRow][curCol] > board[r][c] && cache[curRow][curCol] < cache[r][c])
					{
						cache[curRow][curCol] = cache[r][c];
					}
				}
			}
			cache[curRow][curCol]++;
			result = std::max(result, cache[curRow][curCol]);
		}
	}

	std::cout << result;
}


#include <iostream>
#include <memory.h>

int N;
int board[2][100000];
int cache[2][100000];

bool is_in_range(int col)
{
	return (0 <= col && col < N);
}

int DP(int col)
{
	if (!is_in_range(col))
	{
		return 0;
	}
	else if (cache[0][col] != -1 || cache[1][col] != -1)
	{
		return std::max(cache[0][col], cache[1][col]);
	}
	else
	{
		cache[0][col] = DP(col - 2) + board[0][col];
		cache[1][col] = DP(col - 2) + board[1][col];
		DP(col - 1);
		cache[0][col] = std::max(cache[0][col], cache[1][col - 1] + board[0][col]);
		cache[1][col] = std::max(cache[1][col], cache[0][col - 1] + board[1][col]);
		return std::max(cache[0][col], cache[1][col]);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num_test;
	std::cin >> num_test;
	for (int i = 0; i < num_test; ++i)
	{
		memset(cache, -1, sizeof(cache));
		std::cin >> N;
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < N; ++k)
			{
				std::cin >> board[j][k];
			}
		}
		std::cout << DP(N - 1) << '\n';
	}
}
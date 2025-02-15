
#include <iostream>
#include <string>

int N, M;
int board[50][50];

bool is_in_range(int y, int x, int len)
{
	return ((y + len - 1) < N && (x + len - 1) < M);
}

bool is_ok(int y, int x, int len)
{
	return (board[y][x] == board[y + len - 1][x]) && (board[y][x] == board[y][x + len - 1])
		&& (board[y][x] == board[y + len - 1][x + len - 1]);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int max_len;
	std::string input;
	std::cin >> N >> M;
	max_len = 1;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		for (int j = 0; j < M; ++j)
		{
			board[i][j] = input[j];
		}
	}
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			int cur_len = max_len + 1;
			while (is_in_range(i, j, cur_len))
			{
				if (is_ok(i, j, cur_len))
				{
					max_len = cur_len;
				}
				cur_len++;
			}
		}
	}
	std::cout << max_len * max_len;
}
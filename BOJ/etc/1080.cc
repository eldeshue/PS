
#include <iostream>
#include <string>

int N, M;
bool status[50][50];
bool goal[50][50];

void flip(int y, int x)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			status[y + i][x + j] = !(status[y + i][x + j]);
		}
	}
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // input
  std::string input;
  std::cin >> N >> M;
  for (int i = 0; i < N; ++i)
  {
	std::cin >> input;
	for (int j = 0; j < M; ++j)
	{
		status[i][j] = input[j] - '0';
	}
  }
  for (int i = 0; i < N; ++i)
  {
	std::cin >> input;
	for (int j = 0; j < M; ++j)
	{
		goal[i][j] = input[j] - '0';
	}
  }
  // solve
  int result = 0;
  if (N < 3 || M < 3)
  {
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (status[i][j] != goal[i][j])
			{
				std::cout << -1;
				return 0;
			}
		}
	}
	std::cout << result;
	return 0;
  }
  for (int y = 0; y < N - 2; ++y)
  {
	for (int x = 0; x < M - 2; ++x)
	{
		if (status[y][x] != goal[y][x])	// flip or not
		{
			flip(y, x);
			++result;
		}
	}
	if ((status[y][M - 2] != goal[y][M-2])
		|| (status[y][M - 1] != goal[y][M - 1]))
	{
		std::cout << -1;
		return 0;
	}
  }
  for (int x = 0; x < M; ++x)
  {
	if ((status[N - 2][x] != goal[N-2][x])
		|| (status[N - 1][x] != goal[N - 1][x]))
	{
		std::cout << -1;
		return 0;
	}
  }
  std::cout << result;
}

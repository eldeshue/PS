
#include <iostream>
#include <vector>

int Y, X;
constexpr int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int dfs(std::vector<std::vector<int>>& b, int y, int x)
{
	int cnt = 0;

	for (int i = 0; i < 4; ++i)
	{
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];
		if ( 0 <= ny && ny < Y
			&& 0 <= nx && nx < X
			&& b[ny][nx] == true)
		{
			b[ny][nx] = false;
			cnt += dfs(b, ny, nx);
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> Y >> X;
	std::vector<std::vector<int>> board(Y, std::vector<int>(X, false));
	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
		{
			std::cin >> board[y][x];
		}
	}

	int cntPicture = 0;
	int maxSizePicture = 0;
	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
		{
			if (board[y][x] == true)
			{
				cntPicture++;
				board[y][x] = false;
				maxSizePicture = std::max(maxSizePicture, 
				1 +	dfs(board, y, x));
			}
		}
	}
	std::cout << cntPicture << '\n' << maxSizePicture;
}
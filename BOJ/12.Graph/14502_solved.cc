
#include <iostream>
#include <queue>
#include <vector>

using P = std::pair<int, int>; // row , colum
constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::queue<P> q;

	// input
	int N, M, emptySpaceCnt = -3;
	std::cin >> N >> M;
	std::vector<std::vector<int>> board(N, std::vector<int>(M));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			std::cin >> board[r][c];
			if (!board[r][c])
				emptySpaceCnt++;
			else if (board[r][c] == 2)
				q.push(std::make_pair(r, c));
		}
	}
	// search, brute force
	int result = 0;
	for (int i = 0; i < N * M - 2; ++i)
	{
		int w1r = i / M, w1c = i % M;
		if (board[w1r][w1c] == 0)
		{
			board[w1r][w1c] = 1;
			for (int j = i + 1; j < N * M - 1; ++j)
			{
				int w2r = j / M, w2c = j % M;
				if (board[w2r][w2c] == 0)
				{
					board[w2r][w2c] = 1;
					for (int k = j + 1; k < N * M; ++k)
					{
						int w3r = k / M, w3c = k % M;
						if (board[w3r][w3c] == 0)
						{
							board[w3r][w3c] = 1;
							// bfs
							result = std::max(result, [=]() mutable -> int
											  {
								while (!q.empty())
								{
									auto [curRow, curCol] = q.front();
									q.pop();
									for (int idx = 0; idx < 4; ++idx)
									{
										int nextRow = curRow + dir[idx][0];
										int nextCol = curCol + dir[idx][1];
										if ( [&N, &M](int r, int c) -> bool
											{ return (0 <= r) && (r < N) && (0 <= c) && (c <= M); }(nextRow, nextCol)
										&& board[nextRow][nextCol] == 0)
										{
											board[nextRow][nextCol] = 1;
											q.push(std::make_pair(nextRow, nextCol));
											emptySpaceCnt--;
										}
									}
								}
								return emptySpaceCnt; }());
							board[w3r][w3c] = 0;
						}
					}
					board[w2r][w2c] = 0;
				}
			}
			board[w1r][w1c] = 0;
		}
	}
	std::cout << result;
}

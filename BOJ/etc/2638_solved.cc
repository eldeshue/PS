
#include <iostream>
#include <vector>
#include <queue>

constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs(std::vector<std::vector<int>> &board,
		 std::queue<std::pair<int, int>> &startQ,
		 std::queue<std::pair<int, int>> &resultQ)
{
	while (!startQ.empty())
	{
		int r = startQ.front().first;
		int c = startQ.front().second;
		startQ.pop();
		for (int i = 0; i < 4; ++i)
		{
			int nr = r + dir[i][0];
			int nc = c + dir[i][1];
			if (0 <= nr && nr < board.size() && 0 <= nc && nc < board[0].size())
			{
				if (board[nr][nc] > 0)
				{
					board[nr][nc]--;
					if (board[nr][nc] == 0)
					{
						resultQ.push(std::make_pair(nr, nc));
						board[nr][nc] = -1;
					}
				}
				else if (board[nr][nc] == 0)
				{
					board[nr][nc] = -1;
					startQ.push(std::make_pair(nr, nc));
				}
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, input;
	std::cin >> N >> M;
	std::vector<std::vector<int>> board(N, std::vector<int>(M, 0));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			std::cin >> input;
			if (input == 1)
			{
				board[r][c] = 2;
			}
		}
	}
	int result = 0;
	std::queue<std::pair<int, int>> q1;
	std::queue<std::pair<int, int>> q2;
	std::queue<std::pair<int, int>> &sq = q1;
	std::queue<std::pair<int, int>> &rq = q2;
	board[0][0] = -1;
	sq.push(std::make_pair(0, 0));
	while (!sq.empty())
	{
		bfs(board, sq, rq);
		std::swap(sq, rq);
		result++;
		// debug
		std::cout << '\n';
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				std::cout << board[i][j] << ' ';
			}
			std::cout << '\n';
		}
		//
	}
	std::cout << result - 1;
}

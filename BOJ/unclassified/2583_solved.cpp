
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int M, N, K;
	std::cin >> N >> M >> K;
	std::vector<std::vector<bool>> board(N, std::vector<bool>(M, false));
	for (int i = 0; i < K; ++i)
	{
		int lc, lr, rc, rr;
		std::cin >> lc >> lr >> rc >> rr;
		for (int r = lr; r < rr; ++r)
		{
			for (int c = lc; c < rc; ++c)
			{
				board[r][c] = true;
			}
		}
	}

	// bfs
	constexpr int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	auto bfs = [&board, &dir, N, M](int sR, int sC) -> int
		{
			std::queue<pii> q;
			int cnt = 1;

			board[sR][sC] = true;
			q.push(std::make_pair(sR, sC));
			while (!q.empty())
			{
				const auto [curRow, curCol] = q.front();
				q.pop();
				for (int d = 0; d < 4; ++d)
				{
					int nextRow = curRow + dir[d][0];
					int nextCol = curCol + dir[d][1];
					if (((0 <= nextRow && nextRow < N)
						&& (0 <= nextCol && nextCol < M))
						&& board[nextRow][nextCol] == false)
					{
						cnt++;
						board[nextRow][nextCol] = true;
						q.push(std::make_pair(nextRow, nextCol));
					}
				}
			}
			return cnt;
		};

	// paint
	std::vector<int> result;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			if (!board[r][c])
			{
				result.push_back(bfs(r, c));
			}
		}
	}
	// print
	std::sort(result.begin(), result.end());
	std::cout << result.size() << '\n';
	for (const int n : result)
	{
		std::cout << n << ' ';
	}
}

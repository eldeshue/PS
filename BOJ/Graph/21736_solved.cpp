/*
	BOJ 21736

	심플한 bfs 보드 탐색 문제
*/
#include <iostream>
#include <vector>
#include <deque>

using pii = std::pair<int, int>;
pii dir[4] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };	// y, x

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, sy, sx;
	std::cin >> N >> M;
	std::vector<std::vector<char>> board(N, std::vector<char>(M, 0));
	auto in_range = [&](int const y, int const x) {
		return 0 <= y && y < N && 0 <= x && x < M;
		};

	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			std::cin >> board[r][c];
			if (board[r][c] == 'I')
			{
				sy = r;
				sx = c;
			}
		}
	}

	// bfs
	std::deque<pii> q;
	int cnt = 0;
	q.push_back(pii(sy, sx));
	board[sy][sx] = 'X';
	while (!q.empty())
	{
		auto const [cy, cx] = q.front();
		q.pop_front();

		for (int d = 0; d < 4; ++d)
		{
			int const ny = cy + dir[d].first;
			int const nx = cx + dir[d].second;
			if (in_range(ny, nx) && board[ny][nx] != 'X')
			{
				cnt += (board[ny][nx] == 'P');
				q.push_back(pii(ny, nx));
				board[ny][nx] = 'X';
			}
		}
	}

	// print
	if (cnt == 0)
	{
		std::cout << "TT";
	}
	else
	{
		std::cout << cnt;
	}
}

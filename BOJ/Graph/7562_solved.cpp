
#include <functional>
#include <iostream>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;
	constexpr const int dir[8][2] = {
		{1, 2},
		{2, 1},
		{-1, 2},
		{2, -1},
		{1, -2},
		{-2, 1},
		{-1, -2},
		{-2, -1}
	};

	int num_test;
	std::cin >> num_test;
	while (num_test--)
	{
		int N, start_x, start_y, goal_x, goal_y;
		std::cin >> N >> start_x >> start_y >> goal_x >> goal_y;

		auto inRange = [&](int x, int y) {
			return (((0 <= x) && (x < N)) && ((0 <= y) && (y < N)));
			};

		std::queue<pii> q;
		std::vector<std::vector<int>> board(N, std::vector<int>(N, -1));
		board[start_x][start_y] = 0;
		q.push(std::make_pair(start_x, start_y));
		while (!q.empty())
		{
			if (board[goal_x][goal_y] != -1)
				break;
			const auto [cur_x, cur_y] = q.front();
			q.pop();
			for (int i = 0; i < 8; ++i)
			{
				int const next_x = cur_x + dir[i][0];
				int const next_y = cur_y + dir[i][1];
				if (inRange(next_x, next_y) && board[next_x][next_y] == -1)
				{
					board[next_x][next_y] = board[cur_x][cur_y] + 1;
					q.push(std::make_pair(next_x, next_y));
				}
			}
		}
		std::cout << board[goal_x][goal_y] << '\n';
	}
}
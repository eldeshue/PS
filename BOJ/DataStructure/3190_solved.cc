
/*
	평범한 구현문제. 다른게 아니라 음수의 나머지 연산에서 실수함.
*/
#include <iostream>
#include <vector>
#include <deque>

using pii = std::pair<int, int>;
using pic = std::pair<int, char>;
#define APPLE 1
#define SNAKE 2

constexpr int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, L;
	std::cin >> N >> K;
	std::vector<std::vector<int>> board(N + 1, std::vector<int>(N + 1, 0));
	for (int i = 0; i < K; ++i)
	{
		int r, c;
		std::cin >> r >> c;
		board[r][c] = APPLE;
	}
	std::cin >> L;
	std::deque<pic> schedule(L, {0, ' '});
	for (int i = 0; i < L; ++i)
	{
		std::cin >> schedule[i].first >> schedule[i].second;
	}

	// simulate
	std::deque<pii> snake;
	snake.push_back({1, 1});
	board[1][1] = SNAKE;
	int time = 0;
	int curDir = EAST;
	while (true)
	{
		bool isApple = false;
		// update time
		time++;
		// move head
		int nextR = snake.back().first + dir[curDir][0];
		int nextC = snake.back().second + dir[curDir][1];
		// collision check
		if (![&]() -> bool
						  { return 0 < nextR && nextR <= N && 0 < nextC && nextC <= N; }() || board[nextR][nextC] == SNAKE)
		{
			break; // game over
		}
		else if (board[nextR][nextC] == APPLE)
		{
			isApple = true;
		}
		board[nextR][nextC] = SNAKE;
		snake.push_back(std::make_pair(nextR, nextC));

		// move tail
		if (!isApple)
		{
			const auto &[tailR, tailC] = snake.front();
			board[tailR][tailC] = 0;
			snake.pop_front();
		}
		// change direction
		if (time == schedule.front().first)
		{
			if (schedule.front().second == 'D')
				curDir = (curDir + 1) % 4;
			else
				curDir = (curDir + 3) % 4;
			schedule.pop_front();
		}
	}
	std::cout << time;
}

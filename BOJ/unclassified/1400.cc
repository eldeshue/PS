#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
using Stat = std::tuple<int, int, int, int>;	// cost, dir, row, col

struct I
{
	bool isVertical;
	int hTime, vTime;
	I(bool t, int h, int v) : isVertical(t), hTime(h), vTime(v) {};
	int operator()(int curTime, int enterDir)	// wait intersection
	{

	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while (true)
	{
		// input
		std::priority_queue<Stat, std::vector<Stat>, std::greater<Stat>> pq;
		int m, n, numInter = 0, gR = 0, gC = 0;
		std::cin >> m >> n;
		if (m == 0 && n == 0)
			return 0;
		std::vector<std::vector<char>> board(m, std::vector<char>(n));
		std::vector<std::vector<int>> arriveTime(m, std::vector<int>(n, 2e9));
		for (int r = 0; r < m; ++r)
		{
			for (int c = 0; c < n; ++c)
			{
				std::cin >> board[r][c];
				if ('0' <= board[r][c] && board[r][c] <= '9')
					numInter = std::max(numInter, board[r][c] - '0');
				else if (board[r][c] == 'A')
				{
					arriveTime[r][c] = 0;
					pq.push(std::make_tuple(0, 0, r, c));
				}
				else if (board[r][c] == 'B')
					gR = r; gC = c;
			}
		}
		std::vector<I> intersec;
		for (int i = 0; i < numInter; ++i)
		{
			char idx, type;
			int h, v;
			std::cin >> idx >> type >> h >> v;
			intersec.push_back(I((type == '|'), h, v));
		}

		// dijkstra
		while (!pq.empty())
		{

		}

		if (arriveTime[gR][gC] == 2e9)
			std::cout << "impossible\n";
		else
			std::cout << arriveTime[gR][gC] << '\n';
	}
}

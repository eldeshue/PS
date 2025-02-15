
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>

constexpr int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
using Stat = std::tuple<int, int, int>;	// cost, dir, row, col

struct I
{
	bool isVertical;
	int hTime, vTime;
	I(bool t, int h, int v) : isVertical(t), hTime(h), vTime(v) {};
	int operator()(int curTime, int dir)	// wait intersection
	{
		int mod = curTime % (hTime + vTime);
		if (mod == 0)
			mod = hTime + vTime;
		if (isVertical)	// vertical sign first
		{
			if (~dir & 1)	// vertical entry
			{
				if (mod <= vTime)
					return curTime;
				else
					return curTime - mod + (hTime + vTime + 1);
			}
			else	// horizontal entry
			{
				if (mod <= vTime)	// avoid vertical
					return curTime - mod + vTime + 1;
				else
					return curTime;
			}
		}
		else	// horizontal sign first
		{
			if (~dir & 1)	// vertical entry
			{
				if (mod <= hTime)
					return curTime - mod + hTime + 1;
				else
					return curTime;
			}
			else	// horizontal entry
			{
				if (mod <= hTime)
					return curTime;
				else
					return curTime - mod + (hTime + vTime + 1);
			}
		}
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
		int m, n, numInter = -1, gR = 0, gC = 0;
		std::cin >> m >> n;
		if (m == 0 && n == 0)
			return 0;
		std::vector<std::string> board(m);
		std::vector<std::vector<int>> arriveTime(m, std::vector<int>(n, 2e9));
		for (int r = 0; r < m; ++r)
		{
			std::cin >> board[r];
			for (int c = 0; c < n; ++c)
			{
				if ('0' <= board[r][c] && board[r][c] <= '9')
					numInter = std::max(numInter, board[r][c] - '0');
				else if (board[r][c] == 'A')
				{
					arriveTime[r][c] = 0;
					pq.push(std::make_tuple(0, r, c));
				}
				else if (board[r][c] == 'B')
				{
					gR = r; gC = c;
				}
			}
		}
		std::vector<I> intersec;
		for (int i = 0; i <= numInter; ++i)
		{
			char idx, type;
			int h, v;
			std::cin >> idx >> type >> h >> v;
			intersec.push_back(I((type == '|'), h, v));
		}

		// dijkstra
		while (!pq.empty())
		{
			auto [curTime, curRow, curCol] = pq.top();
			pq.pop();
			for (int d = 0; d < 4; ++d)
			{
				// if intersection, wait
				int nextTime = curTime + 1;
				int nextRow = curRow + dir[d][0];
				int nextCol = curCol + dir[d][1];
				if (nextRow < 0 || nextRow >= m ||
					nextCol < 0 || nextCol >= n
					|| board[nextRow][nextCol] == '.')
					continue;
				if ('0' <= board[nextRow][nextCol]
					&& board[nextRow][nextCol] <= '9')
				{
					nextTime = intersec[board[nextRow][nextCol] - '0'](nextTime, d);
				}

				// update
				if (nextTime >= arriveTime[nextRow][nextCol])
					continue;
				arriveTime[nextRow][nextCol] = nextTime;
				pq.push(std::make_tuple(nextTime, nextRow, nextCol));
			}
		}

		if (arriveTime[gR][gC] == 2e9)
			std::cout << "impossible\n";
		else
			std::cout << arriveTime[gR][gC] << '\n';
	}
}
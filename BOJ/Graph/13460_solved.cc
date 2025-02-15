
#include <iostream>
#include <bit>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <tuple>

using RBPos = std::tuple<int, int, int, int>;
using Boundary = std::tuple<int, int, int, int>;
using stat = std::pair<RBPos, int>;

template <>
struct std::hash<RBPos>
{
	std::size_t operator()(const RBPos &rb) const noexcept
	{
		return std::rotl(std::hash<int>{}(std::get<0>(rb)), 1) ^ std::rotl(std::hash<int>{}(std::get<1>(rb)), 2) ^ std::rotl(std::hash<int>{}(std::get<2>(rb)), 3) ^ std::rotl(std::hash<int>{}(std::get<3>(rb)), 4);
	}
};

class Solution
{
private:
	int maxRow, maxCol;
	int cry, crx, cby, cbx, curDepth;
	int nry, nrx, nby, nbx;
	std::vector<std::string> &board;
	std::vector<std::vector<Boundary>> bop;
	// red only goes to the whole
	// O(1)
	void moveRBVertical(bool isUp)
	{
		nrx = crx;
		nbx = cbx;
		// direction?
		if (isUp)
		{
			// which ball should be moved first?
			nry = std::get<0>(bop[cry][crx]);
			nby = std::get<0>(bop[cby][cbx]);
			// handling overlap
			if ((nry == nby) && (nrx == nbx) && board[nry][nrx] != 'O')
			{
				if (cry < cby) // Red move first
				{
					nby++;
				}
				else // blue move first
				{
					nry++;
				}
			}
		}
		else // move down
		{
			nry = std::get<1>(bop[cry][crx]);
			nby = std::get<1>(bop[cby][cbx]);
			if ((nry == nby) && (nrx == nbx) && board[nry][nrx] != 'O')
			{
				if (cry > cby) // Red move first
				{
					nby--;
				}
				else // blue move first
				{
					nry--;
				}
			}
		}
	}
	void moveRBHorizontal(bool isLeft)
	{
		nry = cry;
		nby = cby;
		// direction?
		if (isLeft)
		{
			// which ball should be moved first?
			nrx = std::get<2>(bop[cry][crx]);
			nbx = std::get<2>(bop[cby][cbx]);
			// handling overlap
			if ((nry == nby) && (nrx == nbx) && board[nry][nrx] != 'O')
			{
				if (crx < cbx) // Red move first
				{
					nbx++;
				}
				else // blue move first
				{
					nrx++;
				}
			}
		}
		else // move down
		{
			nrx = std::get<3>(bop[cry][crx]);
			nbx = std::get<3>(bop[cby][cbx]);
			if ((nry == nby) && (nrx == nbx) && board[nry][nrx] != 'O')
			{
				if (crx > cbx) // Red move first
				{
					nbx--;
				}
				else // blue move first
				{
					nrx--;
				}
			}
		}
	}

public:
	// O(m * n)
	Solution(int n, int m, std::vector<std::string> &b) : maxRow(n), maxCol(m), board(b), bop(n, std::vector<Boundary>(m, {0, 0, 0, 0}))
	{
		for (int y = 0; y < n; ++y)
		{
			for (int x = 0; x < m; ++x)
			{
				if (board[y][x] == 'R')
				{
					cry = y;
					crx = x;
					board[y][x] = '.';
				}
				else if (board[y][x] == 'B')
				{
					cby = y;
					cbx = x;
					board[y][x] = '.';
				}
			}
		}
		// fill bop, boundary of each position
		// up(y small), down(y big), left(x small), right(x big)
		int limit;
		for (int x = 0; x < m; ++x)
		{
			for (int y = 0; y < n; ++y)
			{
				if (board[y][x] == '#')
					limit = y + 1;
				else if (board[y][x] == 'O')
					limit = y;
				std::get<0>(bop[y][x]) = limit;
			}
		}
		for (int x = 0; x < m; ++x)
		{
			for (int y = n - 1; y >= 0; --y)
			{
				if (board[y][x] == '#')
					limit = y - 1;
				else if (board[y][x] == 'O')
					limit = y;
				std::get<1>(bop[y][x]) = limit;
			}
		}
		for (int y = 0; y < n; ++y)
		{
			for (int x = 0; x < m; ++x)
			{
				if (board[y][x] == '#')
					limit = x + 1;
				else if (board[y][x] == 'O')
					limit = x;
				std::get<2>(bop[y][x]) = limit;
			}
		}
		for (int y = 0; y < n; ++y)
		{
			for (int x = m - 1; x >= 0; --x)
			{
				if (board[y][x] == '#')
					limit = x - 1;
				else if (board[y][x] == 'O')
					limit = x;
				std::get<3>(bop[y][x]) = limit;
			}
		}
	}
	int solve() // O(n * m)
	{
		std::queue<stat> q;
		std::unordered_set<RBPos> visited;

		visited.insert(std::tie(cry, crx, cby, cbx));
		q.push(std::make_pair(std::tie(cry, crx, cby, cbx), 0));
		while (!q.empty())
		{
			std::tie(cry, crx, cby, cbx) = q.front().first;
			curDepth = q.front().second;
			q.pop();
			if ((board[cry][crx] == 'O') && (board[cby][cbx] != 'O')) // check solution
			{
				return curDepth;
			}
			else if (curDepth < 10 && (board[cby][cbx] != 'O')) // next move
			{
				// up
				moveRBVertical(true);
				if (visited.find(std::tie(nry, nrx, nby, nbx)) == visited.end())
				{
					visited.insert(std::tie(nry, nrx, nby, nbx));
					q.push(make_pair(std::tie(nry, nrx, nby, nbx), curDepth + 1));
				}
				// down
				moveRBVertical(false);
				if (visited.find(std::tie(nry, nrx, nby, nbx)) == visited.end())
				{
					visited.insert(std::tie(nry, nrx, nby, nbx));
					q.push(make_pair(std::tie(nry, nrx, nby, nbx), curDepth + 1));
				}
				// left
				moveRBHorizontal(true);
				if (visited.find(std::tie(nry, nrx, nby, nbx)) == visited.end())
				{
					visited.insert(std::tie(nry, nrx, nby, nbx));
					q.push(make_pair(std::tie(nry, nrx, nby, nbx), curDepth + 1));
				}
				// right
				moveRBHorizontal(false);
				if (visited.find(std::tie(nry, nrx, nby, nbx)) == visited.end())
				{
					visited.insert(std::tie(nry, nrx, nby, nbx));
					q.push(make_pair(std::tie(nry, nrx, nby, nbx), curDepth + 1));
				}
			}
		}
		return -1;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::string> board(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> board[i];
	}
	std::cout << Solution(N, M, board).solve();
}

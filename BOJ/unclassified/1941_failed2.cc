
#include <iostream>
#include <unordered_set>
#include <tuple>
#include <queue>

using status = std::tuple<int, int, int>;	// status, prevPos, depth

int board = 0;
constexpr int dir[4] = {-5, -1, 1, 5};
std::unordered_set<int> visited;

inline bool in_range(int curPos, int dir)
{
	int y = curPos / 5;
	int x = curPos % 5;
	if (dir == 5)
		return (y < 4);
	else if (dir == -5)
		return (y > 0);
	else if (dir == 1)
		return (x < 4);
	else if (dir == -1)
		return (x > 0);
	return false;
}

bool is_ok(const int val)
{
	// number of S
	int cnt = 0;
	for (int i = 0; i < 25; ++i)
		cnt += (board >> i) & (val >> i) & 1;
	return (cnt >= 4);
}

void print_board(int val)
{
	std::cout << "============\n";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << ((val >> (5 * i + j)) & 1);
		}
		std::cout << '\n';
	}
	std::cout << "============\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::queue<status> Q;

	// input
	char c;
	for (int i = 0; i < 25; ++i)
	{
		std::cin >> c;
		if (c == 'S')
		{
			board |= (1 << i);
			visited.insert(1 << i);
			Q.push(std::make_tuple((1 << i), (1 << i), 1));
		}
	}
	// bfs
	int result = 0;
	while (!Q.empty())
	{
		const int curStat = std::get<0>(Q.front());
		const int curPos = std::get<1>(Q.front());
		const int curDepth = std::get<2>(Q.front());
		Q.pop();
		if (curDepth == 7)
		{
			print_board(curStat);
			if (is_ok(curStat))
				result++;
			continue;
		}
		for (int i = 0; i < 4; ++i)
		{
			if (!in_range(curPos, dir[i]))
				continue;
			int nextPos = curPos + dir[i];
			int nextStat = curStat | (1 << nextPos);
			if (visited.find(nextStat) == visited.end())
			{
				visited.insert(nextStat);
				Q.push(std::make_tuple(nextStat, nextPos, curDepth + 1));
			}
		}
	}
	std::cout << result;
}

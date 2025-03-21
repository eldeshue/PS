
#include <iostream>
#include <queue>
#include <unordered_set>

int board = 0;
int result = 0;
constexpr int dir[4] = {-5, -1, 1, 5};

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
	std::unordered_set<int> visited;
	std::queue<int> Q;
	int tCnt = 0, sCnt = 0;

	// is all connected???
	for (int i = 0; i < 25; ++i)
	{
		if (val & (1 << i))
		{
			//bfs
			visited.insert(i);
			tCnt++;
			if (board & (1 << i))
				sCnt++;
			Q.push(i);
			while (!Q.empty())
			{
				int curPos = Q.front();
				Q.pop();
				for (int i = 0; i < 4; ++i)
				{
					int nextPos = curPos + dir[i];
					if (in_range(curPos, dir[i]) && (val & (1 << nextPos)) && visited.find(nextPos) == visited.end())
					{
						visited.insert(nextPos);
						tCnt++;
						if (board & (1 << nextPos))
							sCnt++;
						Q.push(nextPos);
					}
				}
			}
			return (tCnt == 7) && (4 <= sCnt);
		}
	}
	return false;
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

void count_combinaion(const int depth, const int start, int val)
{
	if (depth == 7)
	{
		if (is_ok(val))
		{
			// debug
			//print_board(val);
			//
			result++;
		}
		return ;
	}
	else
	{
		const int end = 25 - 7 + 1 + depth;
		for (int pos = start; pos < end; ++pos)
		{
			count_combinaion(depth + 1, pos + 1, val | (1 << pos));
		}
		return;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	char c;
	for (int i = 0; i < 25; ++i)
	{
		std::cin >> c;
		if (c == 'S')
			board |= (1 << i);
	}
	// each combination
	// 25C7
	count_combinaion(0, 0, 0);
	std::cout << result;
}

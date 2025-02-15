
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using node = std::pair<int, int>;

int N;
int board[25][25];
std::vector<int> result;
const std::vector<std::vector<int>> dir = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

inline bool inRange(int x, int y)
{
	return (0 <= x && x < N) && (0 <= y && y < N);
}

void bfs(int sx, int sy, int id)	// board[y][x];
{
	std::queue<node> Q;
	result.push_back(1);

	board[sy][sx] = id;
	Q.push(std::make_pair(sx, sy));
	while (!Q.empty())
	{
		const int x = Q.front().first;
		const int y = Q.front().second;
		Q.pop();
		for (int i = 0; i < 4; ++i)
		{
			const int nx = x + dir[i][0];
			const int ny = y + dir[i][1];
			if (inRange(nx, ny) && board[ny][nx] < 0)
			{
				board[ny][nx] = id;
				Q.push(std::make_pair(nx, ny));
				result[id - 1]++;
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char c;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> c;
			board[i][j] -= static_cast<int>(c - '0');
		}
	}
	// count
	int temp = 1;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (board[i][j] < 0)
			{
				bfs(j, i, temp);
				temp++;
			}
		}
	}
	//
	sort(result.begin(), result.end());
	std::cout << result.size() << '\n';
	for (const int& n : result)
	{
		std::cout << n << '\n';
	}
}
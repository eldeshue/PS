
#include <iostream>
#include <string>
#include <queue>
#include <tuple>
#include <memory.h>

using uint = unsigned int;
using node = std::tuple<int, int, uint, bool>;

int N, M;
bool board[1001][1001];
uint min_dist[2][1001][1001];
int four_way[4][2];

bool node_sanity(int y, int x)
{
	if (1 <= y && y <= N && 1 <= x && x <= M)
		return true;
	return false;
}

void BFS()
{
	std::queue<node> nnq;
	nnq.push(std::make_tuple(1, 1, 1, false));
	min_dist[0][1][1] = 1;

	while (!nnq.empty())
	{
		int cur_y = std::get<0>(nnq.front());
		int cur_x = std::get<1>(nnq.front());
		uint nex_d = std::get<2>(nnq.front()) + 1;
		bool cur_wall = std::get<3>(nnq.front());
		nnq.pop();
		for (int i = 0; i < 4; ++i)
		{
			int nex_y = cur_y + four_way[i][0];
			int nex_x = cur_x + four_way[i][1];
			if (node_sanity(nex_y, nex_x) && nex_d < min_dist[cur_wall][nex_y][nex_x])
			{
				if (board[nex_y][nex_x] == false)
				{
					min_dist[cur_wall][nex_y][nex_x] = nex_d;
					nnq.push(std::make_tuple(nex_y, nex_x, nex_d, cur_wall));
				}
				else if (cur_wall == false)
				{
					min_dist[true][nex_y][nex_x] = nex_d;
					nnq.push(std::make_tuple(nex_y, nex_x, nex_d, true));
				}
			}

		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(min_dist, -1, sizeof(min_dist));
	memset(four_way, 0, sizeof(four_way));
	four_way[0][1] = 1;
	four_way[1][0] = 1;
	four_way[2][1] = -1;
	four_way[3][0] = -1;

	std::string input;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> input;
		for (int j = 1; j <= M; ++j)
		{
			board[i][j] = input[j - 1] - '0';
		}
	}
	BFS();
	std::cout << static_cast<int>(std::min(min_dist[0][N][M], min_dist[1][N][M]));
}

// using Dijkstra algorithm(with priority queue)
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <memory.h>

typedef std::tuple<int, int, int> node;
int N, M;
unsigned int map[1000][1000];

struct cmp_node
{
	bool operator()(const node& n1, const node& n2)
	{
		return std::get<2>(n1) > std::get<2>(n2);
	}
};

void Dijkstra(int start_x, int start_y)
{
	std::priority_queue<node, std::vector<node>, cmp_node> PQ;
	PQ.push(std::make_tuple(start_x, start_y, 0));

	while (!PQ.empty())
	{
		int cur_x = std::get<0>(PQ.top());
		int cur_y = std::get<1>(PQ.top());
		int cur_cost = std::get<2>(PQ.top());
		PQ.pop();
		// coordinate sanity check
		if (cur_x < 0 || cur_y < 0 || cur_x >= M || cur_y >= N)
			continue;
		if (map[cur_y][cur_x] <= cur_cost)
			continue;
		map[cur_y][cur_x] = cur_cost;
		PQ.push(std::make_tuple(cur_x - 1, cur_y, cur_cost + 1));
		PQ.push(std::make_tuple(cur_x, cur_y - 1, cur_cost + 1));
		PQ.push(std::make_tuple(cur_x + 1, cur_y, cur_cost + 1));
		PQ.push(std::make_tuple(cur_x, cur_y + 1, cur_cost + 1));
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(map, -1, sizeof(map));

	int start_x = 0, start_y = 0;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			int input;
			std::cin >> input;
			if (input != 0)
			{
				if (input == 2)
				{
					start_y = i;
					start_x = j;
				}
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
	Dijkstra(start_x, start_y);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			std::cout << static_cast<int>(map[i][j]) << ' ';
		}
		std::cout << '\n';
	}
}

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <memory.h>

using node = std::tuple<int, int, int>;
unsigned int field[501][501];
unsigned int min_cost[501][501];

struct cmp_node
{
	bool operator()(const node& n1, const node& n2)
	{
		return std::get<2>(n1) > std::get<2>(n2);
	}
};

void Dijkstra()
{
	std::priority_queue<node, std::vector<node>, cmp_node> PQ;
	PQ.push(std::make_tuple(0, 0, 0));
	min_cost[0][0] = 0;

	while (!PQ.empty())
	{
		int cur_x = std::get<0>(PQ.top());
		int cur_y = std::get<1>(PQ.top());
		int cur_cost = std::get<2>(PQ.top());
		PQ.pop();

		// up
		if (cur_y - 1 >= 0&& field[cur_y - 1][cur_x] != (unsigned int)(-1))
		{
			if (min_cost[cur_y - 1][cur_x] > cur_cost + field[cur_y - 1][cur_x])
			{
				min_cost[cur_y - 1][cur_x] = cur_cost + field[cur_y - 1][cur_x];
				PQ.push(std::make_tuple(cur_x, cur_y - 1, min_cost[cur_y - 1][cur_x]));
			}
		}
		// down
		if (cur_y + 1 <= 500 && field[cur_y + 1][cur_x] != (unsigned int)(-1))
		{
			if (min_cost[cur_y + 1][cur_x] > cur_cost + field[cur_y + 1][cur_x])
			{
				min_cost[cur_y + 1][cur_x] = cur_cost + field[cur_y + 1][cur_x];
				PQ.push(std::make_tuple(cur_x, cur_y + 1, min_cost[cur_y + 1][cur_x]));
			}
		}
		// left
		if (cur_x - 1 >= 0 && field[cur_y][cur_x - 1] != (unsigned int)(-1))
		{
			if (min_cost[cur_y][cur_x - 1] > cur_cost + field[cur_y][cur_x - 1])
			{
				min_cost[cur_y][cur_x - 1] = cur_cost + field[cur_y][cur_x - 1];
				PQ.push(std::make_tuple(cur_x - 1, cur_y, min_cost[cur_y][cur_x - 1]));
			}
		}
		// right
		if (cur_x + 1 <= 500 && field[cur_y][cur_x + 1] != (unsigned int)(-1))
		{
			if (min_cost[cur_y][cur_x + 1] > cur_cost + field[cur_y][cur_x + 1])
			{
				min_cost[cur_y][cur_x + 1] = cur_cost + field[cur_y][cur_x + 1];
				PQ.push(std::make_tuple(cur_x + 1, cur_y, min_cost[cur_y][cur_x + 1]));
			}
		}
	}
}

void set_field(int mx, int my, int Mx, int My, unsigned int val)
{
	for (int y = my; y <= My; ++y)
	{
		for (int x = mx; x <= Mx; ++x)
		{
			field[y][x] = val;
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(field, 0, sizeof(field));
	memset(min_cost, -1, sizeof(min_cost));

	// set field
	int N, M;
	int x1, x2, y1, y2;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> x1 >> y1 >> x2 >> y2;
		set_field(std::min(x1, x2), std::min(y1, y2), 
			std::max(x1, x2), std::max(y1, y2), 1);
	}
	std::cin >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> x1 >> y1 >> x2 >> y2;
		set_field(std::min(x1, x2), std::min(y1, y2), 
			std::max(x1, x2), std::max(y1, y2), (unsigned int)(-1));
	}
	// Dijkstra
	Dijkstra();
	std::cout << (int)min_cost[500][500];
}
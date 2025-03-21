#include <iostream>
#include <vector>
#include <memory.h>

int N;
using edge = std::pair<int, int>;
using uint = unsigned int;
std::vector<edge> edges[16];
unsigned int cache[16][1 << 16];

// tabulation.
void DFS(uint cur_node, uint cur_status)
{
	for (const auto& adj_edge : edges[cur_node])
	{
		uint next_node = adj_edge.first;
		uint next_cost = adj_edge.second + cache[cur_node][cur_status];
		uint next_status = cur_status | (1 << next_node);
		if ((cur_status & (1 << next_node)) == 0
			&& cache[next_node][next_status] > next_cost) // if not visited
		{
			cache[next_node][next_status] = next_cost;
			DFS(next_node,next_status);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	uint input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> input;
			if (input != 0)
			{
				edges[i].push_back(std::make_pair(j, input));
			}
		}
	}
	// 시작은 무조건 0번 노드에서.... 마지막도 무조건 1번 노드.
	DFS(0, 0);
	//
	std::cout << cache[0][(1 << N) - 1];
}


#include <iostream>
#include <vector>
#include <memory.h>

using uint = unsigned int;

std::vector<int> graph[1000001];
uint cache[1000001][2];	// 0: 본인이 일반 노드, 1: 본인이 어댑터 / 값으로는 본인 포함 최소개수

void DP(int parent_node, int cur_node)
{
	if (graph[cur_node].empty())
	{
		// base case
		//cache[cur_node][0] = 0;
		cache[cur_node][1] = 1;
		return ;
	}
	else
	{
		// cache miss
		for (const int child_node : graph[cur_node])
		{
			if (child_node != parent_node)
			{
				DP(cur_node, child_node);
				cache[cur_node][0] += cache[child_node][1];
				cache[cur_node][1] += std::min(cache[child_node][0],
									cache[child_node][1]);
			}
		}
		cache[cur_node][1]++;
		return ;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	int num_node, node1, node2;
	std::cin >> num_node;
	for (int i = 0; i < num_node - 1; ++i)
	{
		std::cin >> node1 >> node2;
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}
	DP(0, 1);
	std::cout << std::min(cache[1][0], cache[1][1]);
}

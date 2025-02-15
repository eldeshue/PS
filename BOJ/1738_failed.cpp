
#include <iostream>
#include <memory.h>
#include <deque>
#include <tuple>

int		edges[20000][3];
bool	is_visited[101];
int		max_cost[101];
int		max_copied[101];
int		back_route[101];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(is_visited, 0, sizeof((is_visited)));

	int num_node, num_edge;
	std::cin >> num_node >> num_edge;
	for (int i = 0; i < num_edge; ++i)
	{
		std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
	}

	is_visited[1] = true;
	for (int i = 0; i < num_node - 1; ++i)
	{
		for (int cur_edge = 0; cur_edge < num_edge; ++cur_edge)
		{
			int& start_node = edges[cur_edge][0];
			int& end_node = edges[cur_edge][1];
			int cost = max_cost[start_node] + edges[cur_edge][2];
			if (is_visited[start_node] && max_cost[end_node] < cost)
			{
				is_visited[end_node] = true;
				back_route[end_node] = start_node;
				max_cost[end_node] = cost;
				max_copied[end_node] = cost;
			}
		}
	}
	for (int cur_edge = 0; cur_edge < num_edge; ++cur_edge)
	{
		int& start_node = edges[cur_edge][0];
		int& end_node = edges[cur_edge][1];
		int cost = max_cost[start_node] + edges[cur_edge][2];
		if (is_visited[start_node] && max_cost[end_node] < cost)
		{
			is_visited[end_node] = true;
			max_cost[end_node] = cost;
		}
	}
	if (max_copied[num_node] < max_cost[num_node])
	{
		std::cout << -1;
		return 0;
	}
	// output
	std::deque<int> output;
	output.push_back(num_node);
	while (output.back() != 1)
	{
		output.push_back(back_route[output.back()]);
	}
	while (!output.empty())
	{
		std::cout << output.back() << ' ';
		output.pop_back();
	}
}


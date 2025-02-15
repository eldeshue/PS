// 1865. ��Ȧ
// �ش� ������ ���� ���� �˰����� ����Ͽ� �־��� �׷����� ���� ����Ŭ�� �߻��ϴ��� ���θ� Ȯ��.
// �ش� ������ ���ǻ����� ������� ��õ��� �ʾҴٴ� ��.
// �� Ư�� ������� 0���� �ΰ� �� ������ ���� �ִܰŸ��� ���ϴ°� �ƴ϶�, ���� �߻� ���ɼ��� üũ
#include <iostream>
#include <memory.h>
#include <vector>
#include <tuple>

using edge = std::tuple<int, int, int>;

// bool is_reachable[501]; // ������ ���� ������, �ʿ���.
int min_cost[501];
std::vector<edge> edges;

void set_init_status()
{
	for (int i = 1; i <= 500; ++i)
		min_cost[i] = 5000001; // �������� ���� ���尡 �ƴϱ⿡ maximum������ �ʱ�ȭ���� ����.
	// memset(is_reachable, 0, sizeof(is_reachable));
	edges.clear();
}

bool Bellman_Ford(int node_num)
{
	/*
	// start node
	int start_node = std::get<0>(edges[0]);
	min_cost[start_node] = 0;
	is_reachable[start_node] = true;
	*/
	// traversal graph
	for (int i = 0; i < node_num - 1; ++i)
	{
		for (const auto& cur_edge : edges)
		{
			int cur_start = std::get<0>(cur_edge);
			int cur_end = std::get<1>(cur_edge);
			int cur_cost = min_cost[cur_start] + std::get<2>(cur_edge);
			if (/*is_reachable[cur_start] && */ cur_cost < min_cost[cur_end])
			{
				//is_reachable[cur_end] = true;
				min_cost[cur_end] = cur_cost;
			}
		}
	}
	// identify negative cycle
	for (const auto& cur_edge : edges)
	{
		int cur_start = std::get<0>(cur_edge);
		int cur_end = std::get<1>(cur_edge);
		int cur_cost = min_cost[cur_start] + std::get<2>(cur_edge);
		// if there is an update, the graph has a negative cycle
		if (cur_cost < min_cost[cur_end])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int test_num, node_num, pos_edge_num, neg_edge_num;
	int start, end, cost;
	std::cin >> test_num;
	for (int i = 0; i < test_num; ++i)
	{
		// set initial status
		set_init_status();
		// input
		std::cin >> node_num >> pos_edge_num >> neg_edge_num;
		for (int j = 0; j < pos_edge_num; ++j)
		{
			std::cin >> start >> end >> cost;
			edges.push_back(std::make_tuple(start, end, cost));
			edges.push_back(std::make_tuple(end, start, cost));
		}
		for (int j = 0; j < neg_edge_num; ++j)
		{
			std::cin >> start >> end >> cost;
			edges.push_back(std::make_tuple(start, end, -cost));
		}
		if (Bellman_Ford(node_num))	// Bellman_Ford() return true if there is no negative cycle
		{
			std::cout << "NO\n";
		}
		else
		{
			std::cout << "YES\n";
		}
	}
}
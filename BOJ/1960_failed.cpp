
/*
	BOJ 1960, ��� ����� - �������, ����

	< �ִ� ���� Ǯ�� >
	�� row�� col�� ���� ������
	source�� row�� ����ǰ�, sink�� col�� ����ȴ�.
	�̵� �� ������ capacity�� �� ���̴�.

	row�� col�� ���̴� ���� ���� �׷���, �� row�� ��� col�� ����ǰ�, �� �ݴ뵵 ��������.
	�̵� ������ capacity�� 1�̴�.

	�ִ� ���� Ž���� ������ ��, row�� col ������ ������ Ȯ���ϸ� ����� ���� �� �ִ�.

	< �׸��� Ǯ�� >
	�켱 ���� ť�� Ȱ��, ���� ���� �뷮�� ���� ��带 �켱���� ä���.
	
*/

#include <iostream>
#include <queue>
#include <memory.h>

constexpr int SRC = 0;
constexpr int MAX_NODE = 1002;

int capacity[MAX_NODE][MAX_NODE];
int flow[MAX_NODE][MAX_NODE];

int BFS(const int SNK)
{
	int parent[MAX_NODE];
	int cur_node;
	std::queue<int> Q;

	memset(parent, -1, sizeof(parent));
	Q.push(SRC);
	while (!Q.empty())
	{
		cur_node = Q.front();
		Q.pop();
		if (cur_node == SNK)
			break;
		for (int next_node = 0; next_node <= SNK; ++next_node)
		{
			if (parent[next_node] == -1 
				&& capacity[cur_node][next_node] > flow[cur_node][next_node])
			{
				parent[next_node] = cur_node;
				Q.push(next_node);
			}
		}
	}
	// traverse aug-path
	// find aug flow, minimum value 
	if (parent[SNK] == -1)
		return 0;
	int aug_flow = 2e9;
	for (cur_node = SNK; cur_node != SRC; cur_node = parent[cur_node])
		aug_flow = std::min(aug_flow,
			capacity[parent[cur_node]][cur_node] - flow[parent[cur_node]][cur_node]);
	// increase the flow
	for (cur_node = SNK; cur_node != SRC; cur_node = parent[cur_node])
	{
		flow[parent[cur_node]][cur_node] += aug_flow;
		flow[cur_node][parent[cur_node]] -= aug_flow;
	}
	return aug_flow;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));

	// input
	int N, SNK, max_flow = 0;
	std::cin >> N;
	SNK = 2 * N + 1;
	for (int r = 1; r <= N; ++r)	// row
	{
		std::cin >> capacity[SRC][r];
		max_flow += capacity[SRC][r];
	}
	for (int c = N + 1; c <= 2 * N; ++c)	// col
		std::cin >> capacity[c][SNK];
	// graph build
	// row : 1 ~ N
	// col : N + 1 ~ 2 * N 
	for (int r = 1; r <= N; ++r)	// row
	{
		for (int c = N + 1; c <= 2 * N; ++c)	// col
		{
			capacity[r][c] = 1;
		}
	}
	// max flow, edmonds-karp
	int total_flow = 0;
	while (true)
	{
		// BFS, find aug-path 
		int prev_total_flow = total_flow;
		total_flow += BFS(SNK);
		if (prev_total_flow == total_flow)
		{
			break;
		}
	}
	if (total_flow != max_flow)
	{
		std::cout << -1;
		return 0;
	}
	// result
	std::cout << 1 << '\n';
	for (int r = 1; r <= N; ++r)	// row
	{
		for (int c = N + 1; c <= 2 * N; ++c)	// col
		{
			std::cout << flow[r][c];
		}
		std::cout << '\n';
	}
}


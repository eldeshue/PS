
// 8086 �ִ� ���� �˰��� ����. ������� ī�� �˰���
// ���� ������ �� ������ ���� ��θ� Ž���ϰ�, �ش� ����� �ִ� �������� ��θ� ä���.
// �̷��� ��ε��� �ݺ��ؼ� ã�ư��鼭 ������ ��δ� ������ ä���, 
// ���� ���� ��ΰ� ���� �� ���� Ž��(BFS)�� �ݺ��Ѵ�.

// ���� ǮĿ�� �˰����� ��̴� ��θ� �����ϴ� ���� �ִ�.
// �̴� ��� �뷮�� 0�� ������ �������� ����� ����ȴ�. 
// �� ������ �������� �����ϸ鼭 ������ �߸��� ��θ� �����, �ٸ� ���⿡�� ������ ä���� �� �ִ�.
// https://velog.io/@kasterra/%EC%9C%A0%EB%9F%89-%EA%B7%B8%EB%9E%98%ED%94%84-%ED%8F%AC%EB%93%9C-%ED%92%80%EC%BB%A4%EC%8A%A8-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98

// ����� ������ ����� �����̶� �� ������ �Ϲ������� ���������� �ʴ�.
// �� �� �� ������ �ʿ䰡 �ִ�.

/*
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

constexpr int NODE_NUM = 52;
using uint = unsigned int;
int capacity[NODE_NUM][NODE_NUM];
int flow[NODE_NUM][NODE_NUM];

int map_node(char c)
{
	if ('A' <= c && c <= 'Z')
		return static_cast<int>(c - 'A');
	else if ('a' <= c && c <= 'z')
		return static_cast<int>(c - 'a' + 26);
}

uint BFS(uint start, uint end)
{
	uint prev_node[NODE_NUM];
	memset(prev_node, -1, sizeof(prev_node));
	std::queue<int> Q;
	Q.push(start);

	uint cur_node;
	while (!Q.empty())
	{
		cur_node = Q.front();
		Q.pop();
		if (cur_node == end)
			break;
		for (int next_node = 0; next_node < 52; ++next_node)
		{
			// ���� ����� Ž��
			// BFS�� ���� �̴����̸�, ���ÿ� ������ ���ɼ��� �ִ�(�� �뷮�� ����) ������ �߰�
			// ������ �����̾ �� �� ����(���� �̹� ���� ���̸� ���� ��).
			if (capacity[cur_node][next_node] - flow[cur_node][next_node] > 0 &&
				prev_node[next_node] == -1)
			{
				Q.push(next_node);
				prev_node[next_node] = cur_node;
			}
		}
	}
	// trace back the route
	// Ž���� ���� ��ΰ� sink�� �������� ���ߴ� -> sink�� ���ϴ� ������δ� ����.
	if (prev_node[end] == -1) return 0;	// no aug route, edmond carp done.
	int aug_flow = 2e9;
	cur_node = end;
	for (cur_node = end; cur_node != start; cur_node = prev_node[cur_node])
	{
	// increasing flow
		aug_flow = std::min(aug_flow, 
			capacity[prev_node[cur_node]][cur_node] - flow[prev_node[cur_node]][cur_node]);
	}
	// ������ ����(aug flow)��ŭ�� ��ο� �ݿ���.
	// ������ ��ο��ٸ�, �̴� �ܼ��� Ȯ���̾���.
	// ������ ��ο��ٸ�, �̴� �Ϻθ�ŭ�� �ٸ� ��η� ����, �� �޸� �기 ����.
	for (cur_node = end; cur_node != start; cur_node = prev_node[cur_node])
	{
		flow[prev_node[cur_node]][cur_node] += aug_flow;	// forward flow
		flow[cur_node][prev_node[cur_node]] -= aug_flow;	// reverse flow
	}
	return aug_flow;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	// taking input
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));
	uint num_edge, total_flow = 0;
	std::cin >> num_edge;
	for (int i = 0; i < num_edge; ++i)
	{
		char from, to;
		uint node1, node2, cap;
		std::cin >> from >> to >> cap;
		node1 = map_node(from);
		node2 = map_node(to);
		capacity[node1][node2] += cap;
		capacity[node2][node1] += cap;	// ������ ������̶� �ݴ뵵 �����ش�.
	}
	// Edmond Karp algorithm
	while (true)
	{
		uint prev_flow = total_flow;
		total_flow += BFS(0, 25);	// source is 'A', sink is 'Z'
		if (prev_flow == total_flow)
			break;
	}
	// result
	std::cout << total_flow;
}
*/
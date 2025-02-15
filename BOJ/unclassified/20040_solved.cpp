// union find 응용문제
// 이미 union한 원소와 union하면 cycle을 이룸.
#include <iostream>
#include <memory.h>

int find(int target_index);
void Union(int node1, int node2);
int parent[500000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(parent, -1, sizeof(parent));

	int N, M, n1, n2;
	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i)
	{
		std::cin >> n1 >> n2;
		if (find(n1) == find(n2))
		{
			std::cout << i;
			return 0;
		}
		else
		{
			Union(n1, n2);
		}
	}
	std::cout << "0";
	return 0;
}

int find(int target_index)
{
	if (parent[target_index] < 0)
	{	// 크기가 1이고, 부모이므로, 자기 자신 하나
		return target_index;
	}
	else
	{
		int p = find(parent[target_index]); // recursively
		parent[target_index] = p;
		return p;
	}
}

void Union(int node1, int node2)
{
	node1 = find(node1);
	node2 = find(node2);

	if (node1 == node2)	// 이미 같은 부모임
	{
		return;
	}

	// 둘의 부모가 다르다
	// 두 노드 모두 부모를 찾았으므로, parent값이 음수임
	// 크기가 작은 트리가 크기가 큰 트리의 밑으로 들어가야 함.
	// 즉 보다 작은 쪽을 부모로
	if (parent[node1] < parent[node2])
	{
		parent[node1] += parent[node2];
		parent[node2] = node1;
	}
	else
	{
		parent[node2] += parent[node1];
		parent[node1] = node2;
	}
}


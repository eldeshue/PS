// union find ���빮��
// �̹� union�� ���ҿ� union�ϸ� cycle�� �̷�.
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
	{	// ũ�Ⱑ 1�̰�, �θ��̹Ƿ�, �ڱ� �ڽ� �ϳ�
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

	if (node1 == node2)	// �̹� ���� �θ���
	{
		return;
	}

	// ���� �θ� �ٸ���
	// �� ��� ��� �θ� ã�����Ƿ�, parent���� ������
	// ũ�Ⱑ ���� Ʈ���� ũ�Ⱑ ū Ʈ���� ������ ���� ��.
	// �� ���� ���� ���� �θ��
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


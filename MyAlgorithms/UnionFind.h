#pragma once

#include <vector>
#include <algorithm>

class UnionFind
{
private:
	int numGroup;
	mutable std::vector<int> parent;

public:
	UnionFind(int size) : parent(size, -1), numGroup(size) {};
	int getGroupNum() const { return numGroup; }
	int getMaxGroupSize() const
	{
		int result = 0;
		std::for_each(parent.begin(), parent.end(), [&](const int& val) -> void
			{if (val < 0) { result = std::max(result, std::abs(val)); } });
		return result;
	};
	int find(int node) const // pass compression, is it const?
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	bool isSameGroup(int node1, int node2) const // ???
	{
		node1 = find(node1);
		node2 = find(node2);
		return node1 == node2;
	}
	void unite(int node1, int node2) // unite by rank
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] >= parent[node2]) // node2's rank is higher
		{
			if (parent[node1] == parent[node2])	// same rank
			{
				parent[node1]--;	// rank increase
			}
			parent[node1] = node2;
		}
		else // node1's rank is higher than node2's rank
		{
			parent[node2] = node1;
		}
		numGroup--;
		return;
	}
};

/*

// weighted Union Find
// �迭�� ���� ������ ���, �θ���. ������ ����
// ����̸� �ڽ��̰�, �θ� ����Ŵ.
// ���� �⺻�����δ� -1 ���� �ʱ�ȭ �Ұ�
int Find(int* const parent, const int size, int target_index)
{
	if (target_index >= size)
	{
		return -1;
	}
	else if (parent[target_index] < 0)
	{	// ũ�Ⱑ 1�̰�, �θ��̹Ƿ�, �ڱ� �ڽ� �ϳ�
		return target_index;
	}
	else
	{
		int p = Find(parent, size, parent[target_index]); // recursively
		parent[target_index] = p;
		return p;
	}
}

void Union(int* const parent, const int size, int node1, int node2)
{
	node1 = Find(parent, size, node1);
	node2 = Find(parent, size, node2);

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

// no argument version.

int Find(int target_index);
void Union(int node1, int node2);

//

int Find(int target_index)
{
	if (parent[target_index] < 0)
	{
		return target_index;
	}
	else
	{
		int p = Find(parent[target_index]);
		parent[target_index] = p;
		return p;
	}
}

void Union( int node1, int node2)
{
	node1 = Find(node1);
	node2 = Find(node2);

	if (node1 == node2)
	{
		return;
	}

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

*/

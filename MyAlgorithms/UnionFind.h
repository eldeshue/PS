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
	void unite(int node1, int node2) // unite by size
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] > parent[node2]) // node2's size is bigger
		{
			parent[node2] += parent[node1];
			parent[node1] = node2;
		}
		else // node1's size is bigger or same
		{
			parent[node1] += parent[node2];
			parent[node2] = node1;
		}
		numGroup--;
		return;
	}
};

/*

// weighted Union Find
// 배열의 값이 음수인 경우, 부모임. 절댓값은 개수 
// 양수이면 자식이고, 부모를 가리킴.
// 따라서 기본적으로는 -1 으로 초기화 할것
int Find(int* const parent, const int size, int target_index)
{
	if (target_index >= size)
	{
		return -1;
	}
	else if (parent[target_index] < 0)
	{	// 크기가 1이고, 부모이므로, 자기 자신 하나
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

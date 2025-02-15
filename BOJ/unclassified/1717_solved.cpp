#include <iostream>
#include <memory.h>

int find(int* const parent, const int size, int target_index);
void Union(int* const parent, const int size, int node1, int node2);

int n, m;
int arr[1000001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arr, -1, sizeof(arr));

	bool isFind;
	int a, b;
	std::cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> isFind >> a >> b;
		if (isFind)
		{
			if (find(arr, n + 1, a) == find(arr, n + 1, b))
			{
				std::cout << "YES\n";
			}
			else
			{
				std::cout << "NO\n";
			}
		}
		else
		{
			Union(arr, n + 1, a, b);
		}
	}
}

int find(int* const parent, const int size, int target_index)
{
	if (target_index >= size)
	{
		return -1;
	}
	else if (parent[target_index] < 0)
	{
		return target_index;
	}
	else
	{
		int p = find(parent, size, parent[target_index]); // recursively
		parent[target_index] = p;
		return p;
	}
}

void Union(int* const parent, const int size, int node1, int node2)
{
	node1 = find(parent, size, node1);
	node2 = find(parent, size, node2);

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

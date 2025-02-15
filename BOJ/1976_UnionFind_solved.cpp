
#include <iostream>
#include <memory.h>

int find(int* const parent, const int size, int target_index);
void Union(int* const parent, const int size, int node1, int node2);
int N, M;
int cities[201];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cities, -1, sizeof(cities));

	bool isConnected;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> isConnected;
			if (isConnected)
			{
				Union(cities, N + 1, i, j);
			}
		}
	}
	int prev, cur;
	std::cin >> prev;
	for (int i = 0; i < M - 1; ++i)
	{
		std::cin >> cur;
		//
		if (find(cities, N + 1, prev) != find(cities, N + 1, cur))
		{
			std::cout << "NO";
			return 0;
		}
		//
		prev = cur;
	}
	std::cout << "YES";
	return 0;
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


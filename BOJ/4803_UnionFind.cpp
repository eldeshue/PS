// using union find
#include <iostream>
#include <memory.h>

int find(int target_index);
void Union(int node1, int node2);

int N, M;
int parent[501];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n1, n2, caseNum = 1;
	while (true)
	{
		memset(parent, -1, sizeof(parent));
		std::cin >> N >> M;

		if (N == M && N == 0)
		{
			break;
		}

		for (int i = 0; i < M; ++i)
		{
			std::cin >> n1 >> n2;
			Union(n1, n2);
		}

		int result = 0;
		for(int i = 1; i <= N; ++i)
		{
			if (parent[i] < 0)	// 이미 사이클을 제거했으므로, 연결 요소의 수를 세면 됨.
			{
				result++;
			}
		}

		if (result == 0)
		{
			std::cout << "Case " << caseNum << ": No trees.\n";
		}
		else if (result == 1)
		{
			std::cout << "Case " << caseNum << ": There is one tree.\n";
		}
		else
		{
			std::cout << "Case " << caseNum << ": A forest of " << result <<" trees.\n";
		}
		caseNum++;
	}
}

int find(int target_index)
{
	if (parent[target_index] <= 0)
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

	if (node1 == node2)	// 같은 부모, 사이클의 존재 
	{
		parent[node1] = 0; // 해당 연결 요소가 사이클이거나 복수의 에지를 가짐
		return;
	}

	// 트리 아닌 요소는 0으로 제거
	if (parent[node1] == 0 || parent[node2] == 0)
	{
		parent[node1] = 0;
		parent[node2] = 0;
	}
	else if (parent[node1] < parent[node2])
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


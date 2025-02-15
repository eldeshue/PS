// kruskal algorithm
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <tuple>
#include <vector>

typedef std::tuple<int, int, int> edge;

int N, M, ans, start, end;
bool visited[10001];
int parent[10001];
edge edges[100001];

int find(int target_index);
void Union(int node1, int node2);

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(visited, 0, sizeof(visited));
	memset(edges, 0, sizeof(edges));
	memset(parent, -1, sizeof(parent));

	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i)
	{
		std::cin >> std::get<0>(edges[i]) // a
			>> std::get<1>(edges[i])	// b
			>> std::get<2>(edges[i]);	// c
	}
	std::cin >> start >> end;

	auto comp = [](const edge& e1, const edge& e2) -> bool
	{
		return std::get<2>(e1) > std::get<2>(e2);
	};

	std::sort(edges, edges + M + 1, comp);	// 벡터에 넣고 정렬하느니, 우선순위 큐를 써도 될듯

	int pos = 0;
	while (find(start) != find(end)) // 시작과 끝노드가 연결될때 까지 시도함.
	{
		int node1 = std::get<0>(edges[pos]);
		int node2 = std::get<1>(edges[pos]);
		if (find(node1) != find(node2))
		{
			ans = std::get<2>(edges[pos]);
			visited[node1] = true;
			visited[node2] = true;
			Union(node1, node2);
		}
		
		pos++;
	}

	std::cout << ans;
}

int find(int target_index)
{
	if (parent[target_index] < 0)
	{	
		return target_index;
	}
	else
	{
		int p = find(parent[target_index]);
		parent[target_index] = p;
		return p;
	}
}

void Union( int node1, int node2)
{
	node1 = find(node1);
	node2 = find(node2);

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

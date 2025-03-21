 //kruskal algorithm
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <tuple>
#include <vector>

typedef std::tuple<int, int, int> edge;

int N, M, ans, start, end;
int parent[10001];		// union by rank에 의해서 root가 아닌 노드는 랭크값을 가짐
edge edges[100001];

int find(int target_index);
void Union(int node1, int node2);

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(edges, 0, sizeof(edges));
	memset(parent, -1, sizeof(parent));	// 유니온 파인드를 위한 메모리

	// input, 노드의 수와 에지의 수
	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i)
	{
		std::cin >> std::get<0>(edges[i]) // a, 노드 번호
			>> std::get<1>(edges[i])	// b, 노드 번호
			>> std::get<2>(edges[i]);	// c, 가중치(중량)
	}
	std::cin >> start >> end;	// 시종점

	// 정렬을 위한 람다함수
	auto comp = [](const edge& e1, const edge& e2) -> bool
	{
		return std::get<2>(e1) > std::get<2>(e2);
	};	// 가중치 기준으로 에지의 내림차순 정렬
	std::sort(edges, edges + M + 1, comp);

	int pos = 0;	// 에지의 인덱스
	while (find(start) != find(end))	// 최소 신장 트리로 종점에 도착하는지
	{
		int node1 = std::get<0>(edges[pos]);
		int node2 = std::get<1>(edges[pos]);
		if (find(node1) != find(node2))	// find의 결과가 서로 다르다 -> 미신장 노드
		{
			ans = std::get<2>(edges[pos]);	// 정렬의 결과 갈수록 가중치 감소함
			Union(node1, node2);	// 트리의 신장
		}

		pos++;
	}

	std::cout << ans;
}

int find(int target_index)
{
	if (parent[target_index] < 0)	// 0보다 작다 -> 랭크값, 즉 루트
	{
		return target_index;	// 자기 자신을 반환함.
	}
	else	// 루트에 오르기 전까지 계속 재귀적으로 찾아나감
	{
		// path compression
		int p = find(parent[target_index]);	// 재귀의 결과 루트를 획득
		parent[target_index] = p;			// 루트로 초기화, depth 감소
		return p;
	}
}

void Union( int node1, int node2)
{
	node1 = find(node1);
	node2 = find(node2);	// find 과정에서 path compression후 루트 획득
							// path compression으로 rank는 이미 1로 초기화되는게?

	if (node1 == node2)	// 이미 같은 set, do nothing
	{
		return;
	}

	// union by rank
	if (parent[node1] < parent[node2])	// 랭크(절대값)가 큰 쪽이 부모가 된다.
	{
		// node1의 랭크 값이 더 크다, 고로 node1이 부모가 된다
		parent[node1] += parent[node2];	// 랭크 값의 절댓값 증가(음수임)
		parent[node2] = node1;			// 루트를 갱신
	}
	else
	{
		parent[node2] += parent[node1];
		parent[node1] = node2;
	}
}

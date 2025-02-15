/*
	BOJ 2533, 사회 관계망 서비스

	기본적으로 tree구조만 입력으로 주어짐. 따라서 tree의 DP로 문제를 풀었음.

	이하는 새로운 방법의 풀이, heal9179님의 풀이임.
*/
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

struct InternalGraphEdge	// 에지 구조체
{
    int from;
    int to;
};

template<size_t V, size_t E>
struct Edges
{
    std::array<InternalGraphEdge, E> edge;	// 에지들을 저장
    std::array<int, V> begin, end;

    void init(int edgeNum)	// 그래프를 전처리, 여기가 이해가 안되네....
    {
		// 그래프의 구조를 재배치 하는듯. 동일한 위상에 대해서 서로 다른 노드 이름(번호)으로 정규화? 하는듯.
        std::sort(edge.begin(), edge.begin() + edgeNum,	// edge를 정렬`
            [](const InternalGraphEdge& a, const InternalGraphEdge& b)
            {
                return a.from < b.from || (a.from == b.from && a.to < b.to);
            }
        );

		// 뭐하는 짓이지???
        std::fill(begin.begin(), begin.end(), E);	// begin, end를 초기화함. E는 도달 불가능한 큰값
        std::fill(end.begin(), end.end(), 0);

        for (int i = 0; i < edgeNum; ++i)
        {
            begin[edge[i].from] = std::min(begin[edge[i].from], i);	// E와 i 중 작은 값을 취함
            end[edge[i].from] = std::max(end[edge[i].from], i);
        }
    }
};

template<size_t V>
struct Vertice
{
    std::array<int, V> vertex;
};		// 정점의 인덱스를 저장함

template<size_t V>
struct VerticeTopologicalSorter	// 위상 정렬, 그래프 입력을 상정하는 듯 보임.
{
    std::array<int, V> inDegree;	// 노드의 차원, 해당 노드에 붙은 에지의 수

    template<size_t E>
    void sort(int vertexNum, Vertice<V>& destination, const Edges<V, E>& edge)
    {
        std::fill(inDegree.begin(), inDegree.end(), 0);

        for (int i = 1; i <= vertexNum; ++i)	// 각 정점에 대해서
            for (int j = edge.begin[i]; j <= edge.end[i]; ++j)	// 해당 정점에 연결된 에지의 수를 count
                ++inDegree[edge.edge[j].to];	// count 결과가 해당 정점의 차원

        int back = 0;
        for (int i = 1; i <= vertexNum; ++i)	// 차원이 1개다 -> leaf노드임
            if (inDegree[i] == 1)
                destination.vertex[back++] = i;	// leaf 노드들을 가장 먼저 저장

        for (int front = 0; front < vertexNum; ++front)	// 마치 철로를 깔면서 주행하는 느낌임.
        {
            int vertex = destination.vertex[front];	// leaf 노드를 제거했으니, 그 인접 노드에서 leaf탐색
            for (int i = edge.begin[vertex]; i <= edge.end[vertex]; ++i)
                if (--inDegree[edge.edge[i].to] == 1)	// leaf가 확인되면, 저장
                    destination.vertex[back++] = edge.edge[i].to;
        }
    }
};

const int MAXN = 1'000'000 + 10;

Edges<MAXN, MAXN * 2> edge;		// ???
Vertice<MAXN> sorted;
VerticeTopologicalSorter<MAXN> sorter;
bool visited[MAXN];
int minEarlyAdapter[MAXN][2];	// DP?

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    for (int i = 0; i < n - 1; ++i)
    {
		// 무향 그래프임.
        std::cin >> edge.edge[i * 2].from >> edge.edge[i * 2].to;	// 순방향
		// 역방향
        edge.edge[i * 2 + 1].from = edge.edge[i * 2].to;
        edge.edge[i * 2 + 1].to = edge.edge[i * 2].from;
    }

    edge.init((n - 1) * 2);
    sorter.sort(n, sorted, edge);

    for (int i = 0; i < n; ++i)	// 위상 정렬을 통해서 전처리를 수행했기에 단순 반복으로 탐색가능한듯.
    {							// 정렬된 순서로 입력되네....
        int node = sorted.vertex[i];
        visited[node] = true;
        minEarlyAdapter[node][1] = 1;

        for (int j = edge.begin[node]; j <= edge.end[node]; ++j)	// 인접한, 미방문 노드들(자식노드)
            if (visited[edge.edge[j].to])
            {
				// 코어 아이디어는 동일하게 DP다.
                minEarlyAdapter[node][0] += minEarlyAdapter[edge.edge[j].to][1];
                minEarlyAdapter[node][1] += std::min(minEarlyAdapter[edge.edge[j].to][0], minEarlyAdapter[edge.edge[j].to][1]);
            }
    }

	// n-1 번 노드가 루트인듯?
    std::cout << std::min(minEarlyAdapter[sorted.vertex[n - 1]][0], minEarlyAdapter[sorted.vertex[n - 1]][1]);

    return 0;
}

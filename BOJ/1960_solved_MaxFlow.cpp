
/*
	BOJ 1960, 행렬 만들기

	< 최대 유량 풀이 >
	각 row와 col을 노드로 생각함
	source는 row로 연결되고, sink는 col로 연결된다.
	이들 둘 사이의 capacity는 총 합이다.

	row와 col의 사이는 완전 연결 그래프, 각 row는 모두 col에 연결되고, 그 반대도 마찬가지.
	이들 사이의 capacity는 1이다.

	최대 유량 탐색을 수행한 후, row와 col 사이의 유량을 확인하면 행렬을 얻을 수 있다.

	인접 행렬로 구성된 에드몬드-카프 풀이는 시간 초과로 실패했음. 인접 리스트 성공.


#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

constexpr int SRC = 0;
constexpr int MAX_NODE = 1002;
int result_matrix[500][500];

typedef struct edge
{
	int from;
	int to;
	int capacity;
	int flow;
	int rev_idx;
	edge(int f, int t, int c, int i) : from(f), to(t), 
										capacity(c), flow(0), rev_idx(i) {};
} edge;

std::vector<edge> edges;
std::vector<int> graph[MAX_NODE];

void add_edge_to_graph(int from, int to, int c)
{
	int e_idx = edges.end() - edges.begin();
	edges.push_back(edge(from, to, c, e_idx + 1));
	edges.push_back(edge(to, from, 0, e_idx));
	graph[from].push_back(e_idx);
	graph[to].push_back(e_idx + 1);
}

int BFS(const int SNK)
{
	int parent_edge_idx[MAX_NODE];
	int cur_node;
	std::queue<int> Q;

	memset(parent_edge_idx, -1, sizeof(parent_edge_idx));
	Q.push(SRC);
	while (!Q.empty())
	{
		cur_node = Q.front();
		Q.pop();
		if (cur_node == SNK)
			break;
		for (const auto& adj_edge_idx : graph[cur_node])
		{
			const edge& adj_edge = edges[adj_edge_idx];
			const int& next_node = adj_edge.to;
			if (parent_edge_idx[next_node] == -1
				&& adj_edge.capacity > adj_edge.flow)
			{
				parent_edge_idx[next_node] = adj_edge_idx;
				Q.push(next_node);
			}
		}
	}
	// find aug flow, minimum flow among path
	if (parent_edge_idx[SNK] == -1)
		return 0;
	int aug_flow = 2e9;
	cur_node = SNK;
	while (cur_node != SRC)
	{
		const edge& cur_edge = edges[parent_edge_idx[cur_node]];
		aug_flow = std::min(aug_flow,
			cur_edge.capacity - cur_edge.flow);
		cur_node = cur_edge.from;
	}
	// increase the flow on aug path
	cur_node = SNK;
	while (cur_node != SRC)
	{
		edge& cur_edge = edges[parent_edge_idx[cur_node]];
		edge& rev_edge = edges[cur_edge.rev_idx];
		cur_edge.flow += aug_flow;
		rev_edge.flow -= aug_flow;
		cur_node = cur_edge.from;
	}
	return aug_flow;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(result_matrix, 0, sizeof(result_matrix));

	// input
	int N, SNK, input, max_row_flow = 0, max_col_flow = 0;
	std::cin >> N;
	SNK = 2 * N + 1;
	for (int r = 1; r <= N; ++r)	// row
	{
		std::cin >> input;
		add_edge_to_graph(SRC, r, input);
		max_row_flow += input;
	}
	for (int c = N + 1; c <= 2 * N; ++c)	// col
	{
		std::cin >> input;
		add_edge_to_graph(c, SNK, input);
		max_col_flow += input;
	}
	if (max_row_flow != max_col_flow)	// input check
	{
		std::cout << -1;
		return 0;
	}
	// graph build
	// row : 1 ~ N
	// col : N + 1 ~ 2 * N 
	for (int r = 1; r <= N; ++r)	// row
	{
		for (int c = N + 1; c <= 2 * N; ++c)	// col
		{
			add_edge_to_graph(r, c, 1);
		}
	}
	// max flow, edmonds-karp
	int total_flow = 0;
	while (true)
	{
		// BFS, find aug-path 
		int prev_total_flow = total_flow;
		total_flow += BFS(SNK);
		if (prev_total_flow == total_flow)	// no augmentation, done
		{
			break;
		}
	}
	if (total_flow != max_row_flow)	// flow check
	{
		std::cout << -1;
		return 0;
	}
	// set result matrix
	for (const auto& e : edges)
	{
		if (0 < e.from && e.from <= N
			&& N < e.to && e.to <= 2 * N)	// edge from row to colum only
		{
			result_matrix[e.from - 1][e.to - (N + 1)] = e.flow;
		}
	}
	// print
	std::cout << 1 << '\n';
	for (int r = 0; r < N; ++r)	// row
	{
		for (int c = 0; c < N; ++c)	// col
		{
			std::cout << result_matrix[r][c];
		}
		std::cout << '\n';
	}
}

*/

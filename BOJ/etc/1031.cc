
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

constexpr int SRC = 0;
constexpr int MAX_NODE = 102;
int SNK;

typedef struct edge
{
	int from;
	int to;
	int cap;
	int flow;
	edge *rev_ptr;
	int is_red; // is from red ?
	edge(int f, int t, int c, edge *r, int ir) : from(f), to(t),
												 cap(c), flow(0), rev_ptr(r), is_red(ir){};
} edge;

std::vector<edge> edges;
std::vector<edge *> graph[MAX_NODE];
bool result[50][50];

void add_edge_to_graph(int f, int t, int c, int ir)
{
	edges.push_back(edge(f, t, c, (edges.begin() + edges.size() + 1).base(), ir));
	edges.push_back(edge(t, f, 0, (edges.begin() + edges.size()).base(), !ir));
	graph[f].push_back(edges.back().rev_ptr);
	graph[t].push_back(&(edges.back()));
}

int BFS()
{
	std::queue<int> Q;
	std::vector<edge *> parent_edge_ptr(, nullptr);
	int cur_node, next_node, aug_flow = 2e9;
	Q.push(SRC);

	// search the aug path
	while (!Q.empty())
	{
		cur_node = Q.front();
		Q.pop();
		if (cur_node == SNK)
			break;
		int is_cur_red = parent_edge_ptr[cur_node]->is_red;
		if (is_cur_red) // red to black, ascending
		{
			for (auto itr = graph[cur_node].begin(); itr != graph[cur_node].end(); ++itr)
			{
				edge &next_edge = **itr;
				next_node = next_edge.to;
				if (parent_edge_ptr[next_node] == nullptr && next_edge.cap > next_edge.flow)
				{
					parent_edge_ptr[next_node] = *itr;
					Q.push(next_node);
				}
			}
		}
		else // black to red, descending
		{
			for (auto ritr = graph[cur_node].rbegin(); ritr != graph[cur_node].rend(); ++ritr)
			{
				edge &next_edge = **ritr;
				next_node = next_edge.to;
				if (parent_edge_ptr[next_node] == nullptr && next_edge.cap > next_edge.flow)
				{
					parent_edge_ptr[next_node] = *ritr;
					Q.push(next_node);
				}
			}
		}
	}
	// trace_back the path
	cur_node = SNK;
	while (cur_node != SRC)
	{
		const edge &cur_edge = *parent_edge_ptr[cur_node];
		aug_flow = std::min(aug_flow, cur_edge.cap - cur_edge.flow);
		cur_node = cur_edge.from;
	}
	// augment flow of graph
	cur_node = SNK;
	while (cur_node != SRC)
	{
		edge &cur_edge = *parent_edge_ptr[cur_node];
		edge &rev_edge = *cur_edge.rev_ptr;
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
	memset(result, 0, sizeof(result));

	// input
	int N, M, input, src_cap, snk_cap;
	std::cin >> N >> M;
	SNK = N + M + 1;
	for ()
	{
		std::cin >> input;
	}
	for ()
	{
		std::cin >> input;
	}
	if (src_cap != snk_cap)
	{
		std::cout << '-1';
		return 0;
	}
	// build graph
	// edmond-karp
	int prev_flow, total_flow = 0;
	while (true)
	{
		prev_flow = total_flow;
		total_flow += BFS();
		if (prev_flow == total_flow)
		{
			break;
		}
	}
	if (total_flow != src_cap)
	{
		std::cout << '-1';
		return 0;
	}
	// result setting
	for (const auto &cur_edge : edges)
	{
		if (1 <= cur_edge.from && cur_edge.from <= N && N + 1 <= cur_edge.to && cur_edge.to <= N + M)
		{
			result[cur_edge.from - 1][cur_edge.to - (N + 1)] = cur_edge.flow;
		}
	}
	// result
	for (int row = 0; row < N; ++row)
	{
		for (int col = 0; col < M; ++col)
		{
			std::cout << result[row][col];
		}
		std::cout << '\n';
	}
}

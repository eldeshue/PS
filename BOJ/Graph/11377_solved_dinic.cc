
#include <iostream>

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

using ll = long long;
using Node = int;

/**
 * @brief implementation of Dinic algorithm
 * @attention this solver does not work when there is explicit reverse edges in the graph
 */
class ImplicitDinic
{
private:
	using AdjList = std::vector<std::vector<Node>>;
	using pii = std::pair<Node, int>;

	ImplicitDinic() = delete;
	ImplicitDinic(ImplicitDinic const&) = delete;
	ImplicitDinic& operator=(ImplicitDinic const&) = delete;

	Node const source_, sink_;
	int const num_node_;

	AdjList const& graph_;
	std::vector<int> level_;
	std::vector<int> next_node_idx_;

	std::vector<std::vector<ll>> const& capacity_;
	std::vector<std::vector<ll>> flow_;

	// build level graph, bfs
	bool BuildLevelGraph()
	{
		std::queue<pii> q;

		// init next node idx, reset before searching aug path through dfs
		std::fill(next_node_idx_.begin(), next_node_idx_.end(), 0);

		// init level field
		std::fill(level_.begin(), level_.end(), -1);

		// bfs, set level
		level_[source_] = 0;
		q.push(std::make_pair(source_, 0));
		while (!q.empty())
		{
			auto const [cur_node, cur_level] = q.front();
			q.pop();

			for (Node const next_node : graph_[cur_node])
			{
				if (level_[next_node] == -1	// not visited
					&& (capacity_[cur_node][next_node] - flow_[cur_node][next_node]) > 0)	// aug path
				{
					level_[next_node] = cur_level + 1;
					q.push(std::make_pair(next_node, cur_level + 1));
				}
			}
		}

		// does level graph reached end node
		return (level_[sink_] != -1);
	}

	// find aug path, dfs until arrive at sink node
	// return blocking flow of aug path
	ll GetAugFlow(Node const cur_node, ll const cur_flow)
	{
		if (cur_node == sink_)	// sink reached
		{
			return cur_flow;
		}

		for (int& i = next_node_idx_[cur_node]; i < graph_[cur_node].size(); ++i)
		{
			Node const next_node = graph_[cur_node][i];
			ll const residual_flow = capacity_[cur_node][next_node] - flow_[cur_node][next_node];
			if (level_[next_node] > level_[cur_node] && residual_flow > 0)
			{
				// recurse
				ll const aug_flow = GetAugFlow(next_node, std::min(cur_flow, residual_flow));

				// augment path found
				if (aug_flow > 0)
				{
					flow_[cur_node][next_node] += aug_flow;
					flow_[next_node][cur_node] -= aug_flow;	// reverse edge
					return aug_flow;
				}
			}
		}

		// no augment path found
		return 0;
	}

public:
	ImplicitDinic(Node const source, Node const sink,
		AdjList const& graph, std::vector<std::vector<ll>> const& capacity)
		: source_(source), sink_(sink), num_node_(graph.size()),
		graph_(graph), level_(num_node_), next_node_idx_(num_node_, 0), capacity_(capacity), flow_(num_node_, std::vector<ll>(num_node_, 0))
	{
	}

	~ImplicitDinic() {}

	ll GetMaxFlow()
	{
		// set flow as zero
		for (auto& vec : flow_)
		{
			for (auto& f : vec)
			{
				f = 0;
			}
		}

		// solve, get maximum flow
		ll total_flow = 0;
		while (BuildLevelGraph())	// O(V * E * V)
		{
			while (true)	// O(E * V)
			{
				ll new_flow = GetAugFlow(source_, std::numeric_limits<ll>().max());	// O(V)
				if (new_flow == 0)
					break;
				total_flow += new_flow;
			}
		}
		return total_flow;
	}

	ll GetFlow(Node const from, Node const to)
	{
		return flow_[from][to];
	}
};


int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	std::cin >> N >> M >> K;
	int const source = N + M + 1;
	int const sink = N + M + 2;
	int const node_cnt = N + M + 3;
	std::vector<std::vector<int>> graph(node_cnt);
	std::vector<std::vector<ll>> capacity(node_cnt, std::vector<ll>(node_cnt, 0));

	// source to 0
	graph[source].push_back(0);
	graph[0].push_back(source);
	capacity[source][0] = K;	// additional capacity

	// 0 to people
	for (int p = 1; p <= N; ++p)
	{
		graph[0].push_back(p);
		graph[p].push_back(0);
		capacity[0][p] = 1;	// additional capacity to people is limited to 1
	}

	// source to people
	for (int p = 1; p <= N; ++p)
	{
		graph[source].push_back(p);
		graph[p].push_back(source);
		capacity[source][p] = 1;
	}

	// task to sink
	for (int t = N + 1; t <= N + M; ++t)
	{
		graph[t].push_back(sink);
		graph[sink].push_back(t);
		capacity[t][sink] = 1;
	}

	// get edge, people to task, capacity 1
	for (int p = 1; p <= N; ++p)
	{
		int num_edge;
		std::cin >> num_edge;
		while (num_edge--)
		{
			int t;
			std::cin >> t;
			graph[p].push_back(t + N);
			graph[t + N].push_back(p);
			capacity[p][t + N] = 1;
		}
	}

	// solve
	ImplicitDinic solver(source, sink, graph, capacity);
	std::cout << solver.GetMaxFlow() << '\n';

	// debug
	/*
	std::cout << "maximum matching\n";
	for (int p = 1; p <= N; ++p)
	{
		for (int t = N + 1; t <= N + M; ++t)
		{
			std::cout << solver.GetFlow(p, t) << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "people's count\n";
	for (int p = 1; p <= N; ++p)
	{
		std::cout << solver.GetFlow(0, p) << '\n';
	}
	std::cout << "picked task\n";
	for (int t = N + 1; t <= N + M; ++t)
	{
		std::cout << solver.GetFlow(t, sink) << '\n';
	}
	*/
}

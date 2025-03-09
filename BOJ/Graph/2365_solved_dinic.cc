
#include <iostream>

#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits>

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
		while (BuildLevelGraph())
		{
			while (true)
			{
				ll new_flow = GetAugFlow(source_, std::numeric_limits<ll>().max());
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
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	int const source = 0, sink = 2 * N + 1, num_node = sink + 1;
	std::vector<std::vector<int>> graph(num_node);
	std::vector<std::vector<ll>> capacity(num_node, std::vector<ll>(num_node, 0));

	ll input_flow = 0, output_flow = 0;
	for (int r = 1; r <= N; ++r)
	{
		graph[source].push_back(r);
		graph[r].push_back(source);	// for reverse edge

		std::cin >> capacity[source][r];
		input_flow += capacity[source][r];
	}
	for (int c = N + 1; c < sink; ++c)
	{
		graph[c].push_back(sink);
		graph[sink].push_back(c);	// for reverse edge

		std::cin >> capacity[c][sink];
		output_flow += capacity[c][sink];
	}

	// build graph
	for (int r = 1; r <= N; ++r)
	{
		for (int c = N + 1; c < sink; ++c)
		{
			graph[r].push_back(c);
			graph[c].push_back(r);	// for reverse edge
		}
	}

	// parametric search, capacity
	// minimize maximum
	ImplicitDinic solver(source, sink, graph, capacity);
	ll left = 0, right = input_flow + 1;
	while (left < right)
	{
		ll mid = (left + right) >> 1;
		for (int r = 1; r <= N; ++r)
		{
			for (int c = N + 1; c < sink; ++c)
			{
				capacity[r][c] = mid;
			}
		}

		ll const total_flow = solver.GetMaxFlow();
		if (total_flow == input_flow)
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}

	// set result
	for (int r = 1; r <= N; ++r)
	{
		for (int c = N + 1; c < sink; ++c)
		{
			capacity[r][c] = left;
		}
	}
	solver.GetMaxFlow();

	// print result
	std::cout << left << '\n';
	for (int r = 1; r <= N; ++r)
	{
		for (int c = N + 1; c < sink; ++c)
		{
			std::cout << solver.GetFlow(r, c) << ' ';
		}
		std::cout << '\n';
	}
}

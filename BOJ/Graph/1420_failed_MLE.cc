
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

/*
	vertex split

	node에 설정된 capacity를 edge로 옮기기 위해서 기존의 노드를 둘로 나눈다.
*/

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N >> M;
	std::vector<std::string> board(N);
	for (auto& row : board)
		std::cin >> row;

	// build graph
	int const V = 2 * N * M;
	int  source = 0, sink = 0;
	std::vector<std::vector<int>> graph(V);
	std::vector<std::vector<ll>> capacity(V, std::vector<ll>(V, 0));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			// vertex split
			int const cur_square_id = r * M + c;
			int const in_node_id = 2 * cur_square_id;
			int const out_node_id = 2 * cur_square_id + 1;
			if (board[r][c] == '.')
			{
				graph[in_node_id].push_back(out_node_id);
				graph[out_node_id].push_back(in_node_id);
				capacity[in_node_id][out_node_id] = 1;
			}
			else if (board[r][c] == 'K')
			{
				source = out_node_id;
			}
			else if (board[r][c] == 'H')
			{
				sink = in_node_id;
			}
			else	// board[r][c] == '#'
			{
				continue;
			}

			// connect to adj square
			auto ConnectSquaresInGraph = [&](int const next_square_id) {
				int const next_in_node_id = 2 * next_square_id;
				int const next_out_node_id = next_in_node_id + 1;

				// cur node to right node
				graph[out_node_id].push_back(next_in_node_id);
				graph[next_in_node_id].push_back(out_node_id);
				capacity[out_node_id][next_in_node_id] = std::numeric_limits<long long>().max();

				// right node to cur node
				graph[next_out_node_id].push_back(in_node_id);
				graph[in_node_id].push_back(next_out_node_id);
				capacity[next_out_node_id][in_node_id] = std::numeric_limits<long long>().max();
				};

			// right square
			if (c < M - 1 && board[r][c + 1] != '#') ConnectSquaresInGraph(r * M + (c + 1));

			// down square
			if (r < N - 1 && board[r + 1][c] != '#') ConnectSquaresInGraph((r + 1) * M + c);
		}
	}

	// solve, Max flow Min Cut theorem
	ImplicitDinic solver(source, sink, graph, capacity);
	long long max_flow = solver.GetMaxFlow();
	if (max_flow == std::numeric_limits<long long>().max())
		std::cout << -1;
	else
		std::cout << max_flow;
}

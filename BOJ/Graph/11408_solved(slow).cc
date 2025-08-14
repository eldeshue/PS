
/*
	BOJ 11408

	simple MCMF problem
*/

#include <iostream>

#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using ll = long long;
using Node = int;
using Flow = ll;
using Cost = ll;
using AdjList = std::vector<std::vector<Node>>;

ll constexpr const MAX_COST = std::numeric_limits<ll>().max() >> 1;	// half limit
ll constexpr const MAX_FLOW = std::numeric_limits<ll>().max() >> 1;	// half limit

/**
 * Dinic style MCMF solver
 *
 * also known as zkw MCMF.
 * based on implementation of ImplicitDinic
 */
class MCMFZKWSolver
{
private:
	MCMFZKWSolver() = delete;
	MCMFZKWSolver(MCMFZKWSolver const&) = delete;
	MCMFZKWSolver(MCMFZKWSolver const&&) = delete;
	MCMFZKWSolver& operator=(MCMFZKWSolver const&) = delete;
	MCMFZKWSolver& operator=(MCMFZKWSolver const&&) = delete;

	Node const source_, sink_;
	int const num_node_;

	AdjList const& graph_;
	std::vector<bool> visited_;
	std::vector<int> next_node_idx_;

	std::vector<std::vector<Flow>> const& capacity_;
	std::vector<std::vector<Flow>> flow_;

	std::vector<std::vector<Cost>>& edge_cost_;
	std::vector<Cost> cost_;

	Flow get_aug_flow(Node const cur_node, ll const cur_flow) {
		if (cur_node == sink_)	// sink reached
		{
			return cur_flow;
		}

		for (int& i = next_node_idx_[cur_node]; i < graph_[cur_node].size(); ++i)	// remember previous idx to traverse
		{
			Node const next_node = graph_[cur_node][i];
			Flow const residual_flow = capacity_[cur_node][next_node] - flow_[cur_node][next_node];
			bool const is_next_node_on_spfa = (cost_[next_node] == (cost_[cur_node] + edge_cost_[cur_node][next_node]));
			if (!visited_[next_node] && is_next_node_on_spfa && residual_flow > 0)
			{
				// recurse
				visited_[next_node] = true;
				Flow const aug_flow = get_aug_flow(next_node, std::min(cur_flow, residual_flow));

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

	/**
	 * update spfa graph
	 *
	 * find aug path to update spfa dag.
	 *
	 * - time complexity
	 * worst : O(E + V)
	 */
	bool update_spfa()
	{
		Cost mn = MAX_COST;
		for (Node cur_node = 0;cur_node < num_node_; ++cur_node)
		{
			if (!visited_[cur_node])
				continue;
			for (Node const next_node : graph_[cur_node]) {
				if (capacity_[cur_node][next_node] - flow_[cur_node][next_node] > 0 && !visited_[next_node])
					mn = std::min(mn, cost_[cur_node] + edge_cost_[cur_node][next_node] - cost_[next_node]);
			}
		}
		if (mn >= MAX_COST)
			return false;	// no aug path found
		for (int n = 0; n < num_node_; ++n) {
			if (!visited_[n]) cost_[n] += mn;
		}
		return true;
	}


public:
	/**
	 *	< Johnson's algorithm >
	 *
	 * preprocessing all edges, preventing negative cost edge problem.
	 * by doing this, we can use Dijkstra to find spfa dag.
	 *
	 * < Dijkstra's algorithm >
	 *
	 * find shortest path from source with residual flow.
	 *
	 * Reason of using BF is to handle negative cost flow.
	 * To enhance this, use Johnson's algorithm to update edges to prevent negative cost.
	 *
	 * instead of level graph, use spfa dag.
	 *
	 * - time complexity
	 * V : num node, E : num edge, f : max flow
	 * worst : O(E log V)
	 */
	MCMFZKWSolver(Node const source, Node const sink,
		AdjList const& graph, std::vector<std::vector<ll>> const& capacity, std::vector<std::vector<ll>>& edge_cost)
		: source_(source), sink_(sink), num_node_(graph.size()),
		graph_(graph), visited_(num_node_, false), next_node_idx_(num_node_, 0)
		, capacity_(capacity), flow_(num_node_, std::vector<Flow>(num_node_, 0))
		, edge_cost_(edge_cost), cost_(num_node_, MAX_COST)
	{
		std::vector<Cost> h(num_node_, MAX_COST);

		// Johnson Algorithm
		{
			// Bellman Ford algorithm
			std::vector<bool> is_in_q(num_node_, false);
			std::queue<Node> q;

			q.push(source_);
			is_in_q[source_] = true;
			while (!q.empty())
			{
				Node cur_node = q.front();
				is_in_q[cur_node] = false;
				q.pop();

				for (Node const next_node : graph[cur_node])
				{
					if (capacity_[cur_node][next_node] > 0
						&& h[next_node] > (h[cur_node] + edge_cost_[cur_node][next_node]))
					{
						h[next_node] = h[cur_node] + edge_cost_[cur_node][next_node];
						if (!is_in_q[next_node])
						{
							is_in_q[next_node] = true;
							q.push(next_node);
						}
					}

				}
			}

			// update cost between nodes
			for (Node cur_node = 0; cur_node < num_node_; ++cur_node)
			{
				for (Node const next_node : graph_[cur_node])
				{
					if (capacity_[cur_node][next_node] > 0)
						edge_cost_[cur_node][next_node] += h[cur_node] - h[next_node];
				}
			}
		}

		{
			// Dijkstra
			using CNode = std::pair<Cost, Node>;
			std::priority_queue<CNode, std::vector<CNode>, std::greater<CNode>> pq;

			cost_[source_] = 0;
			pq.push(CNode(0LL, source_));
			while (!pq.empty())
			{
				auto const [cur_cost, cur_node] = pq.top();
				pq.pop();

				if (cur_cost > cost_[cur_node])	// erase useless nodes
					continue;

				for (Node const next_node : graph_[cur_node])
				{
					if (capacity_[cur_node][next_node] > 0	// residual flow
						&& cur_cost + edge_cost_[cur_node][next_node] < cost_[next_node])	// better cost
					{
						cost_[next_node] = cur_cost + edge_cost_[cur_node][next_node];
						pq.push(CNode(cost_[next_node], next_node));
					}
				}
			}
		}

		// update cost_
		for (Node n = 0; n < num_node_; ++n)
			cost_[n] += h[sink_] - h[source_];
	}

	std::pair<Flow, Cost> solve()
	{
		// using spfa algorithm, update level graph
		// increase flow at a time
		std::pair<Flow, Cost> result = { 0, 0 };
		auto& [max_flow, min_cost] = result;

		do {
			std::fill(next_node_idx_.begin(), next_node_idx_.end(), 0);
			std::fill(visited_.begin(), visited_.end(), false);
			visited_[source_] = true;

			Flow aug_flow = 0;
			while (aug_flow = get_aug_flow(source_, MAX_FLOW))
			{
				// apply aug flow
				min_cost += aug_flow * cost_[sink_];
				max_flow += aug_flow;

				// reset visited
				std::fill(visited_.begin(), visited_.end(), false);
				visited_[source_] = true;
			}

		} while (update_spfa());

		return result;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	int const graph_size = N + M + 2;
	int const src = 0;
	int const snk = N + M + 1;
	std::vector<std::vector<Node>> graph(graph_size);
	std::vector<std::vector<Flow>> cap(graph_size, std::vector<Flow>(graph_size, 0));
	std::vector<std::vector<Flow>> edge_cost(graph_size, std::vector<Flow>(graph_size, 0));

	auto add_edge = [&](Node const from, Node const to, Flow const cp, Cost const cst) {
		graph[from].push_back(to);
		graph[to].push_back(from);
		cap[from][to] = cp;
		edge_cost[from][to] = cst;
		edge_cost[to][from] = -cst;
		};

	// nodes
	for (int i = 1; i <= N; ++i)
	{
		int job_cnt, job, cost;
		std::cin >> job_cnt;
		for (int j = 0; j < job_cnt; ++j)
		{
			std::cin >> job >> cost;
			job += N;
			add_edge(i, job, 1, cost);	// people to job
		}
	}
	for (int i = 1; i <= N; ++i)
		add_edge(src, i, 1, 0);	// source to people
	for (int i = 1; i <= M; ++i)
		add_edge(i + N, snk, 1, 0);	// job to sink

	MCMFZKWSolver solver(src, snk, graph, cap, edge_cost);
	auto const [max_flow, min_cost] = solver.solve();
	std::cout << max_flow << '\n' << min_cost << std::endl;
}

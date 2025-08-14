
/*
	BOJ 3640

	vertex split + MCMF

	============================================

	모든 노드를 vertex split하면 됨.

	두 대의 배(flow)가 source부터 sink를 향해 이동한다.
	두 flow는 서로 겹치는 edge나 node가 있어서는 안된다.

	edge의 cpapacity를 1로 제한하면 문제를 쉽게 풀 수 있다.
	그러나, node의 중복이 문제가 된다.

	========================================================

	이 부분은 vertex split을 통해서 in node와 out node를 분리하고, 둘 사이에 capacity를 1로 두면 된다.

	최대 유량이 2로 제한되어 있으므로, source를 split한 edge에 capacity를 2로 제한하면 된다.
*/
#include <iostream>

#include <vector>
#include <queue>
#include <limits>

using ll = long long;
using Node = int;
using Flow = ll;
using Cost = ll;

Cost constexpr const MAX_COST = std::numeric_limits<ll>().max() >> 1;	// half limit
Flow constexpr const MAX_FLOW = std::numeric_limits<ll>().max() >> 1;	// half limit
struct REdge;
using RGraph = std::vector<std::vector<REdge>>;
struct REdge
{
	Node next_node_;
	Flow capacity_;
	Flow flow_;
	Cost cost_;	// for MCMF
	size_t reverse_idx_;

	void IncreaseFlow(RGraph& graph, Flow const amount)
	{
		flow_ += amount;
		graph[next_node_][reverse_idx_].flow_ -= amount;
	}
	ll GetResidualFlow() const { return capacity_ - flow_; }
};

class ResidualNetwork
{
private:
	int const node_cnt_;
	RGraph graph_;

public:
	explicit ResidualNetwork(int const n) : node_cnt_(n), graph_(node_cnt_) {}
	ResidualNetwork(ResidualNetwork const& other) : node_cnt_(other.node_cnt_), graph_(other.graph_) {}
	ResidualNetwork& operator=(ResidualNetwork const& rhs) = delete;

	void AddUnDirectedEdge(Node const node1, Node const node2, Flow const cap)
	{
		graph_[node1].push_back({ node2, cap, 0, 0, graph_[node2].size() });	// flow cost in undirected graph???
		graph_[node2].push_back({ node1, cap, 0, 0, graph_[node1].size() - 1 });
	}

	void AddDirectedEdge(Node const from, Node const to, Flow const cap, Cost const cst)
	{
		graph_[from].push_back({ to, cap, 0, cst,  graph_[to].size() });
		graph_[to].push_back({ from, 0, 0, -cst,  graph_[from].size() - 1 });
	}

	RGraph& GetGraph() { return graph_; }
};

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

	RGraph& graph_;
	std::vector<bool> visited_;
	std::vector<int> next_node_idx_;
	std::vector<Cost> cost_;

	// 기존의 dinic이 level graph를 보고 길을 찾았다면, mcmf에서 spfa는 cost를 보고 찾는다.
	Flow get_aug_flow(Node const cur_node, ll const cur_flow) {
		if (cur_node == sink_)	// sink reached
		{
			return cur_flow;
		}

		for (int& i = next_node_idx_[cur_node]; i < graph_[cur_node].size(); ++i)	// remember previous idx to traverse
		{
			auto& e = graph_[cur_node][i];
			Flow const residual_flow = e.GetResidualFlow();
			// spfa 위에 있는 node로 flow를 진행해야 함.
			// spfa 위에 있는지는 해당 node에 도달하기 위해 필요한 cost의 합을 비교하여 결정 가능
			// cost는 매 spfa에 맞는 값을 갖도록 업데이트 되어있음.
			bool const is_next_node_on_spfa = (cost_[e.next_node_] == (cost_[cur_node] + e.cost_));
			if (!visited_[e.next_node_] && is_next_node_on_spfa && residual_flow > 0)
			{
				// recurse
				visited_[e.next_node_] = true;
				Flow const aug_flow = get_aug_flow(e.next_node_, std::min(cur_flow, residual_flow));

				// augment path found
				if (aug_flow > 0)
				{
					e.IncreaseFlow(graph_, aug_flow);
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
	 * update spfa graph with minimum cost.
	 *
	 * - time complexity
	 * worst : O(E + V)
	 */
	bool update_spfa()
	{
		Cost aug_cost = MAX_COST;	// spfa의 업데이트를 위한 minimum aug cost
		for (Node cur_node = 0;cur_node < num_node_; ++cur_node)
		{
			if (!visited_[cur_node])
				continue;
			// spfa를 찾는 방법은 cost_를 비교하는 것
			// 따라서, spfa를 업데이트 한다는 것은 cost_의 업데이트
			// 기존의 spfa를 이루는 visited한 node를 순회하면서, 우회할 수 있는 edge 중, cost가 가장 작은 것
			for (auto const& e : graph_[cur_node])
			{
				if (e.GetResidualFlow() > 0 && !visited_[e.next_node_])
					aug_cost = std::min(aug_cost, cost_[cur_node] + e.cost_ - cost_[e.next_node_]);
			}
		}
		// aug cost를 찾지 못했음, 따라서 그래프 업데이트 불가능
		if (aug_cost >= MAX_COST)
			return false;	// no aug path found

		// aug cost를 획득, 이를 바탕으로 최종 cost 정보 update
		for (int n = 0; n < num_node_; ++n) {
			if (!visited_[n]) cost_[n] += aug_cost;
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
	MCMFZKWSolver(Node const source, Node const sink, RGraph& graph)
		: source_(source), sink_(sink), num_node_(graph.size()),
		graph_(graph), visited_(num_node_, false), next_node_idx_(num_node_, 0), cost_(num_node_, MAX_COST)
	{
		// minimum cost spent to reach each node from source
		std::vector<Cost> h(num_node_, MAX_COST);

		// Johnson Algorithm
		{
			// spfa algorithm
			// modified bellman ford, cannot detact negative cycle
			std::vector<bool> is_in_q(num_node_, false);
			std::queue<Node> q;

			q.push(source_);
			is_in_q[source_] = true;
			while (!q.empty())
			{
				Node cur_node = q.front();
				is_in_q[cur_node] = false;
				q.pop();

				for (auto& [next_node, cap, flow, cost, _] : graph_[cur_node])
				{
					if (cap > 0
						&& h[next_node] > (h[cur_node] + cost))
					{
						h[next_node] = h[cur_node] + cost;
						if (!is_in_q[next_node])
						{
							is_in_q[next_node] = true;
							q.push(next_node);
						}
					}

				}
			}

			// update cost between nodes
			// 두 노드 사이를 직접 연결하는 간선의 cost가
			// spfa의 cost를 기준으로 변경됨
			for (Node cur_node = 0; cur_node < num_node_; ++cur_node)
			{
				for (auto& [next_node, cap, flow, cost, _] : graph_[cur_node])
				{
					if (cap > 0)
						cost -= h[next_node] - h[cur_node];
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

				for (auto& [next_node, cap, flow, cost, _] : graph_[cur_node])
				{
					if (cap > 0	// residual flow
						&& cur_cost + cost < cost_[next_node])	// better cost
					{
						cost_[next_node] = cur_cost + cost;
						pq.push(CNode(cost_[next_node], next_node));
					}
				}
			}

			// update cost_, johnson algorithm
			// to prevent negative edge
			for (Node n = 0; n < num_node_; ++n)
				cost_[n] += h[sink_] - h[source_];
		}
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

	int V, E, A, B, C;
	while (std::cin >> V >> E)
	{
		int const graph_size = 1 + 2 * V;
		ResidualNetwork network(graph_size);
		for (int e = 1; e <= E; ++e)
		{
			std::cin >> A >> B >> C;
			network.AddDirectedEdge(A + V, B, 1, C);
		}
		// vertex split
		// cap 1, cost 0
		for (int v = 2; v < V; ++v)
			network.AddDirectedEdge(v, v + V, 1, 0);
		network.AddDirectedEdge(1, 1 + V, 2, 0);
		network.AddDirectedEdge(V, V + V, 2, 0);
		int const src = 1;
		int const snk = graph_size - 1;

		MCMFZKWSolver solver(src, snk, network.GetGraph());
		auto const [max_flow, min_cost] = solver.solve();
		std::cout << min_cost << std::endl;
	}
}

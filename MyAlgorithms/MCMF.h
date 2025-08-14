/*
	< ZKW MCMF >

	Dinic like Minimum Cost, Maximum Flow algorithm.

	기존의 mcmf와는 달리, dinic 알고리즘의 테크닉을 적용하여 최적화 한 구현체.

	기존의 mcmf알고리즘은 spfa 알고리즘으로 flow를 증가시킬 수 있는 path를 찾아서 유량을 흘려 총 유량을 증진시키는 방식.
	여기서 두 가지 최적화를 수행함.

	1. Dinic style
	매 flow마다 spfa를 구하지 말고, dinic의 level graph를 통하여 한 번에 여러 flow를 흘리는 것처럼 개선.
	다만, level graph를 대신하여 spfa 그래프를 사용함.

	결론적으로 매 flow마다 spfa를 업데이트하지 않고, 한 spfa에서 가능한 flow를 다 흘리고, 그 다음에 spfa를 개선함.

	2. advanced spfa
	기존의 구현에서는 매 flow마다 spfa를 찾았고, 이 때 매번 bellman ford 알고리즘을 사용했음.
	그 결과, 시간 복잡도는 O(E * V * F)였음.

	여기서 매번 새로운 spfa를 찾는게 아니라, 처음 구한 spfa를 update하도록 구현하여 O(V * E)를 O(V + E)로 개선함.

	3. Dijkstra
	여전히 최초 spfa를 구하려면 O(VE)인 bellman-ford를 사용해야 함. 그 이유는 음수 사이클을 갖는 edge의 존재임.

	이를 johnson 알고리즘을 동원하여 음수 edge 이슈를 해결한 다음, Dijkstra를 수행하여 실행 시간을 일부 개선함.

	============================================================================

	reference from https://justicehui.github.io/hard-algorithm/2020/03/24/effective-mcmf/
*/
#ifndef MCMF_H
#define MCMF_H

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

#endif

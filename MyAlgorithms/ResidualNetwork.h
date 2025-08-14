
#ifndef RESIDUAL_NETWORK_H
#define RESIDUAL_NETWORK_H

#include <vector>
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

#endif

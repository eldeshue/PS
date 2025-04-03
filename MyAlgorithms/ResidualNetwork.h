
#ifndef RESIDUAL_NETWORK_H
#define RESIDUAL_NETWORK_H

#include <vector>
#include <deque>

using ll = long long;
using Node = int;

struct REdge
{
	Node next_node_;
	ll capacity_;
	ll flow_;
	REdge* reverse_;

	void IncreaseFlow(ll const amount)
	{
		flow_ += amount;
		reverse_->flow_ -= amount;
	}
	ll GetResidualFlow() { return capacity_ - flow_; }
};
using RGraph = std::vector<std::deque<REdge>>;

class ResidualNetwork
{
private:
	int const node_cnt_;
	RGraph graph_;

public:
	explicit ResidualNetwork(int const n) : node_cnt_(n), graph_(node_cnt_) {}
	ResidualNetwork(ResidualNetwork const& other) : node_cnt_(other.node_cnt_), graph_(other.graph_) {}
	ResidualNetwork& operator=(ResidualNetwork const& rhs) = delete;

	void AddUnDirectedEdge(Node const node1, Node const node2, ll const cap)
	{
		graph_[node1].push_back({ node2, cap, 0, nullptr });
		graph_[node2].push_back({ node1, cap, 0, nullptr });
		graph_[node1].back().reverse_ = &(graph_[node2].back());
		graph_[node2].back().reverse_ = &(graph_[node1].back());
	}

	void AddDirectedEdge(Node const from, Node const to, ll const cap)
	{
		graph_[from].push_back({ to, cap, 0, nullptr });
		graph_[to].push_back({ from, 0, 0, nullptr });
		graph_[from].back().reverse_ = &(graph_[to].back());
		graph_[to].back().reverse_ = &(graph_[from].back());
	}

	RGraph& GetGraph() { return graph_; }
};

#endif

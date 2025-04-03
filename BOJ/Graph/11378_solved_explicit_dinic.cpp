
#include <iostream>

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_set>
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

class ExplicitDinic
{
private:
	using pii = std::pair<Node, int>;

	ExplicitDinic() = delete;
	ExplicitDinic(ExplicitDinic const&) = delete;
	ExplicitDinic& operator=(ExplicitDinic const&) = delete;

	Node const source_, sink_;

	RGraph& graph_;
	std::vector<int> level_;
	std::vector<int> next_node_idx_;

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

			for (REdge& e : graph_[cur_node])
			{
				if (level_[e.next_node_] == -1	// not visited
					&& e.GetResidualFlow() > 0)	// aug path
				{
					level_[e.next_node_] = cur_level + 1;
					q.push(std::make_pair(e.next_node_, cur_level + 1));
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
			REdge& cur_edge = graph_[cur_node][i];
			ll const residual_flow = cur_edge.GetResidualFlow();
			if (level_[cur_edge.next_node_] > level_[cur_node] && residual_flow > 0)
			{
				// recurse
				ll const aug_flow = GetAugFlow(cur_edge.next_node_, std::min(cur_flow, residual_flow));

				// augment path found
				if (aug_flow > 0)
				{
					cur_edge.IncreaseFlow(aug_flow);
					return aug_flow;
				}
			}
		}

		// no augment path found
		return 0;
	}

public:
	ExplicitDinic(Node const source, Node const sink,
		RGraph& graph)
		: source_(source), sink_(sink),
		graph_(graph), level_(graph_.size()), next_node_idx_(graph_.size(), 0)
	{
	}

	~ExplicitDinic() {}

	ll GetMaxFlow()
	{
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

	/**
	* @brief traverse residual network and get seperated set of nodes
	*/
	std::pair<std::unordered_set<int>, std::unordered_set<int>> MinCut()
	{
		std::pair<std::unordered_set<int>, std::unordered_set<int>> result;
		auto& [source_side_nodes, sink_side_nodes] = result;

		for (int i = 0; i < graph_.size(); ++i)
			result.second.insert(i);

		// bfs, traverse residual network
		std::queue<int> q;
		sink_side_nodes.erase(source_);
		source_side_nodes.insert(source_);
		q.push(source_);
		while (!q.empty())
		{
			int const cur_node = q.front();
			q.pop();
			for (REdge& e : graph_[cur_node])
			{
				if (sink_side_nodes.count(e.next_node_) &&
					e.GetResidualFlow() > 0)
				{
					sink_side_nodes.erase(e.next_node_);
					source_side_nodes.insert(e.next_node_);
					q.push(e.next_node_);
				}
			}
		}
		return result;
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
	ResidualNetwork graph(node_cnt);

	// source to 0
	graph.AddDirectedEdge(source, 0, K);

	// 0 to people
	for (int p = 1; p <= N; ++p)
	{
		graph.AddDirectedEdge(0, p, K);
	}

	// source to people
	for (int p = 1; p <= N; ++p)
	{
		graph.AddDirectedEdge(source, p, 1);
	}

	// task to sink
	for (int t = N + 1; t <= N + M; ++t)
	{
		graph.AddDirectedEdge(t, sink, 1);
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
			graph.AddDirectedEdge(p, t + N, 1);
		}
	}

	// solve
	ExplicitDinic solver(source, sink, graph.GetGraph());
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

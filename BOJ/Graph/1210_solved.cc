
/*
	BOJ 1210

	노드에 비용을 부과하므로, vertex split을 수행해하여 둘 사이에 노드 점유 비용을 부과하는 엣지를 추가

	min cut은 max flow이므로(쾨닉의 정리), 최대유량 알고리즘을 돌려주면 된다.

	최대유량을 돌린 후 얻어지는 residual network에 대해서 그래프를 분할하는 edge를 찾는데,
	여기서 많이 해맸다.

	---

	처음에는 src에서 bfs를 돌려 residual flow가 0인 edge를 수집했는데, 반례가 존재했다.
	그 다음은 src와 sink에서 각각 돌린 다음, 겹치는느 것을 찾았으나, 이 또한 반례가 존재했다.

	---

	정답은 문제의 정의속에 있었다. min cut에 의해 분할되면서, residual flow가 0인 엣지를 찾으면 된다.

	---

	발상이 꽤 빠르게 떠올린 것 치고는 cut을 내는 edge 구하는 데에 있어서 좀 문제가 있었다...
	쾨닉의 정리에 대한 이해도가 부족한 탓인듯....
*/

#include <iostream>
#include <set>

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

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
					cur_edge.IncreaseFlow(graph_, aug_flow);
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

	std::set<int> solve() {
		// vertex cover 구하는 알고리즘 수행, vertex split으로 나눠진 노드들 획득하기
		// min cut에 의해서 서로 갈라지고, residual flow가 0인 에지를 찾아야...
		auto [from_source, from_sink] = MinCut();
		std::set<int> result;
		// pick common, search for all edges
		for (auto const v : from_source) {
			for (auto const& e : graph_[v]) {
				if (from_sink.contains(e.next_node_) && e.capacity_ > 0 && e.GetResidualFlow() == 0) { // find splitted & saturated edge
					result.insert(v >> 1);
				}
			}
		}
		return result;
	}

};


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int n, m, src, snk;
	std::cin >> n >> m >> src >> snk;
	std::vector<ll> node_cost(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> node_cost[i];
	}
	std::vector<std::pair<int, int>> edges(m);
	for (auto& [n1, n2] : edges) {
		std::cin >> n1 >> n2;
	}

	// build residual graph
	// vertex split
	ResidualNetwork net_work(2 * (n + 1));
	for (int node = 1; node <= n; ++node) {
		int split_node1 = node << 1;	// inlet
		int split_node2 = split_node1 | 1; // outlet

		// 문제는 undirected graph인데, 여기서 vertex split을 어떻게 처리해야 되는거지???
		// 문제를 directed로 만들어야 하는구나?
		net_work.AddDirectedEdge(split_node1, split_node2, node_cost[node], 0);
	}

	// link nodes
	for (auto const [n1, n2] : edges) {
		int in_n1 = n1 << 1;
		int out_n1 = in_n1 | 1;
		int in_n2 = n2 << 1;
		int out_n2 = in_n2 | 1;

		net_work.AddDirectedEdge(out_n1, in_n2, MAX_FLOW, 0);
		net_work.AddDirectedEdge(out_n2, in_n1, MAX_FLOW, 0);
	}

	// run max flow
	ExplicitDinic solver((Node)(src << 1), (Node)((snk << 1) | 1), net_work.GetGraph());
	ll max_flow = solver.GetMaxFlow();

	// find max cut based on residual flow
	auto result = solver.solve();
	for (auto const node : result) {
		std::cout << node << ' ';
	}
}

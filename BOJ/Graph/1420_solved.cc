
#include <iostream>
#include <string>


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

/*
	vertex split

	node에 설정된 capacity를 edge로 옮기기 위해서 기존의 노드를 둘로 나눈다.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
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
	ResidualNetwork rnetwork(V);
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
				rnetwork.AddDirectedEdge(in_node_id, out_node_id, 1);
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

				// cur node to right node
				rnetwork.AddDirectedEdge(out_node_id, next_in_node_id, std::numeric_limits<long long>().max());
				};

			// left square
			if (c > 0 && board[r][c - 1] != '#') ConnectSquaresInGraph(r * M + (c - 1));

			// right square
			if (c < M - 1 && board[r][c + 1] != '#') ConnectSquaresInGraph(r * M + (c + 1));

			// up square
			if (r > 0 && board[r - 1][c] != '#') ConnectSquaresInGraph((r - 1) * M + c);

			// down square
			if (r < N - 1 && board[r + 1][c] != '#') ConnectSquaresInGraph((r + 1) * M + c);
		}
	}

	// solve, Max flow Min Cut theorem
	ExplicitDinic solver(source, sink, rnetwork.GetGraph());
	long long max_flow = solver.GetMaxFlow();
	if (max_flow == std::numeric_limits<long long>().max() || max_flow < 0)	// fucking overflow....
		std::cout << -1;
	else
		std::cout << max_flow;
}

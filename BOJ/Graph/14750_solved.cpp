
#include <iostream>
#include <tuple>

using Point = std::pair<long long, long long>;
using Line = std::pair<Point, Point>;
#define X first
#define Y second

int ccw(const Point& v1, const Point& v2)
{
	long long crossProduct = v1.X * v2.Y - v1.Y * v2.X;
	if (crossProduct > 0)	// counter clock wise
		return 1;
	else if (crossProduct < 0)	// clock wise
		return -1;
	else
		return 0;	// parallel
}

/*
	return value

	1 : cross one point
	0 : does not cross
	-1 : cross multiple points, overlapped
 */
int isCross(Line& l1, Line& l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	int v1 =
		ccw(vec1, std::make_pair(l2.first.X - l1.second.X, l2.first.Y - l1.second.Y))
		* ccw(vec1, std::make_pair(l2.second.X - l1.second.X, l2.second.Y - l1.second.Y));

	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	int v2 =
		ccw(vec2, std::make_pair(l1.first.X - l2.second.X, l1.first.Y - l2.second.Y))
		* ccw(vec2, std::make_pair(l1.second.X - l2.second.X, l1.second.Y - l2.second.Y));

	// multiply vector
	long long tmp = vec1.X;
	vec1.X *= vec2.X;
	vec1.Y *= vec2.X;
	vec2.X *= tmp;
	vec2.Y *= tmp;

	if (v1 == 0 && v2 == 0)	// parallel
	{
		if (l1.first > l1.second) std::swap(l1.first, l1.second);
		if (l2.first > l2.second) std::swap(l2.first, l2.second);

		if (l2.first < l1.second && l1.first < l2.second && vec1 == vec2)	// parallel and cross, at multiple point
			return -1;
		else if (l2.first <= l1.second && l1.first <= l2.second)	// parallel and cross, at one point
			return 1;
		else	// parallel but does not cross
			return 0;
	}

	if ((v1 <= 0) && (v2 <= 0))
		return 1;
	else
		return 0;
}

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
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, H, M;
	std::cin >> N >> K >> H >> M;

	Point start, cur, prev;
	std::vector<Line> walls(N);
	std::cin >> start.X >> start.Y;
	prev = start;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> cur.X >> cur.Y;
		walls[i] = Line(prev, cur);
		prev = cur;
	}
	walls[N - 1] = Line(start, prev);

	int const nodeCnt = H + M + 2;
	int const source = nodeCnt - 2;
	int const sink = nodeCnt - 1;
	ResidualNetwork network(nodeCnt);
	std::vector<Point> holes(H);
	for (int i = 0; i < H; ++i)
	{
		std::cin >> holes[i].X >> holes[i].Y;
		// hole to sink
		network.AddDirectedEdge(i + M, sink, K);
	}
	std::vector<Point> mices(M);
	for (int i = 0; i < M; ++i)
	{
		std::cin >> mices[i].X >> mices[i].Y;
		// source to mice
		network.AddDirectedEdge(source, i, 1);
	}

	// mouse to hole
	for (int m = 0; m < M; ++m)
	{
		for (int h = 0; h < H; ++h)
		{
			Line mouseToHole(mices[m], holes[h]);

			bool isSeen = true;
			for (auto w : walls)
			{
				Line holeToW1(holes[h], w.first);
				Line holeToW2(holes[h], w.second);
				if (isCross(mouseToHole, w) != 0	// cross
					&& (isCross(holeToW1, w) != -1	// except on the wall
						&& isCross(holeToW2, w) != -1))
				{
					isSeen = false;
				}
			}

			if (isSeen)
			{
				network.AddDirectedEdge(m, h + M, 1);
			}
		}
	}

	ExplicitDinic solver(source, sink, network.GetGraph());
	if (solver.GetMaxFlow() >= M)
		std::cout << "Possible";
	else
		std::cout << "Impossible";
}
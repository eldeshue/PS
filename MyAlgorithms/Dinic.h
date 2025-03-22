
#ifndef DINIC_H
#define DINIC_H

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

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
			for (int const next_node : graph_[cur_node])
			{
				if (sink_side_nodes.count(next_node) &&
					capacity_[cur_node][next_node] - flow_[cur_node][next_node] > 0)
				{
					sink_side_nodes.erase(next_node);
					source_side_nodes.insert(next_node);
					q.push(next_node);
				}
			}
		}
		return result;
	}

};

#endif

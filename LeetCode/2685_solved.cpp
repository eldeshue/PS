#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <functional>

class Solution {
private:
	bool IsCompleteCC(int const node_cnt, int const edge_cnt)
	{
		return edge_cnt == (node_cnt * (node_cnt - 1)) / 2;
	}
public:
	int countCompleteComponents(int n,
		vector<vector<int>>& edges)
	{
		vector<int> disjoint_set(n, -1);
		vector<int> edge_count(n, 0);

		function<int(int const)> find = [&](int const node) {
			if (disjoint_set[node] < 0)
			{
				// base case
				return node;
			}
			return disjoint_set[node] = find(disjoint_set[node]);
			};

		auto unite = [&](int node1, int node2) {
			node1 = find(node1);
			node2 = find(node2);

			if (node1 == node2)
			{
				// already in same cc
				// increase edge count
				++edge_count[node1];
			}
			else
			{
				// in different cc, unite by rank
				if (disjoint_set[node1] < disjoint_set[node2])
				{
					// processing node
					disjoint_set[node1] += disjoint_set[node2];
					disjoint_set[node2] = node1;

					// processing edge count combine
					edge_count[node1] += edge_count[node2] + 1;
					edge_count[node2] = -1;
				}
				else
				{
					disjoint_set[node2] += disjoint_set[node1];
					disjoint_set[node1] = node2;

					edge_count[node2] += edge_count[node1] + 1;
					edge_count[node1] = -1;
				}
			}
			};

		// processing
		for (auto const& e : edges)
		{
			int const node1 = e[0];
			int const node2 = e[1];

			unite(node1, node2);
		}

		// get result
		int result = 0;
		for (int i = 0; i < n; ++i)
		{
			result += IsCompleteCC(-1 * disjoint_set[i], edge_count[i]);
		}
		return result;
	}
};


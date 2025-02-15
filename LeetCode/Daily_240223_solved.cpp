/*
	Dijkstra with depth.
*/
#include <iostream>

using namespace std;

// solution class
#include <queue>
#include <tuple>

using uint = unsigned int;
using node = pair<int, uint>;		// next node, cost
using status = tuple<int, uint, int>;	// node id, cost, depth

struct cmp
{
	bool operator()(const status& s1, const status& s2)
	{
		return get<1>(s1) > get<1>(s1);
	}
};

class Solution
{
public:
	// solution method
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
	{
		vector<vector<node>> graph(n);
		vector<uint> cost(n, -1);
		priority_queue<status, vector<status>, cmp> PQ;

		// max depth, k
		// graph setup
		for (const vector<int>& entry : flights)
			graph[entry[0]].push_back(make_pair(entry[1], entry[2]));

		// Dijkstra
		int curNode, curDepth;
		uint curCost;
		cost[src] = 0;
		PQ.push(make_tuple(src, 0, 0));
		while (!PQ.empty())
		{
			curNode = get<0>(PQ.top());
			curCost = get<1>(PQ.top());
			curDepth = get<2>(PQ.top());
			PQ.pop();
			// depth check
			if (curDepth > k)
				continue;
			// node traverse
			for (const node& nextNode : graph[curNode])
			{
				uint nextCost = curCost + nextNode.second;
				if (nextCost < cost[nextNode.first])
				{
					cost[nextNode.first] = nextCost;
					PQ.push(make_tuple(nextNode.first, nextCost, curDepth + 1));
				}
			}
		}
		return cost[dst];
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	/*
	int n = , src = , dst = , k = ;
	vector<vector<int>> f = { {, ,}, {, ,}, {, ,}, {, ,}, {, ,} };
	*/
	Solution test;
	int n1 = 4, src1 = 0, dst1 = 3, k1 = 1;
	vector<vector<int>> f1 = { {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200} };
	std::cout << test.findCheapestPrice(n1, f1, src1, dst1, k1);
}


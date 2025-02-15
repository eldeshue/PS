
#include <iostream>

using namespace std;

#include <queue>
#include <tuple>

using uint = unsigned int;
using node = pair<int, uint>;		  // next node, cost
using status = tuple<int, uint, int>; // node id, cost, depth

struct cmp
{
	bool operator()(const status &s1, const status &s2)
	{
		return get<1>(s1) > get<1>(s1);
	}
};

void print_status(const vector<uint> &cost, int curNodeId, uint curCost, int curDepth)
{
	cout << "==== < print status > ====\n";
	// debug
	cout << "current visit node id   : " << curNodeId << '\n';
	cout << "current visit node cost : " << curCost << '\n';
	cout << "current visit node depth: " << curDepth << '\n';
	cout << "==== < cost  status > ====\n";
	for (const int &n : cost)
	{
		cout << n << ' ';
	}
	cout << '\n';
	cout << "==========================\n";
	// debug
}

class Solution
{
public:
	// solution method
	int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
	{
		vector<vector<node>> graph(n);
		vector<uint> cost(n, -1);
		priority_queue<status, vector<status>, cmp> PQ;

		// max depth, k
		// graph setup
		for (const vector<int> &entry : flights)
			graph[entry[0]].push_back(make_pair(entry[1], entry[2]));

		// traverse
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
			for (const node &nextNode : graph[curNode])
			{
				uint nextCost = curCost + nextNode.second;
				if (nextCost < cost[nextNode.first])
				{
					cost[nextNode.first] = nextCost;
					PQ.push(make_tuple(nextNode.first, nextCost, curDepth + 1));

					// debug
					print_status(cost, curNode, curCost, curDepth);
					// debug
				}
			}
		}

		return cost[dst];
	}
	//
};
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<vector<int>> input =
		{
			{0, 1, 10},
			{1, 2, 10},
			{2, 3, 10},
			{3, 4, 10},
			{4, 5, 10},
			{0, 6, 45},
			{6, 4, 10}};
	int n = 7, src = 0, dst = 5, k = 3;
	Solution test;
	std::cout << test.findCheapestPrice(n, input, src, dst, k);
}

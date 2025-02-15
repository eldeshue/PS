
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <tuple>

int numNode, numEdge;
std::vector<int> adjNode[4001];
int edges[4001][4001];
unsigned int wolfMinDistance[4001][2];
unsigned int foxMinDistance[4001];

struct wolfCmp
{
	bool operator() (const std::tuple<bool, int, int>& t1, const std::tuple<bool, int, int>& t2)
	{ // first : isEven  second : node  third : cost
		return std::get<2>(t1) > std::get<2>(t2);
	}
};

void wolfDijkstra()
{
	std::priority_queue<std::tuple<bool, int, int>, std::vector<std::tuple<bool, int, int>>, wolfCmp> PQ;

	PQ.push(std::make_tuple(true, 1, 0));
	while (!PQ.empty())
	{
		bool isEven = std::get<0>(PQ.top());
		int curNode = std::get<1>(PQ.top());
		int curCost = std::get<2>(PQ.top());
		PQ.pop();
		if (isEven)
		{
			if (wolfMinDistance[curNode][0] <= curCost)
			{
				continue;
			}
			wolfMinDistance[curNode][0] = curCost;
		}
		else
		{
			if (wolfMinDistance[curNode][1] <= curCost)
			{
				continue;
			}
			wolfMinDistance[curNode][1] = curCost;
		}
		for (const auto& nextNode : adjNode[curNode])
		{
			if (isEven)
			{	// 2 times faster, so 1 / 2
				PQ.push(std::make_tuple(!isEven, nextNode, curCost + edges[curNode][nextNode]));
			}
			else
			{	// 2 times slower
				PQ.push(std::make_tuple(!isEven, nextNode, curCost + (edges[curNode][nextNode] * 4)));
			}
		}
	}
}

struct foxCmp
{
	bool operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{	// first : node		second : cost
		return p1.second > p2.second;
	}
};

void foxDijkstra() // normal Dijkstra
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, foxCmp> PQ;

	PQ.push(std::make_pair(1, 0));
	while (!PQ.empty())
	{
		int curNode = PQ.top().first;
		int curCost = PQ.top().second;
		PQ.pop();
		if (foxMinDistance[curNode] <= curCost)
		{
			continue;
		}
		foxMinDistance[curNode] = curCost;
		for (const auto& nextNode : adjNode[curNode])
		{
			PQ.push(std::make_pair(nextNode, curCost + (edges[curNode][nextNode] * 2)));
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(edges, 0, sizeof(edges));
	memset(wolfMinDistance, -1, sizeof(wolfMinDistance));
	memset(foxMinDistance, -1, sizeof(foxMinDistance));

	// input
	int n1, n2, w;
	std::cin >> numNode >> numEdge;
	for (int i = 0; i < numEdge; ++i)
	{
		std::cin >> n1 >> n2 >> w;
		adjNode[n1].push_back(n2);
		adjNode[n2].push_back(n1);
		edges[n1][n2] = w;
		edges[n2][n1] = w;
	}

	// Dijkstra
	wolfDijkstra();
	foxDijkstra();

	// compare
	int result = 0;
	for (int i = 1; i <= numNode; ++i)
	{
		if (wolfMinDistance[i][0] > foxMinDistance[i] && wolfMinDistance[i][1] > foxMinDistance[i])
		{
			result++;
		}
	}
	std::cout << result;
	return 0;
}
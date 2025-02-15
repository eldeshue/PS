
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

int numNode, numEdge, startNode;
std::vector<std::pair<int,int>> adjNode[20001];
unsigned int minDist[20001];

struct cmp
{
	bool operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{ // first : adj node number		secnd : cost
		return p1.second > p2.second;	// priority queue
	}
};

void Dijkstra()
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> PQ;
	
	PQ.push(std::make_pair(startNode, 0));
	while (!PQ.empty())
	{
		// get adj node with the minimum cost
		int curNode = PQ.top().first;
		int curCost = PQ.top().second;
		PQ.pop();
		if (curCost >= minDist[curNode])
		{
			continue;
		}
		minDist[curNode] = curCost;
		for (const auto& nextNode : adjNode[curNode])
		{	// update adj Node of the spanning tree
			PQ.push(std::make_pair(nextNode.first, curCost + nextNode.second));
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(minDist, -1, sizeof(minDist));

	int node1, node2, cost;
	std::cin >> numNode >> numEdge >> startNode;
	for (int i = 0; i < numEdge; ++i)
	{
		std::cin >> node1 >> node2 >> cost;
		adjNode[node1].push_back(std::make_pair(node2, cost));
	}

	Dijkstra();
	for (int i = 1; i <= numNode; ++i)
	{
		if (minDist[i] == -1)
		{
			std::cout << "INF\n";
		}
		else
		{
			std::cout << minDist[i] << "\n";
		}
	}
}
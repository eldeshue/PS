
#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

using uint = unsigned int;
using status = std::pair<int, int>;	// first : next node, second : net cost
int N, M, S, D;
uint adjMatrix[500][500];

struct cmp_priority
{
	bool operator()(const status& st1, const status& st2)
	{
		if (st1.second == st2.second)
			return st1.first > st2.first;
		return st1.second > st2.second;	// second is the cost of the status
	}
};

int Dijkstra()
{
	std::priority_queue<status, std::vector<status>, cmp_priority> PQ;
	uint prevNode[500];
	uint netCost[500];
	uint curNode, curCost, nextCost;
	memset(prevNode, -1, sizeof(prevNode));
	memset(netCost, -1, sizeof(netCost));

	netCost[S] = 0;
	PQ.push(std::make_pair(S, 0));
	while (!PQ.empty())
	{
		curNode = PQ.top().first;
		curCost = PQ.top().second;
		PQ.pop();
		if (netCost[curNode] < curCost)
			continue;
		for (uint nextNode = 0; nextNode < 500; ++nextNode)
		{
			if (adjMatrix[curNode][nextNode] == -1)
				continue;
			nextCost = curCost + adjMatrix[curNode][nextNode];
			if (nextCost < netCost[nextNode])
			{
				netCost[nextNode] = nextCost;
				prevNode[nextNode] = curNode;
			}
			PQ.push(std::make_pair(nextNode, nextCost));
		}
	}
	// erase route
	curNode = D;
	while (prevNode[curNode] != -1)
	{
		adjMatrix[prevNode[curNode]][curNode] = -1;
		curNode = prevNode[curNode];
	}
	// return
	return netCost[D];
}

int getNearShortest()
{
	// get min cost
	int minCost = Dijkstra();
	if (minCost == -1)
		return -1;
	// do Dijkstra again and get near min cost
	// if those values equal, do it again.
	while (true)
	{
		int nearMinCost = Dijkstra();
		if (nearMinCost == -1)
			return -1;
		else if (nearMinCost > minCost)
			return nearMinCost;
	}
	// unreachable
	return -1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int u, v, p;
	while (true)
	{
		memset(adjMatrix, -1, sizeof(adjMatrix));
		std::cin >> N >> M;
		if (N == 0 && M == 0)
			break;
		std::cin >> S >> D;
		for (int i = 0; i < M; ++i)
		{
			std::cin >> u >> v >> p;
			adjMatrix[u][v] = p;
		}
		std::cout << getNearShortest() << '\n';
	}
}

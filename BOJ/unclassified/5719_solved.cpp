
/*
#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

using uint = unsigned int;
using status = std::pair<int, int>;	// first : next node, second : net cost
int N, M, S, D;
uint adjMatrix[500][500];
std::vector<uint> prevNode[500];	// save parent nodes
uint netCost[500];

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
	uint curNode, curCost, nextCost;
	memset(netCost, -1, sizeof(netCost));
	for (int i = 0; i < 500; ++i)
		prevNode[i].clear();

	netCost[S] = 0;
	PQ.push(std::make_pair(S, 0));
	while (!PQ.empty())
	{
		curNode = PQ.top().first;
		curCost = PQ.top().second;
		PQ.pop();
		if (netCost[curNode] < curCost)
			continue;
		for (uint nextNode = 0; nextNode < N; ++nextNode)
		{
			if (adjMatrix[curNode][nextNode] == -1)
				continue;
			nextCost = curCost + adjMatrix[curNode][nextNode];
			if (nextCost < netCost[nextNode])
			{
				netCost[nextNode] = nextCost;
				prevNode[nextNode].clear();
				prevNode[nextNode].push_back(curNode);
				PQ.push(std::make_pair(nextNode, nextCost));
			}
			else if (nextCost == netCost[nextNode])
			{
				// to save several route with same cost
				prevNode[nextNode].push_back(curNode);
			}
		}
	}
	// return
	return netCost[D];
}

void BFSErase(int startNode, int endNode)
{
	std::queue<int> Q;
	bool visited[500] = { false, };

	visited[endNode] = true;
	Q.push(endNode);
	while (!Q.empty())
	{
		int curNode = Q.front();
		Q.pop();
		for (const auto parentNode : prevNode[curNode])
		{
			// erase
			adjMatrix[parentNode][curNode] = -1;
			if (!visited[parentNode])
			{
				Q.push(parentNode);
				visited[parentNode] = true;
			}
		}
	}
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
		int result = Dijkstra();
		if (result != -1)
		{
			BFSErase(S, D);
			result = Dijkstra();
		}
		std::cout << result << '\n';
	}
}
*/
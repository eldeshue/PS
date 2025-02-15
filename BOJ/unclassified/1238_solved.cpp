#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

int numNode, numEdge, numGoal;
std::vector<std::pair<int, int>> adjNode1[1001];	// 정방향 그래프 정보
std::vector<std::pair<int, int>> adjNode2[1001];	// 역방향 그래프 정보
unsigned int minFromParty[1001];	// 정방향 그래프, 파티장에서 복귀하는데 걸리는 최단 cost 기록
unsigned int minToParty[1001];		// 역방향 그래프, 도시에서 파티장에 가는데 드는 최단 cost 기록

struct cmp
{
	bool operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{
		return p1.second > p2.second;
	}
};

void Dijkstra(int startNode, std::vector<std::pair<int, int>>* adjNode, unsigned int* minDist)
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> PQ;
	memset(minDist, -1, 1001 * sizeof(unsigned int));

	PQ.push(std::make_pair(startNode, 0));
	while (!PQ.empty())
	{
		int curNode = PQ.top().first;
		int curCost = PQ.top().second;
		PQ.pop();
		if (curCost >= minDist[curNode])
		{
			continue;
		}
		minDist[curNode] = curCost;
		for (const auto& nextNode : adjNode[curNode])
		{
			PQ.push(std::make_pair(nextNode.first, curCost + nextNode.second));
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int s, e, c;
	std::cin >> numNode >> numEdge >> numGoal;
	for(int i = 0; i < numEdge; ++i)
	{
		std::cin >> s >> e >> c;
		adjNode1[s].push_back(std::make_pair(e, c));
		adjNode2[e].push_back(std::make_pair(s, c));
	}

	unsigned int maxCost = 0;
	Dijkstra(numGoal, adjNode1, minFromParty);
	Dijkstra(numGoal, adjNode2, minToParty);
	for (int i = 1; i <= numNode; ++i)
	{
		maxCost = std::max(maxCost, minFromParty[i] + minToParty[i]);
	}
	std::cout << maxCost;
}
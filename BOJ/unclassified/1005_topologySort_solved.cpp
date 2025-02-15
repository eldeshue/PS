
#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

typedef std::pair<int, int> node;	// cost, in degree

int T, N, K;
node nodeArr[1001];
int Cost[1001];
bool visited[1001];
std::vector<int> adjList[1001];	//

void clear()
{
	memset(nodeArr, 0, sizeof(nodeArr));
	memset(Cost, 0, sizeof(Cost));
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= N; ++i)
	{
		adjList[i].clear();
	}
}

void BFS()
{
	std::queue<int> indexQ;
	for (int i = 1; i <= N; ++i)
	{
		if (nodeArr[i].second == 0)
		{
			nodeArr[i].first = Cost[i];
			visited[i] = true;
			indexQ.push(i);
		}
	}

	while (!indexQ.empty())
	{
		int curIndex = indexQ.front();
		int curCost = nodeArr[curIndex].first;
		indexQ.pop();

		for (auto& nextIndex : adjList[curIndex])
		{
			// decrease degree
			int nextDegree = --nodeArr[nextIndex].second;
			// update max Cost
			int nextCost = curCost + Cost[nextIndex];
			if (nodeArr[nextIndex].first < nextCost)
			{
				nodeArr[nextIndex].first = nextCost;
			}
			// add next node
			// topological sort
			// in degree == 0, 즉 자신보다 선행되어야 하는 노드는 이미 모두 거쳐져야함.
			if (!visited[nextIndex] && nextDegree == 0)
			{
				visited[nextIndex] = true;
				indexQ.push(nextIndex);
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int x, y, goal;
	std::cin >> T;
	for (int i = 0; i < T; ++i)
	{
		clear();
		std::cin >> N >> K;
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> Cost[j];
		}
		for (int j = 0; j < K; ++j)
		{
			std::cin >> x >> y;
			adjList[x].push_back(y);
			nodeArr[y].second++;
		}
		BFS();
		std::cin >> goal;
		std::cout << nodeArr[goal].first << "\n";
	}
}
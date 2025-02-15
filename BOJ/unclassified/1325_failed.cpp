
#include <iostream>
#include <vector>
#include <memory.h>

int numCreed[10001];
std::vector<int> adjList[10001];

// 트리였으면 문제가 없었는데, 그래프에서 사이클이 생기면 문제가 생기네....
// 해당 방식을 해결하려면 강한 연결요소 알고리즘을 활용해야 할 것으로 생각됨...
int dfs(int curNode)
{
	if (numCreed[curNode] > 0)
		return numCreed[curNode];
	else if (numCreed[curNode] == 0)
	{
		// cycle

	}
	numCreed[curNode] = 0;
	for (const int& nextNode : adjList[curNode])
	{
		numCreed[curNode] += dfs(nextNode);
	}
	return ++numCreed[curNode];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(numCreed, -1, sizeof(numCreed));

	// input
	int N, M, parent, child;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> child >> parent;
		adjList[parent].push_back(child);
	}
	// search
	for (int i = 1; i <= N; ++i)
	{
		if (numCreed[i] == -1)
			dfs(i);
	}
	int maxCnt = 0;
	for (int i = 1; i <= N; ++i)
	{
		maxCnt = std::max(maxCnt, numCreed[i]);
	}
	// output
	for (int i = 1; i <= N; ++i)
	{
		if (numCreed[i] == maxCnt)
			std::cout << i << ' ';
	}
}
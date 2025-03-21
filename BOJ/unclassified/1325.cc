
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

int numCreed[10001];
std::vector<int> adjList[10001];

void bfs(int startNode)
{
	std::queue<int> Q;
	bool visited[10001];
	memset(visited, 0, sizeof(visited));

	visited[startNode] = true;
	numCreed[startNode]++;
	Q.push(startNode);
	while (!Q.empty())
	{
		int curNode = Q.front();
		Q.pop();
		for (const int& nextNode : adjList[curNode])
		{
			if (!visited[nextNode])
			{
				visited[nextNode] = true;
				numCreed[nextNode]++;
				Q.push(nextNode);
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(numCreed, 0, sizeof(numCreed));

	// input
	int N, M, parent, child;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> parent >> child;
		adjList[parent].push_back(child);
	}
	// search
	for (int i = 1; i <= N; ++i)
			bfs(i);
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

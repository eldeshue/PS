
#include <iostream>
#include <functional>
#include <vector>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, a, b;
	std::cin >> N >> M;
	if (N == 1)
	{
		std::cout << 0;
		return 0;
	}
	std::vector<std::vector<int>> adjList(N + 1);
	while (M--)
	{
		std::cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	// bfs로 연결 요소를 탐색하며 홀수 차수를 가지는 노드의 개수를 샌다.
	std::vector<int> visited(N + 1, false);
	auto bfs = [&](const int startNode)
		{
			std::queue<int> q;
			int oddCnt = 0;

			visited[startNode] = true;
			q.push(startNode);
			while (!q.empty())
			{
				const int curNode = q.front();
				q.pop();
				oddCnt += adjList[curNode].size() % 2;
				for (const int nextNode : adjList[curNode])
				{
					if (!visited[nextNode])
					{
						visited[nextNode] = true;
						q.push(nextNode);
					}
				}
			}
			return oddCnt;
		};
	// for odd degree node
	int eulerCnt = 0;
	for (int i = 1; i <= N; ++i)
	{
		if (!visited[i])	
		{
			if (!adjList[i].empty()) // 일단 에지가 존재하는 연결요소여야 함. -> 큰 실수
			{
				const int oddNodeCnt = bfs(i);
				if (oddNodeCnt == 0) // 홀수 차수의 노드가 없다 -> 오일러 회로가 존재.
					eulerCnt++;
				else // 홀수 차수의 노드는 항상 쌍으로 존재함, 따라서 2로 나눠주면 경로의 개수
					eulerCnt += oddNodeCnt / 2;
			}
		}
	}
	std::cout << eulerCnt;
}
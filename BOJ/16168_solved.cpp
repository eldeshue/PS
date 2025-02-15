
/*
	주어진 그래프에 대한 오일러 경로의 존재성 문제.

	오일러 경로란 그래프 내의 모든 에지를 중복 없이 지나는 경로를 뜻함.
	흔히 한 붓 그리기라고 부름.

	주어진 그래프에서 오일러 경로의 존재성을 판단하는 조건은 다음과 같음.

	- 1. 단일 연결 요소
		그래프가 단일 연결 요소여야 모든 에지에 접근할 수 있음.
	- 2. degree
		그래프를 구성하는 노드의 degree가 조건을 만족해야 함.
		
		- 2.1 무향 그래프인 경우
			degree가 홀수인 노드가 없거나(모든 노드에서 시작, 종료 가능, 오일러 회로), 
			단 두 개 존재해야 함(둘이 시작 혹은 끝 노드).

		- 2.2 유향 그래프인 경우
			모든 노드가 in degree와 out degree의 개수가 같거나(오일러 회로)
			out degree가 하나 더 큰 노드(시작)와 in degree가 하나 더 큰 노드(종료) 존제.
			시작, 종료 노드가 여럿 있으면 안됨.

	오일러 경로를 구하기 위해서는 Hierholtzer 알고리즘으로 구함.
*/
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, E, a, b;
	std::cin >> N >> E;
	std::vector<std::vector<int>> graph(N + 1);
	std::vector<int> degree(N + 1, 0);
	std::vector<bool> visited(N + 1, false);
	while (E--)
	{
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}
	auto bfs = [&](int startNode)
		{
			std::queue<int> q;

			visited[startNode] = true;
			q.push(startNode);
			while (!q.empty())
			{
				const int curNode = q.front();
				q.pop();
				for (const int nextNode : graph[curNode])
				{
					if (!visited[nextNode])
					{
						visited[nextNode] = true;
						q.push(nextNode);
					}
				}
			}
		};

	// count connected component
	// 시작 종료 노드 찾기
	const int startNodeCnt = std::accumulate(degree.begin(), degree.end(), 0,
		[](const int acc, const int d)
		{
			return acc + (d % 2);
		});
	// 연결 요소의 개수
	int connectCnt = 0;
	for (int node = 1; node <= N; ++node)
	{
		if (!visited[node])
		{
			connectCnt++;
			bfs(node);
		}
	}
	// result
	if ((startNodeCnt == 0 || startNodeCnt == 2) && connectCnt == 1)
	{
		std::cout << "YES";
	}
	else
	{
		std::cout << "NO";
	}
}
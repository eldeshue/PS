
/*
	�־��� �׷����� ���� ���Ϸ� ����� ���缺 ����.

	���Ϸ� ��ζ� �׷��� ���� ��� ������ �ߺ� ���� ������ ��θ� ����.
	���� �� �� �׸����� �θ�.

	�־��� �׷������� ���Ϸ� ����� ���缺�� �Ǵ��ϴ� ������ ������ ����.

	- 1. ���� ���� ���
		�׷����� ���� ���� ��ҿ��� ��� ������ ������ �� ����.
	- 2. degree
		�׷����� �����ϴ� ����� degree�� ������ �����ؾ� ��.
		
		- 2.1 ���� �׷����� ���
			degree�� Ȧ���� ��尡 ���ų�(��� ��忡�� ����, ���� ����, ���Ϸ� ȸ��), 
			�� �� �� �����ؾ� ��(���� ���� Ȥ�� �� ���).

		- 2.2 ���� �׷����� ���
			��� ��尡 in degree�� out degree�� ������ ���ų�(���Ϸ� ȸ��)
			out degree�� �ϳ� �� ū ���(����)�� in degree�� �ϳ� �� ū ���(����) ����.
			����, ���� ��尡 ���� ������ �ȵ�.

	���Ϸ� ��θ� ���ϱ� ���ؼ��� Hierholtzer �˰������� ����.
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
	// ���� ���� ��� ã��
	const int startNodeCnt = std::accumulate(degree.begin(), degree.end(), 0,
		[](const int acc, const int d)
		{
			return acc + (d % 2);
		});
	// ���� ����� ����
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
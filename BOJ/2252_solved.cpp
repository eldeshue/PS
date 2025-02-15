
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

int numPointed[32001];
std::vector<int> graph[32001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(numPointed, 0, sizeof(numPointed));

	int N, M, p, c;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> p >> c;
		numPointed[c]++;
		graph[p].push_back(c);
	}

	// BFS, topological sort
	std::queue<int> Q;
	for (int i = 1; i <= N; ++i)
	{
		if (numPointed[i] == 0)
		{
			Q.push(i);
		}
	}

	while (!Q.empty())
	{
		int curNode = Q.front();
		Q.pop();

		std::cout << curNode << " ";
		for (const auto nextNode : graph[curNode])
		{
			if (numPointed[nextNode] != 0)
			{
				numPointed[nextNode] --;
				if (numPointed[nextNode] == 0)
				{
					Q.push(nextNode);
				}
			}
		}
	}
}
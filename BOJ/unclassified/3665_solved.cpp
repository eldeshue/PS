
#include <iostream>
#include <vector>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int testNum;
	std::cin >> testNum;
	while (testNum--)
	{
		bool isImpossible = false;
		int N, M, a, b;
		std::cin >> N;
		std::vector<int> nodes(N);
		std::vector<int> freq(N + 1, 0);
		std::vector<std::vector<bool>> graph(N + 1, std::vector<bool>(N + 1, false));
		for (int i = 0; i < N; ++i)
		{
			std::cin >> nodes[i];
			// build graph
			for (int j = 0; j < i; ++j)
			{
				graph[nodes[j]][nodes[i]] = true;
				freq[nodes[i]]++;
			}
		}

		std::cin >> M;
		for (int i = 0; i < M; ++i)
		{
			// reverse edge, flip
			std::cin >> a >> b;
			if (graph[a][b])
			{
				graph[a][b] = false;
				freq[b]--;
				graph[b][a] = true;
				freq[a]++;
			}
			else
			{
				graph[a][b] = true;
				freq[b]++;
				graph[b][a] = false;
				freq[a]--;
			}
		}

		std::vector<int> sortedNodes;
		// topological sort
		std::queue<int> nextNodes;
		for (int i = 1; i <= N; ++i)
		{
			if (freq[i] == 0)
			{
				nextNodes.push(i);
				sortedNodes.push_back(i);
			}
		}
		isImpossible = (nextNodes.size() != 1);
		while (!isImpossible && !nextNodes.empty())
		{
			const int curNode = nextNodes.front();
			nextNodes.pop();
			const int prevNodeCount = nextNodes.size();
			for (int nextNode = 1; nextNode <= N; ++nextNode)
			{
				if (graph[curNode][nextNode])
				{
					if ((--freq[nextNode]) == 0)
					{
						// no inbound, 
						nextNodes.push(nextNode);
						sortedNodes.push_back(nextNode);
					}
				}
			}
			if (prevNodeCount + 1 < nextNodes.size())
			{
				isImpossible = true;
			}
		}

		// there are no ambiguous situation.... wow
		if (isImpossible || sortedNodes.size() != N)
		{
			// after sorting, if there are unordered nodes, IMPOSSIBLE
			std::cout << "IMPOSSIBLE\n";
		}
		else
		{
			// ordered properly
			for (const int n : sortedNodes)
				std::cout << n << ' ';
			std::cout << '\n';
		}
	}
}
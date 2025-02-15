
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

bool visited[32001];
int inDegree[32001];
std::vector<int> graph[32001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(visited, 0, sizeof(visited));
	memset(inDegree, 0, sizeof(inDegree));

	int N, K, a, b;
	std::cin >> N >> K;
	for (int i = 0; i < K; ++i)
	{
		std::cin >> a >> b;
		graph[a].push_back(b);
		inDegree[b]++;
	}

	for (int i = 1, cnt = 0; cnt < N; ++i)
	{
		if (!visited[i] && inDegree[i] == 0)
		{
			visited[i] = true;
			for (const auto& child : graph[i])
			{
				if (inDegree[child] > 0)
				{
					inDegree[child]--;
				}
			}
			std::cout << i << " ";
			cnt++;
			i = 0;
		}

		if (i == N)
		{
			i = 0;
		}
	}
}
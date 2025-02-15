
#include <iostream>
#include <functional>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	std::cin >> N >> M >> K;
	std::vector<std::vector<int>> graph(N + 1, std::vector<int>(N + 1, -1));
	std::vector<std::vector<int>> cache(M + 1, std::vector<int>(N + 1, -1));
	for (int i = 0; i < K; ++i)
	{
		int node1, node2, cost;
		std::cin >> node1 >> node2 >> cost;
		if (node1 < node2 && graph[node1][node2] < cost)
			graph[node1][node2] = cost;
	}

	// dp, tabulation
	cache[1][1] = 0;	// cache[curNode][nodeCnt] = cost
	for (int curCnt = 2; curCnt <= M; ++curCnt)
	{
		const int prevCnt = curCnt - 1;
		for (int curNode = 2; curNode <= N; ++curNode)
		{
			int& curVal = cache[curCnt][curNode];
			for (int prevNode = 1; prevNode < curNode; ++prevNode)
			{
				int& prevVal = cache[prevCnt][prevNode];
				if (prevVal != -1 && graph[prevNode][curNode] != -1)
				{
					curVal
						= std::max(curVal, prevVal + graph[prevNode][curNode]);
				}
			}
		}
	}
	int result = 0;
	for (int n = M; n >= 1; --n)
	{
		result = std::max(result, cache[n][N]);
	}
	std::cout << result;
}
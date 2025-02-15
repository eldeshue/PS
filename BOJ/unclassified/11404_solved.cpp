// Floyd warshall
#include <iostream>

static const long long INF = 4000000000;
long long graph[101][101]; // adj matrix

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, s, e, c;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			graph[i][j] = (i == j) ? 0 : INF;
		}
	}
	for (int i = 1; i <= M; ++i)
	{
		std::cin >> s >> e >> c;
		if (c < graph[s][e])
		{
			graph[s][e] = c;
		}
	}
	// Floyd - Warshall algorithm
	for (int mid = 1; mid <= N; ++mid)
	{
		for (int st = 1; st <= N; ++st)
		{
			if (graph[st][mid] == INF) continue;	// preventing overflow
			for (int ed = 1; ed <= N; ++ed)
			{
				if (graph[mid][ed] == INF) continue;
				// update
				// 계속해서 사이에 끼워넣기, 갱신된 후에는 다시 끼워넣기
				// 일단 이해는 했는데, 굉장히 천재적인 발상이다.
				graph[st][ed] = std::min(graph[st][ed], graph[st][mid] + graph[mid][ed]);
			}
		}
	}
	//
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (graph[i][j] == INF)
			{
				std::cout << "0 ";
			}
			else
			{
				std::cout << graph[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
}
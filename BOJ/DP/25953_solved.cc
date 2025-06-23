
/*
	BOJ 25953. 템포럴 그래프

	시간의 흐름에 따라서 간선의 존재가 바뀌는 그래프가 주어진다.
	한 쌍의 정점 사이의 최단 경로를 구한다.
	이 때, 경로는 시간 순으로 배치되어야 한다.

	N : 정점의 수, 10000
	T : 시간, 1000
	M : 시간 당 간선의 수 : 1000
	=============================================================
	* 에지가 시간에 따라서 변한다
	-> 한 번 에지를 타면, 시간이 흐르고, 다시 돌아갈 수 없다.
	-> 즉, 강제로 DAG가 되어버림. 주어진 그래프가 사실은 tree처럼 사용할 수 있음

	* 왔던 노드를 다시 경유할 필요가 있는가???
	-> 더 적은 cost의 경로를 타고 다시 올 수 있다!
	-> but, graph가 DAG라서 다시 탈 필요가 없다. -> 최적 부분 구조, DP
	=============================================================
	sol 1) vertex split
	주어진 정점을 시간마다 서로 다른 정점으로 판단하고, 트리를 순회.
	정점의 개수가 10^7이 되어 memory 소모가 극심하다.
	-> 보류

	sol 2) no split + binary search + Dijkstra
	요점은 현재 도착 시간 이전의 edge는 재경유하지 않는 것
	따라서 한 vertex에 시간 순으로 edge를 깔고, lower bound를 통해서 경유.
	-> failed. 시간의 흐름에 따라서 그래프가 변한다는 부분이 Dijkstra의 최적해를 보장하지 않는 것으로 보임.

	sol 3) dfs, dp
*/

#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, T, M, S, E;
	std::cin >> N >> T >> M >> S >> E;
	std::vector<std::vector<int>> cache(N, std::vector<int>(T + 1, 2e9));
	cache[S][0] = 0;
	for (int t = 0; t < T; ++t)
	{
		for (int n = 0; n < N; ++n) cache[n][t + 1] = cache[n][t];	// 이전에 이미 도착했다
		for (int m = 0; m < M; ++m)	// 시간 순을 지키면서 경로 update, 이전에 도달했어야 경로에 의미가 있음. 시간 순은 대단히 강력했다
		{
			int v1, v2, w;
			std::cin >> v1 >> v2 >> w;
			cache[v1][t + 1] = std::min(cache[v1][t + 1], cache[v2][t] + w);
			cache[v2][t + 1] = std::min(cache[v2][t + 1], cache[v1][t] + w);
		}
	}

	if (cache[E][T] == 2e9)
		std::cout << -1;
	else
		std::cout << cache[E][T];
}

/*
// failed solution, Dijkstra
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using Edge = std::tuple<int, int, int>; // time, next node, cost
using Graph = std::vector<std::vector<Edge>>;
using Stat = std::tuple<int, int, int>; // cost, time, next node

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, T, M, S, E;
	std::cin >> N >> T >> M >> S >> E;
	Graph g(N);
	for (int t = 0; t < T; ++t)
	{
		for (int m = 0; m < M; ++m)
		{
			int v1, v2, w;
			std::cin >> v1 >> v2 >> w;
			g[v1].push_back(std::make_tuple(t, v2, w));
			g[v2].push_back(std::make_tuple(t, v1, w));
		}
	}

	// Dijkstra
	std::vector<int> cost(N, 2e9);
	std::priority_queue<Stat, std::vector<Stat>, std::greater<Stat>> pq;	// min heap
	cost[S] = 0;
	pq.push(std::make_tuple(0, 0, S));
	while (!pq.empty())
	{
		auto const [cc, ct, cn] = pq.top();
		pq.pop();

		// skip redundant cost
		if (cc > cost[cn])
		{
			continue;
		}

		// skip deprecated edges
		auto itr = std::lower_bound(g[cn].begin(), g[cn].end(), std::make_tuple(ct, 0, 0));
		for (; itr != g[cn].end(); ++itr)
		{
			auto const [t, nn, c] = *itr;
			int const nt = t + 1;
			int const nc = cc + c;
			if (cost[nn] > nc)
			{
				cost[nn] = nc;
				pq.push(std::make_tuple(nc, nt, nn));
			}
		}
	}

	if (cost[E] == 2e9)
		std::cout << -1;
	else
		std::cout << cost[E];
}
*/

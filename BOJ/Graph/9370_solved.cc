
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, M, T, S, G, H;
		int x = 0;
		std::cin >> N >> M >> T >> S >> G >> H;
		if (G > H) std::swap(G, H);
		std::vector<std::vector<pii>> graph(N + 1);
		for (int i = 0; i < M; ++i)
		{
			int a, b, d;
			std::cin >> a >> b >> d;
			if (a > b) std::swap(a, b);
			if (a == G && b == H) x = d;
			graph[a].push_back(std::make_pair(b, d));
			graph[b].push_back(std::make_pair(a, d));
		}

		std::vector<int> candidate(T);
		for (auto& n : candidate) std::cin >> n;
		std::sort(candidate.begin(), candidate.end());

		// Dijkstra
		auto Dijkstra = [&](int const start) {
			std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
			std::vector<int> cost(N + 1, 1e9);
			cost[start] = 0;
			pq.push(std::make_pair(0, start));
			while (!pq.empty())
			{
				// pop
				auto const [curCost, curNode] = pq.top();
				pq.pop();

				// skip
				if (cost[curNode] < curCost) continue;

				// traverse
				for (auto const [nextNode, c] : graph[curNode])
				{
					int const nextCost = curCost + c;
					if (nextCost < cost[nextNode])
					{
						cost[nextNode] = nextCost;
						pq.push(std::make_pair(nextCost, nextNode));
					}
				}
			}
			return cost;
			};
		auto fromS = Dijkstra(S);
		auto fromG = Dijkstra(G);
		auto fromH = Dijkstra(H);

		// back track route
		for (int const target : candidate)
		{
			if ((fromS[G] + x + fromH[target]) == fromS[target] || (fromS[H] + x + fromG[target]) == fromS[target])
			{
				std::cout << target << ' ';
			}
		}
		std::cout << '\n';
	}
}

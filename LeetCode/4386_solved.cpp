
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using Point = std::pair<float, float>;
using Edge = std::pair<float, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<Point> stars(N);
	for (auto& [x, y] : stars)
		std::cin >> x >> y;
	std::vector<std::vector<float>> dist(N, std::vector<float>(N, 0.0f));
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			float const d
				= std::sqrt(std::pow(stars[i].first - stars[j].first, 2)
					+ std::pow(stars[i].second - stars[j].second, 2));
			dist[i][j] = d;
			dist[j][i] = d;
		}
	}

	float sum = 0;
	std::vector<bool> visited(N, false);
	std::priority_queue <Edge, std::vector<Edge>, std::greater<Edge>> pq;
	pq.push(std::make_pair(0.0f, 0));
	while (!pq.empty())
	{
		auto [curCost, curNode] = pq.top();
		pq.pop();
		if (visited[curNode])
			continue;
		visited[curNode] = true;
		sum += curCost;
		for (int nextNode = 0; nextNode < N; ++nextNode)
		{
			if (!visited[nextNode])
			{
				pq.push(std::make_pair(dist[curNode][nextNode], nextNode));
			}
		}
	}
	std::cout << sum;
}
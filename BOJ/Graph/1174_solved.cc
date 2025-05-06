
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <iomanip>

class DisjointSet
{
private:
	DisjointSet() = delete;

	int groupNum;
	std::vector<int> parents;
public:
	DisjointSet(int size) : groupNum(size), parents(size, -1) {}

	int find(int node)
	{
		if (parents[node] < 0)
			return node;
		return parents[node] = find(parents[node]);
	}

	void unite(int n1, int n2)
	{
		n1 = find(n1);
		n2 = find(n2);

		if (n1 == n2) return;

		--groupNum;
		if (parents[n1] < parents[n2])
		{
			parents[n1] += parents[n2];
			parents[n2] = n1;
		}
		else
		{
			parents[n2] += parents[n1];
			parents[n1] = n2;
		}
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;
	using Point = std::pair<ll, ll>;
	using Edge = std::tuple<ll, int, int>;

	int N, M;
	std::cin >> N >> M;
	std::vector<Point> coordinates(N, { 0, 0 });
	for (auto& [x, y] : coordinates)
		std::cin >> x >> y;

	DisjointSet uf(N);
	for (int _ = 0; _ < M; ++_)
	{
		int n1, n2;
		std::cin >> n1 >> n2;
		uf.unite(n1, n2);
	}

	std::vector<Edge> edges;
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			edges.push_back(Edge(
				std::pow(coordinates[i].first - coordinates[j].first, 2) + std::pow(coordinates[i].second - coordinates[j].second, 2),
				i + 1, j + 1));
		}
	}
	std::sort(edges.begin(), edges.end());

	double result = 0;
	for (auto const [cost, n1, n2] : edges)
	{
		if (uf.find(n1) != uf.find(n2))
		{
			result += std::sqrt(cost);
			uf.unite(n1, n2);
		}
	}
	std::cout << std::fixed << std::setprecision(2) << result;
}



/*
	BOJ 2637
*/
#include <iostream>
#include <vector>

using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<Edge>>;
using Table = std::vector<std::vector<int>>;

int N, M;

void memoize(Graph const& g, Table& t, std::vector<bool>& v, int const cur_node)
{
	// leaf
	if (g[cur_node].empty())
	{
		t[cur_node][cur_node] = 1;
		return;
	}

	// non-leaf
	for (auto const [next_node, coef] : g[cur_node])
	{
		if (!v[next_node])
		{
			v[next_node] = true;
			memoize(g, t, v, next_node);
		}
		for (int i = 0; i <= N; ++i)
		{
			t[cur_node][i] += t[next_node][i] * coef;
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	std::cin >> N >> M;
	Graph g(N + 1);
	for (int i = 0; i < M; ++i)
	{
		// for x, need y for k ea
		int x, y, k;
		std::cin >> x >> y >> k;
		g[x].push_back(Edge(y, k));
	}

	// dp, dfs
	Table counts(N + 1, std::vector<int>(N + 1, 0));
	std::vector<bool> visited(N + 1, false);
	memoize(g, counts, visited, N);

	// print
	for (int i = 1; i <= N; ++i)
	{
		if (counts[N][i] > 0)
			std::cout << i << ' ' << counts[N][i] << '\n';
	}
}
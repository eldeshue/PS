/*
	BOJ 20303

	union-find + 01 knapsack

	조합이 흥미롭지만, 큰 고찰이 필요하진 않아서 평범했던 문제.
*/
#include <iostream>
#include <vector>

struct UnionFind {
	std::vector<int> parents;
	UnionFind(size_t size) : parents(size, -1) {}

	int find(int node) {
		if (parents[node] < 0)
			return node;
		return parents[node] = find(parents[node]);
	}
	void unite(int node1, int node2, std::vector<int>& candy) {
		node1 = find(node1);
		node2 = find(node2);

		if (node1 == node2)
			return;

		// union by size
		if (parents[node1] <= parents[node2]) {
			parents[node1] += parents[node2];
			parents[node2] = node1;
			candy[node1] += candy[node2];
			candy[node2] = -1;
		}
		else // (parents[node1] > parents[node2]) 
		{
			parents[node2] += parents[node1];
			parents[node1] = node2;
			candy[node2] += candy[node1];
			candy[node1] = -1;
		}
	}
	bool is_same_group(int node1, int node2)
	{
		node1 = find(node1);
		node2 = find(node2);

		return (node1 == node2);
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M, K;
	std::cin >> N >> M >> K;
	UnionFind uf(N + 1);
	std::vector<int> candy(N + 1, 0);
	for (int i = 1; i <= N; ++i)
		std::cin >> candy[i];
	for (int i = 0; i < M; ++i) {
		int n1, n2;
		std::cin >> n1 >> n2;
		uf.unite(n1, n2, candy);
	}

	// get groups
	using pii = std::pair<int, int>;
	std::vector<pii> groups;
	for (int i = 1; i <= N; ++i)
	{
		if (!uf.is_same_group(0, i)) {
			int root = uf.find(i);
			groups.push_back(std::make_pair(-uf.parents[root], candy[root]));
			uf.unite(0, root, candy);
		}

	}

	// dp, 01 knapsack
	std::vector<int> cache(30001, -1);
	cache[0] = 0;
	for (auto const [num_cry, num_candy] : groups) {
		for (int i = K - num_cry; i >= 0; --i) {
			if (cache[i] != -1) {
				cache[i + num_cry]
					= std::max(cache[i + num_cry], cache[i] + num_candy);
			}
		}
	}

	// get result
	int result = 0;
	for (int i = 0; i < K; ++i)
		result = std::max(result, cache[i]);

	// print
	std::cout << result;
}

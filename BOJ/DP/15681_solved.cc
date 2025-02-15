
#include <iostream>
#include <numeric>
#include <vector>

int dfs(const std::vector<std::vector<int>> &tree, std::vector<int> &cache, int curNode, int prevNode)
{
	for (const int &nextNode : tree[curNode])
	{
		if (nextNode != prevNode)
			cache[curNode] += dfs(tree, cache, nextNode, curNode);
	}
	return ++cache[curNode];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, R, Q, U, V;
	std::cin >> N >> R >> Q;
	// build tree
	std::vector<std::vector<int>> tree(N + 1, std::vector<int>());
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> U >> V;
		tree[U].push_back(V);
		tree[V].push_back(U);
	}
	// set cache
	std::vector<int> cache(N + 1, 0);
	dfs(tree, cache, R, 0);
	// query
	int q;
	for (int i = 0; i < Q; ++i)
	{
		std::cin >> q;
		std::cout << cache[q] << '\n';
	}
}

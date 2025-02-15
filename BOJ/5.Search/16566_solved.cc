
#include <iostream>
#include <algorithm>
#include <vector>

// union-find
int find(std::vector<int> &ds, int node)
{
	if (ds[node] < 0) // base case
		return node;
	return ds[node] = find(ds, ds[node]); // path compression
}

void uniteRight(std::vector<int> &ds, int lNode, int rNode)
{
	lNode = find(ds, lNode);
	rNode = find(ds, rNode);

	if (lNode == rNode)
		return;
	ds[lNode] = rNode;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	std::cin >> N >> M >> K;
	std::vector<int> disjointSet(N + 2, -1);
	std::vector<int> hands(M);
	for (int i = 0; i < M; ++i)
		std::cin >> hands[i];
	std::sort(hands.begin(), hands.end());

	// build disjoint set
	int prevStart = 1;
	for (const int card : hands)
	{
		for (int i = prevStart; i < card; ++i)
			disjointSet[i] = card;
		prevStart = card + 1;
	}

	// search
	int query, result;
	for (int i = 0; i < K; ++i)
	{
		std::cin >> query;

		// 값은 이분 탐색(lower bound)로 획득, lower_bound( query + 1 );
		result = *std::lower_bound(hands.begin(), hands.end(), query + 1);
		result = find(disjointSet, result);

		// update right
		uniteRight(disjointSet, result, result + 1);
		//		uniteRight(disjointSet, result - 1, result);
		std::cout << result << '\n';
	}
}

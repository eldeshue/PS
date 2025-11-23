/*
	BOJ 22954

	서로 다른 크기의 두 트리로 분할하기

	서로 다른 크기를 어떻게 구현하지?

	==========================================

	일단 크루스칼을 돌려서 컴포넌트가 2개 남을 때 까지 진행함.

	만약 두 컴포넌트의 크기가 같다면, 기존의 엣지를 하나 대체하면 됨.

	대체하는 엣지는 탐색하지 않은 엣지 중에서 두 연결 요소를 하나로 합치는 엣지임.

	이 엣지로 그래프를 다시 build하면 됨.

	union find를 쓸 것이기 때문에, re-build의 비용이 여전히 O(M)임.
*/
#include <iostream>
#include <vector>
#include <functional>
using Edge = std::pair<int, int>;
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N >> M;	// N : number of nodes, M : number of edges
	std::vector<Edge> edges(M);
	for (auto& [n1, n2] : edges) // given edges
		std::cin >> n1 >> n2;

	// define union find
	std::vector<int> disjoint_set(N + 1, -1);
	int num_cc = N;
	std::function<int(int const)> find = [&](int const node) -> int {
		if (disjoint_set[node] < 0)
		{
			return node;
		}
		return disjoint_set[node] = find(disjoint_set[node]);
		};
	auto unite = [&](int node1, int node2) {
		node1 = find(node1);
		node2 = find(node2);

		if (node1 == node2)
			return;
		num_cc--;
		if (disjoint_set[node1] <= disjoint_set[node2])	// union by size
		{
			disjoint_set[node1] += disjoint_set[node2];
			disjoint_set[node2] = node1;
		}
		else
		{
			disjoint_set[node2] += disjoint_set[node1];
			disjoint_set[node1] = node2;
		}
		};

	// like kruskal algorithm
	// unite until number of connected-components are 2
	std::vector<int> used_edge_idx;
	for (int i = 0; i < M; ++i)
	{
		if (num_cc <= 2)
			break;
		auto [n1, n2] = edges[i];
		if (find(n1) != find(n2))
		{
			unite(n1, n2);
			used_edge_idx.push_back(i);
		}
	}
	if (num_cc != 2 || N <= 2)
	{
		std::cout << -1;
		return 0;
	}

	// find root
	int root1 = 0, root2 = 0;
	for (int n = 1; n <= N; ++n)
	{
		if (disjoint_set[n] < 0)
		{
			if (root1 == 0)
			{
				root1 = n;
			}
			else
			{
				root2 = n;
			}
		}
	}

	// size of each component are same, failed
	// rebuild graph
	if (num_cc == 2 && disjoint_set[root1] == disjoint_set[root2])
	{
		// find another edge
		for (int i = M - 1; i >= 0; --i)
		{
			auto [n1, n2] = edges[i];
			if (find(n1) != find(n2))
			{
				used_edge_idx[0] = i;	// change edge
				break;
			}
		}

		// rebuild
		std::fill(disjoint_set.begin(), disjoint_set.end(), -1);
		num_cc = N;
		for (int i : used_edge_idx)
		{
			auto [n1, n2] = edges[i];
			unite(n1, n2);
		}
	}

	// to print result, traverse disjoint set
	// check nodes, O(N)
	for (int n = 1; n <= N; ++n)
		find(n); // path compression

	int first_cc_color = find(1);

	std::vector<int> n1, n2;
	for (int n = 1; n <= N; ++n)
	{
		if (disjoint_set[n] == first_cc_color || n == first_cc_color)
		{
			n1.push_back(n);
		}
		else
		{
			n2.push_back(n);
		}
	}

	// check edges, O(M)
	std::vector<int> e1, e2;
	for (auto i : used_edge_idx)
	{
		auto [n1, n2] = edges[i];
		if (find(n1) == first_cc_color)
			e1.push_back(i + 1);
		else
			e2.push_back(i + 1);
	}

	// print result
	if (num_cc != 2 || n1.size() == n2.size())
	{
		std::cout << -1;
		return 0;
	}
	std::cout << n1.size() << ' ' << n2.size() << '\n';
	for (auto n : n1)
	{
		std::cout << n << ' ';
	}
	std::cout << '\n';
	for (auto e : e1)
	{
		std::cout << e << ' ';
	}
	std::cout << '\n';
	for (auto n : n2)
	{
		std::cout << n << ' ';
	}
	std::cout << '\n';
	for (auto e : e2)
	{
		std::cout << e << ' ';
	}
	std::cout << '\n';
}

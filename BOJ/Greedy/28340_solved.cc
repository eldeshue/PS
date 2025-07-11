
/*
	BOJ 28340

	허프만 코딩을 k진법으로 확장하기.

	==========================================
	문제의 핵심은 ghost node의 추가.
	이는 k진-huffman tree를 만들 때, 불완전 트리가 생김으로 인한 문제로,
	완전 k진 트리가 나오도록 가중치 0인 고스트 노드를 필요로 함.

	ghost node를 추가하지 않으면, 최종적으로 pq에 1개가 남지 않을 수 있게 됨.
	이 경우 불필요하게 많은

	한 번 tree로 묶을 때 마다 k-1개의 원소가 사라짐. 최종적으로 leaf node의 수를 1 + (K - 1)개의 배수가 되도록 해야 함.
	이렇게 leaf node의 수를 맞춰주면, 반드시 root노드 1 개가 남음.

	=========================================
	advanced solution

	실제 허프만 트리를 순회할 필요가 없다.
	왜냐 하면, pq를 출입할 때 마다 허프만 트리에서의 depth가 1씩 증가한다.
	따라서, pq를 출입하는 횟수만큼 가중치가 늘어나는 효과가 발생한다.
*/
// 허프만 트리를 순회하지 않는 솔루션.
#include <iostream>
#include <vector>
#include <queue>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, K;
		std::cin >> N >> K;
		int const len = [&]() -> int {	// calculate len after adding ghost nodes
			int result = 1;
			while (result < N)
			{
				result += K - 1;
			}
			return result;
			}();
		std::vector<ll> freq(len, 0);	// freq of ghost nodes are 0
		for (int i = 0; i < N; ++i)	// non-ghost leaf nodes
			std::cin >> freq[i];

		// min heap
		std::priority_queue<ll, std::vector<ll>, std::greater<ll>> pq;
		for (int i = 0; i < len; ++i)
			pq.push(freq[i]);

		ll result = 0;
		while (pq.size() > 1)
		{
			ll tmp = 0;
			for (int _ = 0; _ < K; ++_)
			{
				tmp += pq.top();
				pq.pop();
			}
			result += tmp;
			pq.push(tmp);
		}
		std::cout << result << '\n';
	}
}


/*
// 실제 허프만 트리를 구하고, dfs로 순회하는 솔루션.
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using ll = long long;
using HuffmanStat = std::pair<ll, int>;	// freq, symbol

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, K;
		std::cin >> N >> K;
		int const len = [&]() -> int {	// calculate len after adding ghost nodes
			int result = 1;
			while (result < N)
			{
				result += K - 1;
			}
			return result;
			}();
		std::vector<ll> freq(len, 0);	// freq of ghost nodes are 0
		for (int i = 0; i < N; ++i)	// non-ghost leaf nodes
			std::cin >> freq[i];

		// min heap
		std::priority_queue<HuffmanStat, std::vector<HuffmanStat>, std::greater<HuffmanStat>> pq;
		for (int i = 0; i < len; ++i)
			pq.push(std::make_pair(freq[i], i));

		// build huffman tree
		std::vector<std::vector<int>> graph(len);	// 0~len leafs(0~N non ghost), else is intermediate node, last is root
		auto build_new_parent = [&](int const child_num) {
			// invariant : all the node in pq are already in the graph
			int const new_id = graph.size();

			// make new root of sub-tree
			graph.push_back(std::vector<int>());

			// pop k or less nodes from pq
			ll new_freq = 0;
			for (int _ = 0; _ < child_num; ++_)
			{
				new_freq += pq.top().first;
				graph[new_id].push_back(pq.top().second);
				pq.pop();
			}

			// push it back to the pq
			pq.push(std::make_pair(new_freq, new_id));
			};
		while (pq.size() >= K)
			build_new_parent(K);

		// dfs huffman tree, collect result
		ll result = 0;
		std::function<void(int, int)> dfs = [&](int node, int depth) {
			if (graph[node].empty())
			{
				// root
				result += freq[node] * depth;
				return;
			}

			// non root
			for (auto const next : graph[node])
			{
				dfs(next, depth + 1);
			}
			};
		dfs(graph.size() - 1, 0);

		// print
		std::cout << result << '\n';
	}
}


*/

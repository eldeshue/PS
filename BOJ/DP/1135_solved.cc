
#include <iostream>
#include <vector>
#include <algorithm>

int dp(const std::vector<std::vector<int>> &graph, int curNode) // subtree의 solution을 재활용하므로 dp
{
	if (graph[curNode].empty()) // leaf
	{
		return 0;
	}
	// get result of subtree;
	std::vector<int> cache(graph[curNode].size());
	for (int i = 0; i < cache.size(); ++i)
	{
		cache[i] = dp(graph, graph[curNode][i]);
	}
	// sort, 최대 부분결과가 최소가 되도록 해야 함.
	std::sort(cache.begin(), cache.end()); // n log n인데, dp함수는 중복 없이 모든 노드에 대해서 실행됨, 즉 전체 다 합쳐서 n log n
	// get max time as partial result;
	int result = 0;
	for (int i = cache.size() - 1; i >= 0; --i)
	{
		result = std::max(result, i + 1 + cache[cache.size() - 1 - i]); // 트리의 부분 결과마다 가중치가 붙는데, 그 결과가 최소가 될려면
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, parent;
	std::cin >> N;
	std::vector<std::vector<int>> graph(N);
	std::cin >> parent;
	for (int child = 1; child < N; ++child)
	{
		std::cin >> parent;
		graph[parent].push_back(child);
	}
	std::cout << dp(graph, 0);
}

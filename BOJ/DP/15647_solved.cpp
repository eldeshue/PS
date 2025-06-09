
/*
	boj 15647

	노드 별 거리의 총 합을 구하기.

	한 노드에서 다른 모든 노드를 향하는 거리의 합을 구하는데,
	이를 모든 노드에 대해서 구해야 함을 의미한다.

	주어진 그래프 상황이 트리이므로, 경로는 하나만 존재한다. 따라서 하나로 결정됨.

	======================================================================

	1번 노드를 root로 삼아서 모든 노드에 대한 비용 총 합을 계산한다.

	이후 tree를 순회하면서 비용 총 합을 조정하도록 한다.

	일단 subtree에 존재하는 노드의 개수를 저장, 이들을 반영한다.

	즉 root를 이동할 때 루트로 부터 다른 노드를 향하는 모든 경로의 cost 총 합은
	어떻게 업데이트 될 까?
*/
#include <iostream>
#include <vector>
#include <functional>

using ll = long long;
using Edge = std::pair<int, ll>;
using Graph = std::vector<std::vector<Edge>>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	Graph g(N + 1);
	for (int i = 0; i < N - 1; ++i) {
		int u, v;
		ll d;
		std::cin >> u >> v >> d;
		g[u].push_back(Edge(v, d));
		g[v].push_back(Edge(u, d));
	}

	// dfs, tree traversal
	// accumulate total dist from root
	// count subtree size
	ll total_dist_sum = 0;
	std::vector<int> subtree_size(N + 1, 0);
	std::vector<bool> visited(N + 1, false);
	std::function<int(int, ll)> dfs_collect_sum = [&](int cur_node, ll cur_dist) -> int {
		int cur_subtree_node_cnt = 1;

		for (auto const [next_node, dist] : g[cur_node]) {
			if (!visited[next_node]) {
				visited[next_node] = true;
				total_dist_sum += cur_dist + dist;
				cur_subtree_node_cnt += dfs_collect_sum(next_node, cur_dist + dist);
			}
		}
		return subtree_size[cur_node] = cur_subtree_node_cnt;
		};
	visited[1] = true;
	dfs_collect_sum(1, 0);

	// back tracking, update total_dist_sum with different root
	std::fill(visited.begin(), visited.end(), false);
	std::vector<ll> result(N + 1, 0);
	std::function<void(int)> dfs_dp = [&](int cur_node) {

		for (auto const [next_node, dist] : g[cur_node]) {
			if (!visited[next_node]) {
				visited[next_node] = true;

				// edge를 하나 건널 때 마다 total_dist_sum에 
				// 해당 edge를 포함하는 경로의 개수 만큼 update가 발생함.
				// dist * ((N - subtree_size[next_node]) - subtree_size[next_node])
				total_dist_sum += dist * (N - 2LL * subtree_size[next_node]);
				// back track
				result[next_node] = total_dist_sum;
				dfs_dp(next_node);
				// roll back
				total_dist_sum -= dist * (N - 2LL * subtree_size[next_node]);
			}
		}
		};
	visited[1] = true;
	result[1] = total_dist_sum;
	dfs_dp(1);

	// print result
	for (int i = 1; i <= N; ++i)
		std::cout << result[i] << '\n';
}
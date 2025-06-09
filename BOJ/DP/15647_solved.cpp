
/*
	boj 15647

	��� �� �Ÿ��� �� ���� ���ϱ�.

	�� ��忡�� �ٸ� ��� ��带 ���ϴ� �Ÿ��� ���� ���ϴµ�,
	�̸� ��� ��忡 ���ؼ� ���ؾ� ���� �ǹ��Ѵ�.

	�־��� �׷��� ��Ȳ�� Ʈ���̹Ƿ�, ��δ� �ϳ��� �����Ѵ�. ���� �ϳ��� ������.

	======================================================================

	1�� ��带 root�� ��Ƽ� ��� ��忡 ���� ��� �� ���� ����Ѵ�.

	���� tree�� ��ȸ�ϸ鼭 ��� �� ���� �����ϵ��� �Ѵ�.

	�ϴ� subtree�� �����ϴ� ����� ������ ����, �̵��� �ݿ��Ѵ�.

	�� root�� �̵��� �� ��Ʈ�� ���� �ٸ� ��带 ���ϴ� ��� ����� cost �� ����
	��� ������Ʈ �� ��?
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

				// edge�� �ϳ� �ǳ� �� ���� total_dist_sum�� 
				// �ش� edge�� �����ϴ� ����� ���� ��ŭ update�� �߻���.
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
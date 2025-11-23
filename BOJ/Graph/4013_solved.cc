/*
	BOJ 4013

	주어진 그래프에 대하여 SCC를 돌려서 dag로 그래프를 압축한 다음,
	dfs를 한 번 더 돌려서 최대 value의 path를 얻으면 되겠다.

	dag로 만들어야 하는 이유는 간단하다.
	현재 문제에서는 방문한 노드를 재방문할 수 있으므로,
	사이클의 존재로 인한 경로 복잡성을 제거하기 위함이다.

	그러나, 여전히 같은 노드를 향하는 서로 다른 경로는 존재할 수 있다.

	1 2

	2 3

	1 4

	4 3

	이 경우에 1->3으로 가는 경로는 두 개가 된다.
	따라서 둘 중 보다 나은 비용을 내는 결과가 구분될 수 있다.

	=====================================================

	scc로 정리된 dag를 순회하는 방법에 대해서 고민한다.
	당면한 생각으로는 위상 정렬을 생각했다.

	우리의 목표인 s를 제외한 모든 root를 제외하고 위상정렬을 다 수행한 다음,
	s에서 출발하는 위상정렬을 다시 한 번 수행한다.

	이를 통해서 시간 복잡도를 줄이고, 정확하게 출발 위치에서만 제한되는 경로를 얻을 수 있다.
*/
#include <iostream>

#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>

#include <queue>

class TarjanSolver
{
private:
	TarjanSolver() = delete;
	TarjanSolver(const TarjanSolver&) = delete;
	TarjanSolver& operator=(const TarjanSolver&) = delete;

	using Graph = std::vector<std::vector<int>>;

	const Graph& graph;	// graph, adjacent list
	const int N;	// number of nodes
	int order;		// order of node to visit
	int curSccNum;	// count number of scc group

	std::stack<int> st;	// stack for tarjan algorithm

	std::vector<int> sccGroupNum;	// saving id of scc per node
	std::vector<bool> collected;	// identify the node is collected as scc or not

	int dfs(int node)
	{
		int ans = sccGroupNum[node] = ++order;
		st.push(node);

		// search through children
		for (const int childNode : graph[node])
		{
			if (sccGroupNum[childNode] == 0)	// not visited, search
				ans = std::min(ans, dfs(childNode));
			else if (!collected[childNode])	// visited but not collected
				ans = std::min(ans, sccGroupNum[childNode]);
		}

		// compare with current status
		// if the value of visited[node] is equal with the ans
		// means this 'node' is part of scc
		if (ans == sccGroupNum[node])
		{
			++curSccNum;	// scc found, increase
			while (true)
			{
				int top = st.top();
				st.pop();
				sccGroupNum[top] = curSccNum;
				collected[top] = true;	// check the node as collected

				if (top == node)	// meet self, end of scc
					break;
			}
		}
		return ans;
	}

public:
	TarjanSolver(const Graph& g)
		: graph(g), N(g.size()), order(0), curSccNum(0),
		sccGroupNum(N, 0), collected(N, false)
	{
		// run tarjan algorithm, 1-based
		for (int node = 1; node < N; ++node)
			if (sccGroupNum[node] == 0)
				dfs(node);
	}

	bool _2sat()
	{
		const int offset = N / 2;
		for (int i = 1; i <= offset; ++i)
		{
			if (sccGroupNum[i] == sccGroupNum[i + offset])
				return false;
		}
		return true;
	}

	std::vector<int> _2satResult()
	{
		// topological sort
		// because of the Tarjan algorithm,
		// the order of the nodes are already setted.
		// higher the node id, lower topology value
		// set result combination of 2-sat
		// mark the node false, meeting first
		const int offset = N / 2;
		std::vector<int> result(offset + 1, -1);

		for (int i = 1; i <= offset; ++i)
			result[i] = (sccGroupNum[i] < sccGroupNum[i + offset]);
		return result;
	}

	int _queryGroupId(int const node) {
		return sccGroupNum[node];
	}

	Graph _getDagOfScc() {
		// list of edges
		// to exclude duplicated edges, use hash set
		std::vector<std::unordered_set<int>> adj_list_scc(curSccNum + 1);
		for (int from = 1; from < N; ++from)
		{
			int const fromScc = sccGroupNum[from];
			for (int const to : graph[from])
			{
				int const toScc = sccGroupNum[to];
				if (fromScc != toScc)
				{
					adj_list_scc[fromScc].insert(toScc);
				}
			}
		}

		// transform
		Graph result(curSccNum + 1);
		std::transform(adj_list_scc.begin(), adj_list_scc.end(), result.begin(),
			[](std::unordered_set<int> const& list) {
				return std::vector<int>(list.begin(), list.end());
			});
		return result;
	}
};

using Graph = std::vector<std::vector<int>>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N >> M;
	Graph g(N + 1);
	for (int i = 0; i < M; ++i)
	{
		int s, e;
		std::cin >> s >> e;
		g[s].push_back(e);
	}
	// preprocessing, compress graph
	TarjanSolver ts(g);
	g = ts._getDagOfScc();	// 0-indexed graph

	std::vector<int> money(g.size(), 0);
	for (int i = 1; i <= N; ++i)
	{
		int m;
		std::cin >> m;
		money[ts._queryGroupId(i)] += m;
	}
	int S, P;
	std::cin >> S >> P;
	std::vector<bool> is_rstrt(g.size(), false);
	for (int i = 0; i < P; ++i)
	{
		int node;
		std::cin >> node;
		is_rstrt[ts._queryGroupId(node)] = true;
	}

	// topological sort to dag
	// count ref of nodes
	std::vector<int> in_count(g.size(), 0);
	for (auto const& row : g)
	{
		for (auto const node : row)
		{
			in_count[node]++;
		}
	}

	// topological sort, calc result
	auto topological_sort = [&](int const skip_node) -> int {
		// 중복 경로의 영향을 제거하기 위해 위상정렬 수행
		// 중복 경로에 따른 최댓값 유지를 위해서 최댓값만 저장하는 DP를 수행
		std::vector<int> cache(g.size(), 0);

		std::queue<int> q;
		for (int node = 0; node < g.size(); ++node)
		{
			if (in_count[node] == 0 && node != skip_node)
				q.push(node);
		}

		int result = 0;
		while (!q.empty())
		{
			int const cur_node = q.front();
			q.pop();
			cache[cur_node] += money[cur_node];
			in_count[cur_node] = -1;	// visited, 다음 위상정렬에서 재방문 막기
			if (is_rstrt[cur_node])
				result = std::max(result, cache[cur_node]);

			for (int const next_node : g[cur_node])
			{
				--in_count[next_node];
				cache[next_node] = std::max(cache[next_node], cache[cur_node]);
				if (in_count[next_node] == 0 && next_node != skip_node)
				{
					q.push(next_node);
				}
			}
		}
		return result;
		};
	// 먼저 위상정렬을 한 번 수행해서 시작점 S 이전 노드에서 출발하는 경로의 영향을 모두 제거
	topological_sort(ts._queryGroupId(S));
	// 이후 위상정렬을 한 번 더 수행, S에서 시작하는 경로들만 검사함.
	std::cout << topological_sort(-1);
}


/*
	BOJ 4196

	도미노 문제, 도미노의 개수 N, 도미노 사이의 연결 관계 M
	 각각 100K

	 도미노를 노드, 관계를 에지로 하는 그래프 문제
	 도미노가 넘어지기 위한 단뱡향 관계, 단방향 edge임.

	 문제에서 요구하는 것은, 최소 몇 개의 도미노를 쓰러뜨려야 전부 넘길 수 있느냐

	 =========================

	 scc를 구하지 않고도 문제를 풀 수 있지 않을까 싶어서
	 dfs와 inlet count만 준비해서 풀이에 도전함

	 먼저 in count가 0인 노드들을 시작으로 dfs를 수행하여 그래프를 지운 후
	 남은 노드들에 대해서 그냥 dfs를 수행했음.

	 여기서 반례가 등장하는데, 바로 두 사이클이 하나의 에지로 연결되는 경우임.

	 이 경우는 사이클이 일종의 root 노드가 되는 경우라서 식별이 불가능함.

	 =============================

	 결국 scc를 돌려서 그래프를 단축해야 함.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <stack>

#include <unordered_set>
#include <algorithm>

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

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, M;
		std::cin >> N >> M;
		Graph g(N + 1);
		for (int i = 0; i < M; ++i)
		{
			int from, to;
			std::cin >> from >> to;
			g[from].push_back(to);
		}

		// tarjan algorithm
		// find scc and reduce the graph
		TarjanSolver ts(g);
		Graph dag = ts._getDagOfScc();	// O(M)

		// traverse dag, count in order of nodes
		// O(M)
		int const num_scc = dag.size() - 1;
		std::vector<int> in_cnt(num_scc + 1, 0);
		for (int node = 1; node <= num_scc; ++node)
		{
			for (int const to : dag[node])
			{
				in_cnt[to]++;
			}
		}

		// count number of root in dag
		// root's in count is 0
		int result = 0;
		for (int i = 1; i < in_cnt.size(); ++i)
		{
			result += (in_cnt[i] == 0);
		}
		std::cout << result << '\n';
	}
}

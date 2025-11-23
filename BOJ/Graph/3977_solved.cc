/*
	BOJ 3977

	scc로 그래프를 dag로 만든 다음, 단 하나의 root를 찾는다.

	만약 root가 여럿이라면, confused

	만약 root가 하나라면, 해당 root를 scc로 갖는 모든 노드를 출력하도록 함.
*/

#include <iostream>

#include <vector>
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

	std::vector<int> _getSccGroupID() {
		return sccGroupNum;
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
			from++; to++;
			g[from].push_back(to);
		}

		// solve 
		TarjanSolver solver(g);
		Graph dag = solver._getDagOfScc();
		std::vector<int> sccId = solver._getSccGroupID();

		// find unique root
		std::vector<int> out_cnt(dag.size(), 0);
		for (auto const& vec : dag)
		{
			for (auto const node : vec)
			{
				out_cnt[node]++;
			}
		}
		int root_cnt = 0;
		int root = 0;
		for (int i = 1; i < dag.size(); ++i)
		{
			if (out_cnt[i] == 0)
			{
				root_cnt++;
				root = i;
			}
		}

		// print
		if (root_cnt == 1)
		{
			for (int i = 1; i <= N; ++i)
			{
				if (sccId[i] == root)
				{
					std::cout << i - 1 << '\n';
				}
			}
		}
		else
		{
			std::cout << "Confused\n";
		}
		std::cout << '\n';
	}
}

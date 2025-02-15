
#include <iostream>
#include <vector>
#include <stack>

class TarjanSolver
{
private:
	TarjanSolver();
	TarjanSolver(const TarjanSolver&);
	TarjanSolver& operator=(const TarjanSolver&);

	using Graph = std::vector<std::vector<int>>;

	const Graph& graph;	// graph, adjacent list
	const int N;	// number of nodes
	int order;		// order of node to visit

	std::stack<int> st;	// stack for tarjan algorithm

	std::vector<int> visited;	// vector for saving id of scc
	std::vector<bool> scc;		// ???

	int dfs(int node)
	{
		int ans = visited[node] = ++order;
		st.push(node);
		// search through children
		for (const int childNode : graph[node])
		{
			if (visited[childNode] == 0)	// not visited, search
				ans = std::min(ans, dfs(childNode));
			else if (!scc[childNode])	// visited but not collected as part of scc
				ans = std::min(ans, visited[childNode]);
		}
		// compare with current status
		// if the value of visited[node] is equal with the ans
		// means this 'node' is part of scc
		if (ans == visited[node])
		{
			while (true)
			{
				int top = st.top();
				st.pop();
				visited[top] = ans;
				scc[top] = true;	// check the node is collected

				if (top == node)	// meet self, end of scc
					break;
			}
		}
		return ans;
	}

public:
	TarjanSolver(const Graph& g)
		: graph(g), N(g.size()), order(0), visited(N, 0), scc(N, false)
	{
		// run tarjan algorithm
		for (int node = 1; node < N; ++node)
			if (visited[node] == 0)
				dfs(node);
	}
	bool _2sat()	// 2-SAT, satisfiability.
	{
		const int offset = N / 2;
		for (int i = 1; i <= offset; ++i)
		{
			if (visited[i] == visited[i + offset])
				return false;
		}
		return true;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	/*
		normal bool value : 1 ~ N
		opposite bool balue : N + 1 ~ 2N

		if (N > 0)
			opposite(N) == normal + N
	*/
	int N, M, i, j;
	auto opposite = [&](int n)
		{
			if (n < 0)
				return -n;
			return N + n;
		};
	auto convert = [&](int n)
		{
			if (n < 0)
				return N - n;
			return n;
		};
	std::cin >> N >> M;
	std::vector<std::vector<int>> adjList(2 * N + 1);
	for (int n = 0; n < M; ++n)
	{
		std::cin >> i >> j;
		adjList[opposite(i)].push_back(convert(j));
		adjList[opposite(j)].push_back(convert(i));
	}
	TarjanSolver s(adjList);
	std::cout << s._2sat();
}
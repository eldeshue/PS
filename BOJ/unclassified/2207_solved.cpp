
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
		// run tarjan algorithm
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
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, i, j;
	auto opposite = [&](int n)
		{
			if (n < 0)
				return -n;
			return M + n;
		};
	auto convert = [&](int n)
		{
			if (n < 0)
				return M - n;
			return n;
		};
	std::cin >> N >> M;
	std::vector<std::vector<int>> adjList(2 * M + 1);
	for (int n = 0; n < N; ++n)
	{
		std::cin >> i >> j;
		adjList[opposite(i)].push_back(convert(j));
		adjList[opposite(j)].push_back(convert(i));
	}
	TarjanSolver s(adjList);
	if (s._2sat())
	{
		std::cout << "^_^";
	}
	else
	{
		std::cout << "OTL";
	}
}
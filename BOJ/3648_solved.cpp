
/*
	특정 노드가 반드시 참이 되는 2-sat를 얻고 싶다.

	기존의 그래프에 추가적인 clause를 가해서 조건을 추가함.
*/
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

	// N : number of bol statement
	// M : number of clause 
	int N, M, a, b;
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
	while (std::cin >> N >> M)
	{
		std::vector<std::vector<int>> g(2 * N + 1);
		// input, build graph
		for (int i = 0; i < M; ++i)
		{
			std::cin >> a >> b;
			g[opposite(a)].push_back(convert(b));
			g[opposite(b)].push_back(convert(a));
		}
		/*
		// SOLUTION 

		// node '1' must be true. so add another clause
		// 1번 노드가 반드시 참이되는 조건이 필요함.
		// 따라서 기존의 그래프에 임의로 절을 하나 추가하여 조정된 그래프를 만들어야 함
		// (node1 OR node1)
		// 이는 곧 2-SAT의 정의에 의해 모순이 없이 성립하려면 반드시 node1이 참이 되어야 함.
		// 그렇지 않다면 모순이 발생한 것.
		*/
		g[opposite(1)].push_back(convert(1));

		// solve
		TarjanSolver s(g);
		if (s._2sat())
			std::cout << "yes\n";
		else
			std::cout << "no\n";
	}
}
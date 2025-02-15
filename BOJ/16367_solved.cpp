
/*
	k���� ���� 1~k���� �־���. ��� ������ Red, Blue�� �� �� �� �ϳ��� ����. -> bool statement
	n���� ����� 3���� ������ ���ؼ� ���� ������. -> clause

	��� ����� 3���� ���� ��, 2�� �̻��� ���� �� �ִٸ� R�� B�� �� ������ ��Ÿ����, �׷��� �ʴٸ� -1

	2-SAT�� ������Ȳ�� ǥ���ϱ⸸ �ϸ�, �� ������ SCC�� Ǯ �� ����.

	�ϳ��� clause�� (a OR b OR c)�� ���ؼ�

	-a->b, -a->c
	-b->a, -b->c
	-c->a, -c->b

	�� 6���� edge�� ���� �� ���� ������ ����. 2-SAT��� �� �� ���� ������

	Red�� true, Blue�� false
	Red�� +, Blue�� -
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

class TarjanSolver
{
private:
	TarjanSolver();
	TarjanSolver(const TarjanSolver&);
	TarjanSolver& operator=(const TarjanSolver&);

	using Graph = std::vector<std::vector<int>>;

	const Graph& graph; // graph, adjacent list
	const int N;		// number of nodes
	int order;			// order of node to visit
	int curSccNum;		// count number of scc group

	std::stack<int> st; // stack for tarjan algorithm

	std::vector<int> sccGroupNum; // saving id of scc per node
	std::vector<bool> collected;  // identify the node is collected as scc or not

	int dfs(int node)
	{
		int ans = sccGroupNum[node] = ++order;
		st.push(node);

		// search through children
		for (const int childNode : graph[node])
		{
			if (sccGroupNum[childNode] == 0) // not visited, search
				ans = std::min(ans, dfs(childNode));
			else if (!collected[childNode]) // visited but not collected
				ans = std::min(ans, sccGroupNum[childNode]);
		}

		// compare with current status
		// if the value of visited[node] is equal with the ans
		// means this 'node' is part of scc
		if (ans == sccGroupNum[node])
		{
			++curSccNum; // scc found, increase
			while (true)
			{
				int top = st.top();
				st.pop();
				sccGroupNum[top] = curSccNum;
				collected[top] = true; // check the node as collected

				if (top == node) // meet self, end of scc
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

	std::string _2satResult()
	{
		// topological sort
		// because of the Tarjan algorithm,
		// the order of the nodes are already setted.
		// higher the node id, lower topology value
		// set result combination of 2-sat
		// mark the node false, meeting first
		const int offset = N / 2;
		std::string result(offset, -1);

		for (int i = 1; i <= offset; ++i)
			result[i - 1] = (sccGroupNum[i] < sccGroupNum[i + offset]) ? 'R' : 'B';
		return result;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// build graph
	int K, N, n1, n2, n3;
	std::cin >> K >> N;
	std::vector<std::vector<int>> graph(2 * K + 1);
	auto getNode = [&]()
		{
			int node;
			char c;
			std::cin >> node >> c;
			if (c == 'B')
				node += K;
			return node;
		};
	auto reverseNode = [&](const int node)
		{
			if (node > K)
				return node - K;
			else
				return node + K;
		};
	auto add2EdgesFromClause = [&](const int n1, const int n2, const int n3)
		{
			graph[reverseNode(n1)].push_back(n2);
			graph[reverseNode(n1)].push_back(n3);
		};
	for (int i = 0; i < N; ++i)
	{
		n1 = getNode();
		n2 = getNode();
		n3 = getNode();
		add2EdgesFromClause(n1, n2, n3);
		add2EdgesFromClause(n2, n1, n3);
		add2EdgesFromClause(n3, n1, n2);
	}
	// run Tarjan algorithm
	TarjanSolver ts(graph);
	// get result
	if (ts._2sat())
	{
		std::cout << ts._2satResult();
	}
	else
	{
		std::cout << "-1";
	}
}
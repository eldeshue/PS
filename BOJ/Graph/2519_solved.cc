

#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

class TarjanSolver
{
private:
	TarjanSolver();
	TarjanSolver(const TarjanSolver &);
	TarjanSolver &operator=(const TarjanSolver &);

	using Graph = std::vector<std::vector<int>>;

	const Graph &graph; // graph, adjacent list
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
	TarjanSolver(const Graph &g)
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
		std::vector<int> result;

		for (int i = 1; i <= offset; ++i)
		{
			if (sccGroupNum[i] > sccGroupNum[i + offset]) // collect false
			{
				result.push_back(i);
			}
		}
		return result;
	}
};

using Point = std::pair<long long, long long>;
using Line = std::pair<Point, Point>;
#define X first
#define Y second

int cross(const Point &v1, const Point &v2)
{
	long long product = v1.X * v2.Y - v1.Y * v2.X;
	if (product > 0)
		return 1;
	else if (product < 0)
		return -1;
	else
		return 0;
}

// 1 : cross one point
// 0 : does not cross
// -1 : cross multiple points, overlapped
int isCross(Line &l1, Line &l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	int v1 =
		cross(vec1, std::make_pair(l2.first.X - l1.second.X, l2.first.Y - l1.second.Y)) * cross(vec1, std::make_pair(l2.second.X - l1.second.X, l2.second.Y - l1.second.Y));

	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	int v2 =
		cross(vec2, std::make_pair(l1.first.X - l2.second.X, l1.first.Y - l2.second.Y)) * cross(vec2, std::make_pair(l1.second.X - l2.second.X, l1.second.Y - l2.second.Y));

	//
	long long tmp = vec1.X;
	vec1.X *= vec2.X;
	vec1.Y *= vec2.X;
	vec2.X *= tmp;
	vec2.Y *= tmp;

	// overlap???
	if (v1 == 0 && v2 == 0)
	{
		if (l1.first > l1.second)
			std::swap(l1.first, l1.second);
		if (l2.first > l2.second)
			std::swap(l2.first, l2.second);

		if (l2.first < l1.second && l1.first < l2.second && vec1 == vec2)
			return -1;
		else if (l2.first <= l1.second && l1.first <= l2.second)
			return 1;
		else
			return 0;
	}
	// not overlap
	if ((v1 <= 0) && (v2 <= 0))
		return 1;
	else
		return 0;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K; // N : number of people, K : number of lines
	std::cin >> N;
	K = 3 * N;
	std::vector<Line> lines(K + 1);					// 1 based
	std::vector<std::vector<int>> graph(2 * K + 1); // adj list
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
	for (int i = 1; i <= K; ++i)
	{
		std::cin >> lines[i].first.first >> lines[i].first.second >> lines[i].second.first >> lines[i].second.second;
		if ((i % 3) == 0)
		{
			// clause, at least one must be true, 1false + 2true
			add2EdgesFromClause(i - 2, i - 1, i);
			add2EdgesFromClause(i, i - 2, i - 1);
			add2EdgesFromClause(i - 1, i, i - 2);
		}
	}
	for (int i = 1; i < K; ++i)
	{
		for (int j = i + 1; j <= K; ++j)
		{
			// clause, cross check
			// 1true, 1false
			if (isCross(lines[i], lines[j]))
			{
				graph[i].push_back(reverseNode(j));
				graph[j].push_back(reverseNode(i));
			}
		}
	}

	TarjanSolver solver(graph);
	if (solver._2sat())
	{
		std::vector<int> result = solver._2satResult();
		std::cout << result.size() << '\n';
		for (const int n : result)
			std::cout << n << ' ';
	}
	else
	{
		std::cout << "-1\n";
	}
}


#include <iostream>

#include <vector>
#include <queue>

using ll = long long;
using pii = std::pair<int, int>; // child node, cost
using Graph = std::vector<std::vector<pii>>;
class LCATree
{
private:
	static constexpr int ROOT = 1;

	// field
	Graph const &graph;
	int const size;
	int const lgSize;
	std::vector<std::vector<int>> sparseTable;
	std::vector<int> &parent; // ref to sparseTable[0]
	std::vector<int> depth;
	std::vector<ll> dist; // for this problem

	LCATree();
	LCATree(const LCATree &);
	LCATree &operator=(const LCATree &);

	int log2(int n)
	{
		int bitCnt = 0;
		while (n > 1)
		{
			n >>= 1;
			bitCnt++;
		}
		return bitCnt;
	}

	void bfs()
	{
		std::queue<int> nextNodes;
		std::vector<bool> visited(size + 1, false);

		visited[ROOT] = true;
		nextNodes.push(ROOT);
		while (!nextNodes.empty())
		{
			int curNode = nextNodes.front();
			nextNodes.pop();
			for (const auto [childNode, cost] : graph[curNode])
			{
				if (visited[childNode] == false)
				{
					visited[childNode] = true;
					parent[childNode] = curNode;
					depth[childNode] = depth[curNode] + 1;
					dist[childNode] = dist[curNode] + static_cast<ll>(cost);
					nextNodes.push(childNode);
				}
			}
		}
	}

public:
	LCATree(const int N, const Graph &g) : size(N), lgSize(log2(N) + 1), sparseTable(lgSize + 1, std::vector<int>(size + 1, 1)),
										   graph(g), parent(sparseTable[0]), dist(N + 1, 0), depth(N + 1, 0)
	{
		// setting parent and dist
		bfs();

		// setting sparse table
		for (int i = 1; i <= lgSize; ++i)
			for (int j = 1; j <= size; ++j)
				sparseTable[i][j] = sparseTable[i - 1][sparseTable[i - 1][j]];
	}
	~LCATree() {}

	ll query(int node, ll cost)
	{
		// farest room
		for (int pos = lgSize; pos >= 0; --pos)
		{
			const int nextNode = sparseTable[pos][node];
			if ((dist[node] - dist[nextNode]) <= cost)
			{
				cost -= dist[node] - dist[nextNode];
				node = nextNode; // jump
			}
		}
		return node;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, n1, n2, c;
	std::cin >> N;
	std::vector<int> queries(N + 1);
	for (int q = 1; q <= N; ++q)
		std::cin >> queries[q];
	Graph g(N + 1);
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> n1 >> n2 >> c;
		g[n1].push_back(std::make_pair(n2, c));
		g[n2].push_back(std::make_pair(n1, c));
	}
	LCATree tree(N, g);
	for (int room = 1; room <= N; ++room)
	{
		const int energy = queries[room];
		std::cout << tree.query(room, energy) << '\n';
	}
}

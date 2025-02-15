
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
	LCATree(const int N, const Graph &g) : size(N), lgSize(log2(N) + 1), sparseTable(lgSize + 1, std::vector<int>(size + 1, 0)),
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

	int queryLCA(int node1, int node2)
	{
		const int d1 = depth[node1];
		const int d2 = depth[node2];
		if (d1 != d2)
		{
			// move deeper one up, make d1 and d2 same
			int &deeperNode = (d1 > d2) ? node1 : node2;
			int diff = std::abs(d1 - d2);
			for (int pos = 0; pos <= lgSize; ++pos)
			{
				if (diff & (1 << pos))
				{
					deeperNode = sparseTable[pos][deeperNode];
				}
			}
		}
		// search, lower bound, log N, jump
		int lcaNode = node1;
		if (node1 != node2)
		{
			for (int pos = lgSize; pos >= 0; --pos)
			{
				const int nextNode1 = sparseTable[pos][node1];
				const int nextNode2 = sparseTable[pos][node2];
				if (nextNode1 != nextNode2)
				{
					node1 = nextNode1;
					node2 = nextNode2;
				}
			}
			lcaNode = sparseTable[0][node1];
		}
		return lcaNode;
	}

	ll queryDist(int node1, int node2)
	{
		const int lcaNode = queryLCA(node1, node2);
		return dist[node1] + dist[node2] - 2 * dist[lcaNode];
	}

	int queryKthNode(int from, int to, int k)
	{
		const int lcaNode = queryLCA(from, to);
		const int fToLCA = depth[from] - depth[lcaNode];
		const int tToLCA = depth[to] - depth[lcaNode];

		int start, step;
		if (k <= fToLCA)
		{
			start = from;
			step = k;
		}
		else
		{
			start = to;
			step = fToLCA + tToLCA - k;
		}
		// jump
		for (int pos = 0; pos <= lgSize; ++pos)
		{
			if (step & (1 << pos))
			{
				start = sparseTable[pos][start];
			}
		}
		return start;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, n1, n2, c;
	std::cin >> N;
	Graph g(N + 1);
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> n1 >> n2 >> c;
		g[n1].push_back(std::make_pair(n2, c));
		g[n2].push_back(std::make_pair(n1, c));
	}
	LCATree tree(N, g);
	int M, q, k;
	std::cin >> M;
	while (M--)
	{
		std::cin >> q >> n1 >> n2;
		if (q == 1)
			std::cout << tree.queryDist(n1, n2) << '\n';
		else
		{
			std::cin >> k;
			std::cout << tree.queryKthNode(n1, n2, --k) << '\n';
		}
	}
}

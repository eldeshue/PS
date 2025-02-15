
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using Vertex = std::array<int, 3>; // x, y, z
using Edge = std::array<int, 3>;   // idx1, idx2, cost

class UnionFind
{
private:
	std::vector<int> parent;

public:
	UnionFind(const int n) : parent(n, -1) {}
	int find(int node) // path compression
	{
		if (parent[node] < 0)
			return node;
		else
			return parent[node] = this->find(parent[node]);
	}
	void unite(int node1, int node2)
	{
		int p1 = this->find(node1);
		int p2 = this->find(node2);
		if (p1 == p2)
			return;
		else
		{
			if (parent[p1] < parent[p2]) // p1's rank is higher
			{
				parent[p1] = std::min(parent[p1], parent[p2] - 1);
				parent[p2] = p1;
			}
			else
			{
				parent[p2] = std::min(parent[p2], parent[p1] - 1);
				parent[p1] = p2;
			}
		}
	}
};

struct cmpVertex
{
	int cIdx;
	const std::vector<Vertex> &vBuf;
	cmpVertex(const int &cIdx, const std::vector<Vertex> &vBuf) : cIdx(cIdx), vBuf(vBuf) {}
	bool operator()(const int &n1, const int &n2)
	{
		return vBuf[n1][cIdx] < vBuf[n2][cIdx];
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<Vertex> vertices(N);
	std::vector<int> xIBuf(N), yIBuf(N), zIBuf(N);
	// init vertices
	for (int i = 0; i < N; ++i)
		std::cin >> vertices[i][0] >> vertices[i][1] >> vertices[i][2];
	// init index buffers
	for (int i = 0; i < N; ++i)
	{
		xIBuf[i] = i;
		yIBuf[i] = i;
		zIBuf[i] = i;
	}
	std::sort(xIBuf.begin(), xIBuf.end(), cmpVertex{0, vertices});
	std::sort(yIBuf.begin(), yIBuf.end(), cmpVertex{1, vertices});
	std::sort(zIBuf.begin(), zIBuf.end(), cmpVertex{2, vertices});
	std::vector<Edge> edges;
	for (int i = 0; i < N - 1; ++i)
	{
		edges.push_back({xIBuf[i], xIBuf[i + 1], std::abs(vertices[xIBuf[i]][0] - vertices[xIBuf[i + 1]][0])});
		edges.push_back({yIBuf[i], yIBuf[i + 1], std::abs(vertices[yIBuf[i]][1] - vertices[yIBuf[i + 1]][1])});
		edges.push_back({zIBuf[i], zIBuf[i + 1], std::abs(vertices[zIBuf[i]][2] - vertices[zIBuf[i + 1]][2])});
	}
	std::sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) -> bool
			  { return e1[2] < e2[2]; });
	// kruscal algorithm
	unsigned long long result = 0;
	UnionFind uf(N);
	for (const Edge &e : edges)
	{
		if (uf.find(e[0]) == uf.find(e[1])) // same tree, skip
		{
			continue;
		}
		else // union
		{
			result += e[2];
			uf.unite(e[0], e[1]);
		}
	}
	std::cout << result;
}

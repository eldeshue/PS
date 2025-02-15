
/*
	Bipartite Matching - Konig's theorem.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>

class HopcroftKarpSolver
{
private:
	using pii = std::pair<int, int>;
	// else right
	int rowSize;
	const std::vector<std::vector<int>> &graph;
	std::vector<int> matchedNodes;
	std::vector<int> distLayer;

	bool isLeft(const int &nodeId) const { return (~(nodeId / rowSize) & 1); };
	bool isFreeNode(const int &nodeId) { return (matchedNodes[nodeId] == -1); };
	bool isMatchedEdge(const int &lNode, const int &rNode) { return (matchedNodes[lNode] == rNode); };
	// find minimum distance of aug path
	int bfs()
	{
		std::queue<pii> q;
		bool augFlag = false;
		int minAugDist = 0;

		fill(distLayer.begin(), distLayer.end(), -1);
		for (int node = 0; node < graph.size(); ++node)
		{
			// all left and unmatched nodes
			if (isLeft(node) && isFreeNode(node) && !graph[node].empty())
			{
				distLayer[node] = 0;
				q.push(std::make_pair(node, 0));
			}
		}
		while (!q.empty())
		{
			auto [curNode, curDist] = q.front();
			q.pop();
			if (augFlag == true && curDist > minAugDist)
			{
				// no more aug path
				break;
			}
			else if (!isLeft(curNode) && !isFreeNode(curNode)) // current node is right, use matched edge
			{
				const int &nextNode = matchedNodes[curNode];
				distLayer[nextNode] = curDist + 1;
				q.push(std::make_pair(nextNode, curDist + 1));
			}
			else // current node is left
			{
				for (const int &nextNode : graph[curNode])
				{
					// finding unmatched edge
					if (distLayer[nextNode] == -1 && !isMatchedEdge(curNode, nextNode))
					{
						distLayer[nextNode] = curDist + 1;
						q.push(std::make_pair(nextNode, curDist + 1));
						if (!augFlag && !isLeft(nextNode) && isFreeNode(nextNode))
						{
							augFlag = true;
							minAugDist = curDist + 1;
						}
					}
				}
			}
		}
		return minAugDist;
	}
	bool dfs(const int &curNode, const int &curDist)
	{
		// base case
		if (curDist == 0 && isLeft(curNode) && isFreeNode(curNode))
		{
			return true;
		}
		else if (isLeft(curNode)) // follow matched edge
		{
			return dfs(matchedNodes[curNode], curDist - 1);
		}
		else // follow unmatched edge
		{
			for (const int &nextNode : graph[curNode])
			{
				// follow alternate path depend on distLayer
				if (distLayer[nextNode] == curDist - 1)
				{
					distLayer[nextNode] = -1;
					if (dfs(nextNode, curDist - 1))
					{
						matchedNodes[curNode] = nextNode;
						matchedNodes[nextNode] = curNode;
						return true;
					}
				}
			}
		}
		return false;
	}

public:
	HopcroftKarpSolver(const int rowSize, const std::vector<std::vector<int>> &g)
		: rowSize(rowSize), graph(g), matchedNodes(g.size(), -1), distLayer(g.size(), false){};
	int maxMatch()
	{
		int targetDist = 0, maxMatchCnt = 0;
		while (true)
		{
			// find augment path using bfs
			targetDist = bfs();

			if (targetDist == 0)
			{
				break; // no augment path, maximum matching
			}
			// update augment path using dfs
			for (int node = 0; node < distLayer.size(); ++node)
			{
				// dfs, if dfs == true -> result++
				if (matchedNodes[node] == -1 && distLayer[node] == targetDist)
				{
					distLayer[node] = -1;
					if (dfs(node, targetDist))
						maxMatchCnt++;
				}
			}
		}
		return maxMatchCnt;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int numTest;
	std::cin >> numTest;
	while (numTest--)
	{
		int N, M;
		std::cin >> N >> M;
		std::vector<std::string> map(N);
		for (int i = 0; i < N; ++i)
		{
			std::cin >> map[i];
		}
		std::vector<std::vector<int>> graph(N * M, std::vector<int>());
		int numNode = 0, nodeId = 0;
		for (int c = 0; c < M; ++c)
		{
			// build graph
			for (int r = 0; r < N; ++r)
			{
				if (map[r][c] == '.')
				{
					if (c + 1 < M)
					{
						for (int j = -1; j <= 1; ++j)
						{
							int rr = r + j;
							int nextNodeId = nodeId + N + j;
							if (0 <= rr && rr < N && map[rr][c + 1] == '.')
							{
								graph[nodeId].push_back(nextNodeId);
								graph[nextNodeId].push_back(nodeId);
							}
						}
					}
					numNode++;
				}
				nodeId++;
			}
		}
		HopcroftKarpSolver hks(N, graph);
		// wrt konig's theorem, number of minimum vertex cover is equal to maximum match in bipartite graph
		std::cout << numNode - hks.maxMatch() << '\n';
	}
}

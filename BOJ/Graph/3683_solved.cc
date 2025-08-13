
/*
	BOJ 3683

	개와 고양이

	누군가는 개를 고르고, 누군가는 고양이를 고른다.

	그냥 개나 고양이 둘 중 하나를 골라서 모조리 진출시키면 편한데, 이러면 최대 가치를 얻을 수 없다.
	최대의가치를 얻기 위해서는 충돌을 피해서 섞어 골라야 한다.

	=============================================================

	그렇다면, 충돌을 일으키는 인원을 가능하면 적게 제거하는 것이 목표다.

	즉, 모든 갈등을 제거할 가능한 적은 인원을 찾는 것이다.

	여기서 쾨닉의 정리가 등장한다.

	========================================================

	개를 고르는 인간, 고양이를 고르는 인간으로 그래프를 이분하고,
	서로 충돌하는 인간끼리 edge로 연결한다.

	서로 충돌하는 둘 중 하나는 사라져야만 한다. 따라서, 이분 매칭을 수행하면 된다.

	최대 매칭의 수는 minimum vertex cover 이하가 되기 때문이다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

class HopcroftKarpSolver
{
private:
	// less than offset is left, from 0 to offset - 1
	// else right
	using pii = std::pair<int, int>;
	int offset;
	const std::vector<std::vector<int>>& graph;
	std::vector<int> matchedNodes;
	std::vector<int> distLayer;

	bool isLeft(const int& nodeId) { return (nodeId < offset); }
	bool isFreeNode(const int& nodeId) { return (matchedNodes[nodeId] == -1); };
	bool isMatchedEdge(const int& lNode, const int& rNode) { return (matchedNodes[lNode] == rNode); };
	// find minimum distance of aug path
	int bfs()
	{
		std::queue<pii> q;
		bool augFlag = false;
		int minAugDist = 0;

		fill(distLayer.begin(), distLayer.end(), -1);
		for (int lNode = 0; lNode < offset; ++lNode)
		{
			// all left and unmatched nodes
			if (isFreeNode(lNode))
			{
				distLayer[lNode] = 0;
				q.push(std::make_pair(lNode, 0));
			}
		}
		while (!q.empty())
		{
			int curNode, curDist;
			std::tie(curNode, curDist) = q.front();
			q.pop();
			if (augFlag == true && curDist > minAugDist)
			{
				// no more aug path
				break;
			}
			else if (!isLeft(curNode) && !isFreeNode(curNode)) // current node is right, use matched edge
			{
				const int& nextNode = matchedNodes[curNode];
				distLayer[nextNode] = curDist + 1;
				q.push(std::make_pair(nextNode, curDist + 1));
			}
			else // current node is left
			{
				for (const int& nextNode : graph[curNode])
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
	bool dfs(const int& curNode, const int& curDist)
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
			for (const int& nextNode : graph[curNode])
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
	HopcroftKarpSolver(int offset, const std::vector<std::vector<int>>& g)
		: offset(offset), graph(g), matchedNodes(g.size(), -1), distLayer(g.size(), false) {
	};
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

	int T;
	std::cin >> T;
	while (T--)
	{
		// input
		int C, D, V;
		std::cin >> C >> D >> V;
		int const num_animal = C + D;
		std::vector<std::vector<int>> vote(num_animal * 2);
		for (int id = 0; id < V; ++id)
		{
			char type; int val;
			for (int j = 0; j < 2; ++j)
			{
				std::cin >> type >> val;
				val--;	// change to 0 indexed

				// cat lover
				if (type == 'D')
				{
					val += C;
				}
				val += j * num_animal;
				vote[val].push_back(id);
			}
		}

		// build graph
		// bipartite graph
		std::vector<std::vector<int>> graph(2 * V);
		for (int i = 0; i < num_animal; ++i)
		{
			for (auto lover : vote[i])
			{
				for (auto hater : vote[i + num_animal])
				{
					if (i < C)	// cat lover, dog hater
					{
						graph[lover].push_back(hater + V);
						graph[hater + V].push_back(lover);
					}
					else // dog lover, cat hater
					{
						graph[lover + V].push_back(hater);
						graph[hater].push_back(lover + V);
					}
				}
			}
		}

		// solve
		HopcroftKarpSolver solver(V, graph);
		std::cout << V - solver.maxMatch() << '\n';
	}
}

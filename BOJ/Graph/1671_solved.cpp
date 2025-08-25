/*
	BOJ 1671

	잡아먹는 상어는 둘, 잡아 먹히는 상어는 하나

	잡아먹는 상어와 잡아 먹히는 상어로 이분 그래프를 구성,
	이분매칭을 돌리고, 남은 상어가 살아남는다.

	추가적으로 능력치가 같은 상어는 서로를 잡아먹을 수 있다.
	하지만 한 번에 하나의 상어만 먹으므로, 같은 능력치를 갖는 상어의
	사이클 발생을 견제하면 된다.

	즉, vertex split을 한 쪽에만 하는 느낌으로 접근하면 될듯?
*/
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

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

using Stat = std::tuple<int, int, int>;
bool is_edible(Stat const& h, Stat const& p)
{
	auto const& [hz, hp, hm] = h;
	auto const& [pz, pp, pm] = p;
	return (hz >= pz) && (hp >= pp) && (hm >= pm);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<Stat> stats(N);
	for (auto& [sz, sp, sm] : stats)
		std::cin >> sz >> sp >> sm;

	// build graph
	std::vector<std::vector<int>> graph(3 * N);
	for (int hunter = 0; hunter < N; ++hunter)
	{
		for (int prey = 0; prey < N; ++prey)
		{
			if (is_edible(stats[hunter], stats[prey]))
			{
				if (hunter >= prey && stats[hunter] == stats[prey])
					continue;	// 능력치가 같은 상어는 사이클이 발생할 수 있으므로, 이를 견제한다.
				graph[hunter].push_back(2 * N + prey);
				graph[2 * N + prey].push_back(hunter);
				graph[hunter + N].push_back(2 * N + prey);
				graph[2 * N + prey].push_back(hunter + N);
			}
		}
	}

	// bipartite graph matching
	HopcroftKarpSolver solver(2 * N, graph);
	std::cout << N - solver.maxMatch();
}
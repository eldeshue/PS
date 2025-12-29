/*
	BOJ 1867

	이분 매칭에서 쾨닉의 정리 적용하는 기본 문제, well-known

	---

	한 돌을 치우려면 적어도 해당 row 혹은 col 중 하나는 반드시 선택해야 함 <- 핵심
	따라서, row/col이 겹치지 않는 돌이 있다면, 무조건 1획을 사용해야 함.

	문제에서는 최소 획의 수를 구해야 함.
	따라서 row/col이 서로 겹치지 않는 돌의 조합에 대하여, 그 조합을 이루는 돌의 수는?

	-> 조합 최적화

	----

	최소한의 획의 수는 곧 서로 겹치지 않는 조합을 이루는 돌의 갯수임

	여기가 쾨닉의 정리가 발휘되는 부분.
	이분 매칭은 기본적으로 조합 최적화, 서로 겹치지 않는 에지로 연결된 정점쌍을 최대한 구하는 것

	이 최댓값 구하기를 쾨닉의 정리로 뒤집으면, 정점 쌍을 덮는 최소한의 엣지,
	즉, minimum vertex cover가 된다.

	---

	문제 상황을 이분 그래프로 모델링 하면 다음과 같다.

	우리가 구해야 하는 것은 서로 겹치지 않는 row/col을 갖는 돌의 최소 갯수를 구하는 것.

	따라서, 돌이 곧 edge고 돌의 좌표를 구성하는 row / col이 이분 그래프를 이룬다.

	---

	이분 그래프에서 쾨닉의 정리에 의해 최대 매칭이 곧 최소 정점 커버이다.

	즉, 이분 그래프로 모델링 할 수 있는 상황이면, 최대 조합 혹은 최소 조합 둘 모두 적용 가능하다.
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

	bool isLeft(const int nodeId) const { return (nodeId < offset); }
	bool isFreeNode(const int nodeId) { return (matchedNodes[nodeId] == -1); };
	bool isMatchedEdge(const int lNode, const int rNode) { return (matchedNodes[lNode] == rNode); };
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


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> N >> K;
	std::vector<std::vector<int>> graph(2 + 2 * N);
	for (int i = 0; i < K; ++i) {
		int r, c;
		std::cin >> r >> c;
		c += N;
		graph[r].push_back(c);
		graph[c].push_back(r);
	}

	HopcroftKarpSolver solver(1 + N, graph);
	std::cout << solver.maxMatch();
}

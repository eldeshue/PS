
/*
	Hopcroft-Karp algorithm

	이분매칭 최대화 문제를 푸는 가장 효율적인 알고리즘.
	시간 복잡도는 O(n ^ 2.5)
	증명은 https://gazelle-and-cs.tistory.com/35
	구현 참고는 https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm

	< 구현 >
	먼저 그래프가 유향이라면, 무향으로 만들어라. 이분그래프는 보통 방향이 없음.
	매칭은 방향이 의미가 없다. 오히려 알고리즘을 적용하려면 무향으로 만들어야 함.

	증강 경로가 없을 때 까지 다음을 반복함.
	1. 가장 짧은 길이의 증강 경로들 찾기. bfs
	시작 그룹의 점들 중, 매칭의 일부가 아닌 점들을 대상으로 BFS를 수행.
		이를 통해서 가장 길이가 짧은 증강 경로들(의 끝 점, 즉 매칭 아닌 점)을 찾음.
		-> 못찾으면 증강경로가 없다는 뜻이고, 이는 즉 현재 매칭이 최대임을 의미.
		-> 찾은 증강 경로의 점들을 수집함, 이들은 한 번에 확장될 예정임.
		-> bfs 과정에서 비매칭 시작 노드에서 떨어진 거리를 이용(노드마다 레벨을 부여)

	2. 증강 경로들 확장하기. dfs
	BFS를 수행하여 찾아낸 최단 증강 경로들을 몰아서 업데이트 함.
	업데이트 하는 과정은 재귀적 dfs로 구현되며, 경로를 확인함.
	상기 path가 증강경로 여부에 따라 바낌.
	기본적으로 모든 노드는 즉시 visited로 체크해서 중복 방문을 피해야 함.
	1. 해당 경로가 증강 경로이다.
		-> 경험한 경로를 되감으면서(스택이 풀리면서) 뒤집어줌(매칭 비매칭 이동).
	2. 증강 경로가 아니다
		-> 해당 경로의 노드를 방문으로 체크하고, 이탈한다.

	해당 알고리즘이 종료하면 최대 이분 그래프에서 최대 매칭을 찾았음을 보장할 수 있음.

	보통 최대 매칭의 개수를 원하니 이는 업데이트 과정에서 쉽게 얻을 수 있음.
	증강 경로를 하나 업데이트 하는 과정에서 매칭의 개수는 경로마다 하나 증가함.
	그리고 증강 경로가 서로 겹치지 않음(노드 및 에지를 공유하지 않음)은 보장됨.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using pii = std::pair<int, int>;

class HopcroftKarpSolver
{
private:
	// less than offset is left, from 0 to offset - 1
	// else right
	int offset;
	const std::vector<std::vector<int>> &graph;
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
		for (int lNode = 0; lNode < offset; ++lNode )
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
			else if (!isLeft(curNode) && !isFreeNode(curNode))	// current node is right, use matched edge
			{
				const int& nextNode = matchedNodes[curNode];
				distLayer[nextNode] = curDist + 1;
				q.push(std::make_pair(nextNode, curDist + 1));
			}
			else	// current node is left
			{
				for (const int& nextNode : graph[curNode])
				{
					// finding unmatched edge
					if (distLayer[nextNode] == -1
						&& !isMatchedEdge(curNode, nextNode))
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
		else if (isLeft(curNode))	// follow matched edge
		{
			return dfs(matchedNodes[curNode], curDist - 1);
		}
		else	// follow unmatched edge
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
	HopcroftKarpSolver(int offset, const std::vector<std::vector<int>> &g)
		: offset(offset), graph(g), matchedNodes(g.size(), -1), distLayer(g.size(), false) {};
	int maxMatch()
	{
		int targetDist = 0, maxMatchCnt = 0;
		while (true)
		{
			// find augment path using bfs
			targetDist = bfs();

			if (targetDist == 0)
			{
				break;	// no augment path, maximum matching
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

	int N, M, numWork, input;
	std::cin >> N >> M;
	std::vector<std::vector<int>> graph(N + M + 1, std::vector<int>());
	for (int i = 0; i < N; ++i)
	{
		std::cin >> numWork;
		for (int j = 0; j < numWork; ++j)
		{
			std::cin >> input;
			input += N;
			graph[i].push_back(input);
			graph[input].push_back(i);
		}
	}
	HopcroftKarpSolver hks(N, graph);
	std::cout << hks.maxMatch();
}

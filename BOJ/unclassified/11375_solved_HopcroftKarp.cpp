
/*
	Hopcroft-Karp algorithm
	
	�̺и�Ī �ִ�ȭ ������ Ǫ�� ���� ȿ������ �˰���.
	�ð� ���⵵�� O(n ^ 2.5)
	������ https://gazelle-and-cs.tistory.com/35
	���� ����� https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm

	< ���� >
	���� �׷����� �����̶��, �������� ������. �̺б׷����� ���� ������ ����.
	��Ī�� ������ �ǹ̰� ����. ������ �˰����� �����Ϸ��� �������� ������ ��.

	���� ��ΰ� ���� �� ���� ������ �ݺ���.
	1. ���� ª�� ������ ���� ��ε� ã��. bfs
	���� �׷��� ���� ��, ��Ī�� �Ϻΰ� �ƴ� ������ ������� BFS�� ����.
		�̸� ���ؼ� ���� ���̰� ª�� ���� ��ε�(�� �� ��, �� ��Ī �ƴ� ��)�� ã��.
		-> ��ã���� ������ΰ� ���ٴ� ���̰�, �̴� �� ���� ��Ī�� �ִ����� �ǹ�.
		-> ã�� ���� ����� ������ ������, �̵��� �� ���� Ȯ��� ������.
		-> bfs �������� ���Ī ���� ��忡�� ������ �Ÿ��� �̿�(��帶�� ������ �ο�)

	2. ���� ��ε� Ȯ���ϱ�. dfs
	BFS�� �����Ͽ� ã�Ƴ� �ִ� ���� ��ε��� ���Ƽ� ������Ʈ ��.
	������Ʈ �ϴ� ������ ����� dfs�� �����Ǹ�, ��θ� Ȯ����.
	��� path�� ������� ���ο� ���� �ٳ�. 
	�⺻������ ��� ���� ��� visited�� üũ�ؼ� �ߺ� �湮�� ���ؾ� ��.
	1. �ش� ��ΰ� ���� ����̴�.
		-> ������ ��θ� �ǰ����鼭(������ Ǯ���鼭) ��������(��Ī ���Ī �̵�).
	2. ���� ��ΰ� �ƴϴ�
		-> �ش� ����� ��带 �湮���� üũ�ϰ�, ��Ż�Ѵ�.

	�ش� �˰����� �����ϸ� �ִ� �̺� �׷������� �ִ� ��Ī�� ã������ ������ �� ����.

	���� �ִ� ��Ī�� ������ ���ϴ� �̴� ������Ʈ �������� ���� ���� �� ����.
	���� ��θ� �ϳ� ������Ʈ �ϴ� �������� ��Ī�� ������ ��θ��� �ϳ� ������.
	�׸��� ���� ��ΰ� ���� ��ġ�� ����(��� �� ������ �������� ����)�� �����.
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
	HopcroftKarpSolver(int offset, const std::vector<std::vector<int>>& g)
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

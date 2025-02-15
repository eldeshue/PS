// 트리의 지름.
// 임의의 한 노드에서 시작하여, 해당 노드에서 가장 먼 노드a를 구함.
// 구한 a를 시작으로, a에서 가장 멀리있는 노드 b를 구함.
// 그리하면 a와 b는 해당 트리의 양 끝을 이루며, 두 노드 사이의 거리가 곧 트리의 지름임.
// 먼 노드는 트리의 순회(bfs, dfs)로 구할 수 있음.
// 단, 그래프에는 적용할 수 없고, 에지의 가중치가 음수여도 적용 불가능함.
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

unsigned int maxDist;
bool visited[100001];
std::vector<std::pair<int, int>> tree[100001];

int bfs_far(int root)
{
	std::queue<std::pair<int, unsigned int>> Q;
	int farNode = root;
	maxDist = 0;

	memset(visited, 0, sizeof(visited));
	visited[root] = true;
	Q.push(std::make_pair(root, 0));

	while (!Q.empty())
	{
		int curNode = Q.front().first;
		unsigned int curDist = Q.front().second;
		Q.pop();

		if (maxDist < curDist)
		{
			farNode = curNode;
			maxDist = curDist;
		}

		for (const auto& nextNode : tree[curNode])
		{
			if (!visited[nextNode.first])
			{
				visited[nextNode.first] = true;
				Q.push(std::make_pair(nextNode.first, curDist + nextNode.second));
			}
		}
	}

	return farNode;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, n1, n2, c;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> n1 >> n2;
		while(n2 != -1)
		{
			std::cin >> c;
			tree[n1].push_back(std::make_pair(n2, c));
			std::cin >> n2;
		}
	}

	int start, end;
	start = bfs_far(1);
	end = bfs_far(start);
	std::cout << maxDist;
}
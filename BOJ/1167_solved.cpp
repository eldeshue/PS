// Ʈ���� ����.
// ������ �� ��忡�� �����Ͽ�, �ش� ��忡�� ���� �� ���a�� ����.
// ���� a�� ��������, a���� ���� �ָ��ִ� ��� b�� ����.
// �׸��ϸ� a�� b�� �ش� Ʈ���� �� ���� �̷��, �� ��� ������ �Ÿ��� �� Ʈ���� ������.
// �� ���� Ʈ���� ��ȸ(bfs, dfs)�� ���� �� ����.
// ��, �׷������� ������ �� ����, ������ ����ġ�� �������� ���� �Ұ�����.
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
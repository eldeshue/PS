
#include <iostream>
#include <vector>
#include <memory.h>

int numCreed[10001];
std::vector<int> adjList[10001];

// Ʈ�������� ������ �����µ�, �׷������� ����Ŭ�� ����� ������ �����....
// �ش� ����� �ذ��Ϸ��� ���� ������ �˰����� Ȱ���ؾ� �� ������ ������...
int dfs(int curNode)
{
	if (numCreed[curNode] > 0)
		return numCreed[curNode];
	else if (numCreed[curNode] == 0)
	{
		// cycle

	}
	numCreed[curNode] = 0;
	for (const int& nextNode : adjList[curNode])
	{
		numCreed[curNode] += dfs(nextNode);
	}
	return ++numCreed[curNode];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(numCreed, -1, sizeof(numCreed));

	// input
	int N, M, parent, child;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> child >> parent;
		adjList[parent].push_back(child);
	}
	// search
	for (int i = 1; i <= N; ++i)
	{
		if (numCreed[i] == -1)
			dfs(i);
	}
	int maxCnt = 0;
	for (int i = 1; i <= N; ++i)
	{
		maxCnt = std::max(maxCnt, numCreed[i]);
	}
	// output
	for (int i = 1; i <= N; ++i)
	{
		if (numCreed[i] == maxCnt)
			std::cout << i << ' ';
	}
}
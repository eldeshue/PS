
#include <iostream>
#include <memory.h>
#include <vector>

int N, root, eraseNode;
int parents[50];
int leafVal[50];
std::vector<int> graph[50];

int DFS(int curNode)
{
	if (graph[curNode].size() == 0) // leaf
	{
		return leafVal[curNode] = 1;
	}

	int leafCount = 0;
	for (const auto& nextNode : graph[curNode])
	{
		leafCount += DFS(nextNode);
	}
	return leafVal[curNode] = leafCount;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(leafVal, 0, sizeof(leafVal));

	int parent;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> parent;
		parents[i] = parent;
		if (parent < 0)
		{
			root = i;
		}
		else
		{
			graph[parent].push_back(i);
		}
	}
	std::cin >> eraseNode;

	DFS(root);

	if (root != eraseNode)
	{
		if (graph[parents[eraseNode]].size() == 1)
		{
			std::cout << leafVal[root] - leafVal[eraseNode] + 1;
			return 0;
		}
	}

	std::cout << leafVal[root] - leafVal[eraseNode];
	return 0;
}
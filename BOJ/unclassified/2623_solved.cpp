
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

int numSinger, numPD;
std::vector<int> graph[1001];
int edgeCount[1001];
int result[1000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(edgeCount, 0, sizeof(edgeCount));
	std::queue<int> Q;

	int numInput, curNode, prevNode;
	std::cin >> numSinger >> numPD;
	for (int i = 0; i < numPD; ++i)
	{
		std::cin >> numInput >> prevNode;
		for (int j = 0; j < numInput - 1; ++j)
		{
			std::cin >> curNode;
			edgeCount[curNode]++;
			graph[prevNode].push_back(curNode);
			prevNode = curNode;
		}
	}

	// find start
	for (int i = 1; i <= numSinger; ++i)
	{
		if (edgeCount[i] == 0)
		{
			Q.push(i);
		}
	}

	// BFS like
	int index = 0;
	while(!Q.empty())
	{ 
		curNode = Q.front();
		result[index] = curNode;
		index++;
		Q.pop();

		for (const auto nextNode : graph[curNode])
		{
			edgeCount[nextNode]--;
			if (edgeCount[nextNode] == 0)
			{
				Q.push(nextNode);
			}
		}
	}

	if (index < numSinger)
	{
		std::cout << 0;
		return 0;
	}
	else
	{
		for (int i = 0; i < numSinger; ++i)
		{
			std::cout << result[i] << "\n";
		}
		return 0;
	}
}
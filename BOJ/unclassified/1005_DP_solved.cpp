
#include <iostream>
#include <memory.h>
#include <vector>

int numNode, goalNode;
int cache[1001];
int buildTime[1001];
std::vector<int> reverseGraph[1001];

void clear(int N)
{
	memset(cache, -1, (N + 1) * sizeof(int)); // must initialize cache by -1.
											  // else, 0 can be bottle neck.
											  // because build time can be 0.
	for (int i = 1; i <= N; ++i)
	{
		reverseGraph[i].clear();		// clear graph
	}
}

int DP(int curNode)	// this graph can have multiple start node
{
	if (cache[curNode] != -1)	// cache hit
	{
		return cache[curNode];
	}
	else // cache miss, base case included
	{
		int temp, maxChildTime = 0;
		// find max
		for (const auto& parent : reverseGraph[curNode])
		{
			temp = DP(parent);
			if (cache[parent] > maxChildTime)
			{
				maxChildTime = temp;
			}
		}
		return cache[curNode] = buildTime[curNode] + maxChildTime;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int numTest;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		int edgeNum, parent, child;
		std::cin >> numNode >> edgeNum;
		clear(numNode);
		for (int j = 1; j <= numNode; ++j) // set build time
		{
			std::cin >> buildTime[j];
		}
		for (int j = 0; j < edgeNum; ++j) // set graph, adjacent nodes
		{
			std::cin >> parent >> child;
			reverseGraph[child].push_back(parent);
		}
		std::cin >> goalNode;
		std::cout << DP(goalNode) << "\n";
	}
}
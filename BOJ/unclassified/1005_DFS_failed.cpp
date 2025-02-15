// ACM Craft
// tree + DFS
// failed, TLE
#include <iostream>
#include <memory.h>
#include <vector>

int numNode, goalNode;
int cache[1001];
int buildTime[1001];
bool isStartNode[1001];
std::vector<int> graph[1001];
std::vector<int> start;

void clear(int N)
{
	memset(cache, 0, (N + 1) * sizeof(int));
	for (int i = 1; i <= N; ++i)
	{
		isStartNode[i] = true;	// clear start nodes
		graph[i].clear();		// clear graph
	}
	start.clear();
}

void DFS_DP(int val, int curNode)	// this graph can have multiple start node
{
	val += buildTime[curNode];	// build current node
	if (val > cache[curNode])	// compare and cache
	{
		cache[curNode] = val;
	}

	for (const auto& elem : graph[curNode])	// next node
	{
		DFS_DP(cache[curNode], elem);
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
			isStartNode[child] = false; // exclude pointed node, which is not root
			graph[parent].push_back(child);
		}
		std::cin >> goalNode;
		// add start nodes
		for (int j = 1; j <= numNode; ++j)
		{
			if (isStartNode[j])
			{
				start.push_back(j);
			}
		}
		// traversal graphs. the graph can have multiple root node	
		for (const auto& elem : start)
		{
	  		DFS_DP(0, elem); // how to find start node ??? node that has never been pointed.
		}
		std::cout << cache[goalNode] << "\n";
	}
}

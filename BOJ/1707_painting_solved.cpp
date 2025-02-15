#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>

int numTest, numNode, numEdge, startNode;
std::vector<int> graph[20001];		// connection list
int color[20001];

void clear() // initialize buffers
{
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= numNode; ++i)
	{
		graph[i].clear();
	}
}

int findNotVisitNode() // find not color node
{
	for (int i = 1; i <= numNode; ++i)
	{
		if (!color[i])
		{
			return i;
		}
	}
	// not found, return -1
	return -1;
}

bool BFS(int startNodeNum)
{
	std::queue<int> nextNode;
	int curColor = 1;
	color[startNodeNum] = curColor;
	nextNode.push(startNodeNum);
	
	while (!nextNode.empty())
	{
		int curNode = nextNode.front();
		nextNode.pop();
		curColor = color[curNode] * -1;

		for (const auto& adj : graph[curNode])
		{
			if (color[adj] == 0) // not color
			{
				color[adj] = curColor;
				nextNode.push(adj);
			}
			else if(color[adj] == color[curNode]) 
			{
				return false;
			}

		}

	}
	
	return true;
}



int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int input1, input2;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		// fill graph
		std::cin >> numNode >> numEdge;
		clear();
		for (int j = 0; j < numEdge; ++j)
		{
			std::cin >> input1 >> input2;
			graph[input1].push_back(input2);
			graph[input2].push_back(input1);
		}
		// find cycle with odd number node.
		bool result = true;
		while ((startNode = findNotVisitNode()) > 0) // travel until all nodes are color
		{
			result &= BFS(startNode);
		}
		// print result
		if (result)
		{
			std::cout << "YES\n";
		}
		else
		{
			std::cout << "NO\n";
		}
	}
}

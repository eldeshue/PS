
#include <iostream>
#include <queue>
#include <vector>

std::vector<int> graph[101];
bool visited[101] = { false };
int numInfected = 0;

void infectBFS()
{
	std::queue<int> nextNode;
	// always starts from 1
	visited[1] = true;
	nextNode.push(1);
	
	while (!nextNode.empty())
	{
		int curNode = nextNode.front();
		nextNode.pop();

		for (const auto& elem : graph[curNode])
		{
			if (!visited[elem])
			{
				visited[elem] = true;
				nextNode.push(elem);
				numInfected++;
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int numNode, numEdge, input1, input2;
	std::cin >> numNode >> numEdge;
	for (int i = 0; i < numEdge; ++i)
	{
		std::cin >> input1 >> input2;
		graph[input1].push_back(input2);
		graph[input2].push_back(input1);
	}

	infectBFS();
	std::cout << numInfected;
}
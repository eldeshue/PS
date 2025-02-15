/*
// 이분 불가능 그래프의 특성, 홀수 사이클
// 홀수 사이클을 가지는지 여부를 확인하여 문제를 풀기.
#include <iostream>
#include <memory.h>
#include <vector>
#include <map>

int numTest, numNode, numEdge, startNode;
std::map<int, int> branchRecord;	// branch only if the node.size() >= 3
std::vector<int> graph[20001];		// connection list
bool visited[20001];

void clear() // initialize buffers
{
	memset(visited, 0, sizeof(visited));
	branchRecord.clear();
	for (int i = 1; i <= numNode; ++i)
	{
		graph[i].clear();
	}
}

int findNotVisitNode() // find not visited node
{
	for (int i = 1; i <= numNode; ++i)
	{
		if (!visited[i])
		{
			return i;
		}
	}
	// not found, return -1
	return -1;
}

bool DFS(int curNodeNum, int prevNodeNum, int curLength) // find odd length cycle
{
	bool isBipartie = true;
	std::vector<int>& curNode = graph[curNodeNum];

	// record the branch
	if (curNode.size() >= 3 || (curNodeNum == startNode && curNode.size() >= 2))
	{
		branchRecord.insert(std::make_pair(curNodeNum, curLength));
	}

	
	if (curNode.size() == 1 && curNodeNum != startNode)	// leaf
	{
		return true;
	}
	else // not leaf, branch
	{
		for (const auto& adj : curNode)
		{
			if (!visited[adj]) // not visited, new node
			{
				visited[adj] = true;
				isBipartie &= DFS(adj, curNodeNum, curLength + 1);
			}
			else if(adj != prevNodeNum) // visited, meet the end of the cycle
			{
				int cycleLength = curLength - branchRecord[adj] + 1;

				if ((cycleLength % 2) == 1) // length is odd, not bipartie
				{
					return false;
				}
			}
		}

		return isBipartie;
	}
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
		while ((startNode = findNotVisitNode()) > 0) // travel until all nodes are visited
		{
			visited[startNode] = true;
			result &= DFS(startNode, 0, 1);
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

*/

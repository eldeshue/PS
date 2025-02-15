// 오일러 회로, 순회 경로 찾는 문제
// 쉽게 한 붓 그리기, 모든 edge의 순회
// 보다 고차원적인 그래프 이론에 대한 학습이 필요한듯.
// 구현 자체는 DFS를 이용하여 백트래킹하면 되는듯 하지만,
// 깊이 우선 순회를 해도 어떻게 모든 에지를 순회할 수 있는지 모르겠음.
// 혹시나 어떤 식으로 heuristic을 부여해야 풀 수 있을까?

/*
#include <iostream>
#include <memory.h>
#include <deque>

std::deque<int> eulerCircuit;
int numNode, numTotalEdge = 0;
int edge[1001][1001]; // edge[node][0] = number of the node's edge
					  // edge[node1][node2] = number of the edge between node1 and node2

void DFS(int curNode)
{
	eulerCircuit.push_back(curNode);

	// find next Node to move, find the node with little edge
	// 다음으로 움직일 노드를 선정하는 방법, 핵심 구조.
	int nextNode = 0, val = 0;
	for (int i = 1; i <= numNode; ++i)
	{
		// 다음 노드를 어떻게 구하는지? 
		
		////////////////////////////
	}

	if (nextNode == 0) // stop, cant find next node 
	{
		return;
	}
	else // erase and move
	{
		edge[curNode][nextNode]--;
		edge[curNode][0]--;
		edge[nextNode][curNode]--;
		edge[nextNode][0]--;
		return DFS(nextNode);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(edge, 0, sizeof(edge));

	// initialize adjacent matrix, edge
	std::cin >> numNode;
	for (int i = 1; i <= numNode; ++i)
	{
		for (int j = 1; j <= numNode; ++j)
		{
			std::cin >> edge[i][j];
			edge[i][0] += edge[i][j];
		}
		numTotalEdge += edge[i][0];
		if (edge[i][0] % 2 != 0) // not euler circuit
		{
			std::cout << -1;
			return 0;
		}
	}
	///////// find start Node ////////
	int startNode = 0, startVal = 0;
	for (int i = 1; i <= numNode; ++i)
	{
		if (startVal < edge[i][0])
		{
			startVal = edge[i][0];
			startNode = i;
		}
	}
	/////////// travel //////////////
	DFS(startNode);
	//////////// print ////////////////
	while (!eulerCircuit.empty())
	{
		std::cout << eulerCircuit.front() << " ";
		eulerCircuit.pop_front();
	}
}
*/
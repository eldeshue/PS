// ���Ϸ� ȸ��, ��ȸ ��� ã�� ����
// ���� �� �� �׸���, ��� edge�� ��ȸ
// ���� ���������� �׷��� �̷п� ���� �н��� �ʿ��ѵ�.
// ���� ��ü�� DFS�� �̿��Ͽ� ��Ʈ��ŷ�ϸ� �Ǵµ� ������,
// ���� �켱 ��ȸ�� �ص� ��� ��� ������ ��ȸ�� �� �ִ��� �𸣰���.
// Ȥ�ó� � ������ heuristic�� �ο��ؾ� Ǯ �� ������?

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
	// �������� ������ ��带 �����ϴ� ���, �ٽ� ����.
	int nextNode = 0, val = 0;
	for (int i = 1; i <= numNode; ++i)
	{
		// ���� ��带 ��� ���ϴ���? 
		
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
// ������ ����
/*
 * �������� ���� : �����ϸ� �׷����� ���� ����� ���� ������.
 * ���� : �׷��� ���� ����Ŭ�� �̷��� �ʴ� edge�� �������� �� �и���.
 * solution : ������ �̷�� ��尡 cycle�� �Ϻ����� �ƴ��� �ĺ��Ѵ�.
		 * DFS : �׷����� ��ȸ�ϸ鼭 ����Ŭ�� �̷���� ���θ� Ȯ���ϵ��� �Ѵ�. DFS�� ������ DFS��
		 �׷����� ���������� Ž���ϱ� ������.
		 * ���� ���� ��� : �迭�� �����ؼ� DFS�� ��ȸ�� ������ �����Ѵ�.
	
	1) ���� ��尡 �̹� �湮�� ���, �� �ڽź��� ������ ���� -> ����Ŭ�� ���� Ȯ��.
	���� ������ ������ ���� ����� ������ ����Ŭ�� �̷�� ������ ��ĥ�Ѵ�.(��ȯ������ ���� �˸�) 
	-> ��ĥ�� ��� ���̿����� �������� �߻����� ����(������ �̷�).

	2) ���� ��尡 �̹湮 ���. DFS�� ����
		2-1) DFS�� ��ȯ��, �� ���� Ȯ���� ���, �ڽź��� ���� ������ ĥ���� -> ����Ŭ�� �Ϻ�
		���� �ڽ��� ���� ������, �ڽű����� �ϳ��� ����Ŭ��.

		2-2) ��ȯ��, �� ���� �ڽź��� ������. -> ����Ŭ�� �ٱ�, �� �������� �̷�� ���.

*/
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

int V, E, curPos = 1;
int arrival[100001];	// ���� ������ �񱳸� ���ؼ� ������. visited�� Ȯ��, color����
std::vector<std::vector<int>> graph;		// ���� ���� ����
std::vector<std::pair<int, int>> bridge;	// ��� ����

int DFS(int curNode, int parent)
{
	arrival[curNode] = curPos++;	// ���� ������ ������
	int curVal = arrival[curNode];	// �ش� ����� ���� ����, ���� ���� ���� ����Ŭ�� �Ϻ����� Ȯ��

	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];	// ���� ����� ���� ���
		if (nextNode == parent)	// �ش� ��尡 �θ��, ������
		{
			continue;
		}

		if (arrival[nextNode] == 0) // not visited
		{
			int retVal = DFS(nextNode, curNode);	// DFS����, ���� ����� ���� Ȯ��
			if (retVal > arrival[curNode]) // not cycle, bridge
			{
				unsigned int a = curNode;
				unsigned int b = nextNode;
				if (a > b)
				{
					std::swap(a, b);
				}
				bridge.push_back(std::make_pair(a, b));	// ���� ����
			}
			curVal = std::min(curVal, retVal);	// �ڽ��� ���� ����
		}
		else // visited, cycle found
		{
			curVal = std::min(curVal, arrival[nextNode]);	// ���� ��尡 �̹� ���� ���, ���� ����
		}
	}

	return curVal;	// �ڽ��� ���� ��ȯ�ؼ� �θ� ��忡�� �ٽ� �Ǻ��ϱ�
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arrival, 0, sizeof(arrival));

	int node1, node2;
	std::cin >> V >> E;
	graph.resize(V + 1);
	for (int i = 0; i < E; ++i)
	{
		std::cin >> node1 >> node2;
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}

	DFS(1,0);

	std::sort(bridge.begin(), bridge.end());
	std::cout << bridge.size() << "\n";
	for(const auto b : bridge)
	{
		std::cout << b.first << " " << b.second << "\n";
	}
}
// ���� �� ����.
// ���� �� �˰���� ���������� back edge�� �����Ͽ� ������ Ǭ��.
// �ٸ�, �������� �ִٸ� ���� ���� ���� ���� ���ǰ� �ٸ�. Ǯ�� ����� ����� ����.
//
// �����ϰ� �����ڸ�, ����Ŭ�� �ŵ��� �Ǵ� ���� ����Ŭ�� �̷��� �ʴ� ���, 
// �׸��� BST�� ��Ʈ�� 2�� �̻��� �ڽ��� ���� �����.
// 
#include <iostream>
#include <memory.h>
#include <vector>

int V, E, cnt = 0, curTime = 1;
int arrival[100001];
std::vector<int> graph[100001];
bool isArticulationPoint[100001];

int DFS(int curNode, bool isRoot)	// 
{
	arrival[curNode] = curTime++;
	int curColor = arrival[curNode];
	int dstChild = 0;	// dfs Ʈ���� �ڽ��� ���� 2 �̻��̸�, ������ �������̴�.

	// ���� ����� ��ȸ 
	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];

		if (arrival[nextNode] == 0)	// not visited
		{
			dstChild++;	// DST�� �ڽ��� ���� Ȯ�� 
			int nextColor = DFS(nextNode, false);
			curColor = std::min(curColor, nextColor);
			// �Ž��� ���鼭 ĥ�� ����Ŭ�� ��, Ȥ�� �������� �Ϻ�
			// �ڽ��� ���� ���� �ڽź��� ũ��, �������� �Ϻ���.
			// �ڽ��� ���� �ڽ��� ������ ���� ���ٸ�, ����Ŭ�� ����.
			if (!isRoot && nextColor >= arrival[curNode] && !isArticulationPoint[curNode])
			{	
				cnt++;
				isArticulationPoint[curNode] = true;
			}
		}
		else // back edge�� ã����, visited, color�� ������
		{
			curColor = std::min(curColor, arrival[nextNode]);
		}
	}

	if (isRoot && dstChild > 1)	// ��Ʈ�� ���� ���� ����
	{
		cnt++;
		isArticulationPoint[curNode] = true;
	}

	return curColor;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arrival, 0, sizeof(arrival));
	memset(isArticulationPoint, 0, sizeof(isArticulationPoint));

	int n1, n2;
	std::cin >> V >> E;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}

	for(int i = 1; i <= V && (curTime != V + 1); ++i)
	{
		if (arrival[i] == 0)	// �̹湮 ��带 root�� ��Ƽ� ��ȸ 
		{
			DFS(i, true);
		}
	}

	std::cout << cnt << "\n";
	for (int i = 1; i <= V; ++i)
	{
		if (isArticulationPoint[i])
		{
			std::cout << i << " ";
		}
	}
}
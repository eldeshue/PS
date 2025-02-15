// using BFS
#include <iostream>
#include <vector>
#include <queue>

typedef struct node { // Ʈ�� �ڷᱸ���� ��尡 �ƴ϶� ��ǻ� �׷�����
	// index == value
	std::vector<int> near_node; // �׷����� Ʈ���� ���̴� ��ȯ ����
} node;

std::vector<bool> visited;   // �湮 ���� ���, �̸� ���ؼ� �θ�� �ڽ��� ������, �θ�� �����ϱ⿡
std::vector<node*> tree;	 // ���� tree���� 2���� �迭��. ���� ���δ� ��尡 ������ ����.
std::vector<int> result;	 // ��ȸ ����� ���, ������.
std::queue<int> travel_queue;	// BFS������ �ʿ��� ���Լ��� �ڷᱸ���� ť.

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int numNode, input1, input2;
	std::cin >> numNode;
	tree.resize(numNode + 1);	// �ε����� value�� �Ͽ�ȭ �ϱ� ���ؼ� 1 ũ�� �Ҵ���
	visited.resize(numNode + 1);
	result.resize(numNode + 1);
	// initialize
	for (int i = 1; i <= numNode; ++i)
	{
		tree[i] = new node;
		visited[i] = false;
	}
	// get input
	for (int i = 1; i < numNode; ++i)
	{
		std::cin >> input1 >> input2;
		tree[input1]->near_node.push_back(input2); // �θ� �ڽ� �����ϰ� �׳� ���� ���θ� ����,
		tree[input2]->near_node.push_back(input1); // �� tree�� �ƴ� �Ϲ����� graph��.
	}
	// BFS, start from 1
	// �ʺ� �켱 Ž���� �����ϱ� ���ؼ� ť�� Ȱ��
	travel_queue.push(1);
	while (!travel_queue.empty())
	{
		int cur_node_index = travel_queue.front(); // ��⿭�� ���� ���� ������
		travel_queue.pop(); // ����
		visited[cur_node_index] = true; // �ش� ��带 �����Ͽ����� ����

		// �� ����� ���� ���(�θ� + �ڽ�)�� ���Ͽ� ������ �з� ������ ������
		for (const auto& elem : tree[cur_node_index]->near_node) 
		{
			if (visited[elem]) // �̹� �������� �ִ� ��� -> �θ���.
			{
				result[cur_node_index] = elem;
			}
			else // ���� ������ ���� -> �ڽ���.
			{
				travel_queue.push(elem); // �ʺ� �켱 Ž���� ���� ť�� �߰�
			}
		}
	}

	for (int i = 2; i <= numNode; ++i) // �ܼ� ���� ���
	{
		std::cout << result[i] << "\n";
	}
}
// using BFS
#include <iostream>
#include <vector>
#include <queue>

typedef struct node { // 트리 자료구조의 노드가 아니라 사실상 그래프임
	// index == value
	std::vector<int> near_node; // 그래프와 트리의 차이는 순환 여부
} node;

std::vector<bool> visited;   // 방문 여부 기록, 이를 통해서 부모와 자식을 구별함, 부모는 유일하기에
std::vector<node*> tree;	 // 말은 tree지만 2차원 배열임. 연결 여부는 노드가 가지고 있음.
std::vector<int> result;	 // 순회 결과를 기록, 정답지.
std::queue<int> travel_queue;	// BFS구현에 필요한 선입선출 자료구조인 큐.

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int numNode, input1, input2;
	std::cin >> numNode;
	tree.resize(numNode + 1);	// 인덱스와 value를 일원화 하기 위해서 1 크게 할당함
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
		tree[input1]->near_node.push_back(input2); // 부모 자식 무관하게 그냥 연결 여부만 저장,
		tree[input2]->near_node.push_back(input1); // 즉 tree가 아닌 일반적인 graph임.
	}
	// BFS, start from 1
	// 너비 우선 탐색을 구현하기 위해서 큐를 활용
	travel_queue.push(1);
	while (!travel_queue.empty())
	{
		int cur_node_index = travel_queue.front(); // 대기열의 가장 앞을 가져옴
		travel_queue.pop(); // 제거
		visited[cur_node_index] = true; // 해당 노드를 경유하였음을 저장

		// 각 노드의 인접 노드(부모 + 자식)에 대하여 다음의 분류 과정을 수행함
		for (const auto& elem : tree[cur_node_index]->near_node) 
		{
			if (visited[elem]) // 이미 지난적이 있는 경우 -> 부모임.
			{
				result[cur_node_index] = elem;
			}
			else // 지난 전적이 없다 -> 자식임.
			{
				travel_queue.push(elem); // 너비 우선 탐색을 위한 큐에 추가
			}
		}
	}

	for (int i = 2; i <= numNode; ++i) // 단순 정답 출력
	{
		std::cout << result[i] << "\n";
	}
}
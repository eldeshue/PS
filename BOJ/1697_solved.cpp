
#include <iostream>
#include <queue>

bool visited[100001] = { false };
int numTime[100001] = { 100000 };

void BFS(int startNode, int endNode)
{
	std::queue<int> nextNode;
	nextNode.push(startNode);
	visited[startNode] = true;
	numTime[startNode] = 0;
	
	while (!nextNode.empty())
	{
		int newNode, curNode = nextNode.front();
		nextNode.pop();

		if (curNode == endNode)
		{
			return;
		}

		// add next node
		// *2
		int newTime = numTime[curNode] + 1;
		if ((newNode = curNode * 2) <= 100000 && !visited[newNode])
		{
			numTime[newNode] = newTime;
			visited[newNode] = true;	// 이미 거쳐온 노드라면, 이미 최소 시간으로 경유함.
			nextNode.push(newNode);
		}
		// +1
		if ((newNode = curNode + 1) <= 100000 && !visited[newNode])
		{
			numTime[newNode] = newTime;
			visited[newNode] = true;	// 이미 거쳐온 노드라면, 이미 최소 시간으로 경유함.
			nextNode.push(newNode);
		}
		// -1
		if ((newNode = curNode - 1) >= 0 && !visited[newNode])
		{
			numTime[newNode] = newTime;
			visited[newNode] = true;	// 이미 거쳐온 노드라면, 이미 최소 시간으로 경유함.
			nextNode.push(newNode);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int start, goal;
	std::cin >> start >> goal;
	BFS(start, goal);
	std::cout << numTime[goal];
}
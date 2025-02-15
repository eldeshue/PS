
// https://www.acmicpc.net/problem/9466
#include <iostream>
#include <memory.h>

#define NOT_VISITED 0
#define VISITED -1

int nodeNum, numProject;
int nextNode[100001];		// graph
int visited[100001];		// paint color

void DFS(int curNode, int curColor)
{
	// cur
	visited[curNode] = curColor;
	// next
	const int& nextColor = visited[nextNode[curNode]];
	if (0 < nextColor && nextColor <= curColor)
		numProject += curColor - nextColor + 1;
	else if (nextColor == NOT_VISITED )
		DFS(nextNode[curNode], curColor + 1);
	visited[curNode] = VISITED;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int testNum;
	std::cin >> testNum;
	while (testNum--)
	{
		memset(visited, 0, sizeof(visited));
		numProject = 0;

		std::cin >> nodeNum;
		for (int i = 1; i <= nodeNum; ++i)
		{
			std::cin >> nextNode[i];
		}

		// solve
		for (int i = 1; i <= nodeNum; ++i)
		{
			if (visited[i] == NOT_VISITED)
				DFS(i, 1);
		}

		// output
		std::cout << nodeNum - numProject << '\n';
	}
}

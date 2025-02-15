
#include <iostream>
#include <memory.h>
#include <vector>

typedef std::pair<int, int> node;

int N, farestNode, result = 0;
int Dist[10001];
std::vector<node> graph[10001];

void DFS(int curNode)
{
	for (const auto& nextNode : graph[curNode])
	{
		if (Dist[nextNode.first] == -1)
		{
			Dist[nextNode.first] = Dist[curNode] + nextNode.second;
			DFS(nextNode.first);

			// update farest Node
			if (Dist[nextNode.first] > Dist[farestNode])
			{
				farestNode = nextNode.first;
			}
		}
	}
}

void setFarestNode(int startNode, int& target)
{
	memset(Dist, -1, sizeof(Dist));
	farestNode = startNode;
	Dist[startNode] = 0;

	DFS(startNode);

	result = Dist[farestNode];
	target = farestNode;
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int A, B, n1, n2, c;
	std::cin >> N;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> n1 >> n2 >> c;
		graph[n1].push_back(node(n2, c));
		graph[n2].push_back(node(n1, c));
	}

	// find A
	setFarestNode(1, A);
	// find B
	setFarestNode(A, B);
	std::cout << result;
}
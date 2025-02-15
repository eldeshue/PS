
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

typedef struct node
{
	int arrivTime;
	int num;
	node(int a, int n) : arrivTime(a), num(n) {}
} node;

struct comp
{
	bool operator()(const node& n1, const node& n2)
	{
		if (n1.arrivTime == n2.arrivTime)
		{
			return n1.num > n2.num;
		}
		else
		{
			return n1.arrivTime > n2.arrivTime;
		}
	}
};

bool visited[32001];
int inDegree[32001];
std::vector<int> forwardGraph[32001];
std::vector<int> backwardGraph[32001];

void findLeaf(std::priority_queue < node, std::vector<node>, comp>& Q, int child)	// using backward graph, find leaf
{
	if (!visited[child] && inDegree[child] == 0)	// not visited leaf node, have 0 in Degree
	{
		for (const auto& gChild : forwardGraph[child])
		{
			if (inDegree[gChild] > 0)
			{
				inDegree[gChild]--;
			}
		}
		visited[child] = true;
		Q.push(node(0, child));
		return;
	}
	else if (visited[child])	// visited, already checked
	{
		return;
	}
	else
	{
		for (const auto& parent : backwardGraph[child])
		{
			findLeaf(Q, parent);
		}
	}
}

void BFS(int root)	// topological sort
{
	std::priority_queue<node, std::vector<node>, comp> Q;
	findLeaf(Q, root);

	while (!Q.empty())
	{
		int curNodeArriv = Q.top().arrivTime;
		int curNodeNum = Q.top().num;
		Q.pop();
		std::cout << curNodeNum << " ";
		for (const auto& nextNode : forwardGraph[curNodeNum])
		{
			if (inDegree[nextNode] > 0)
			{
				--inDegree[nextNode];
			}
		}

		if (curNodeNum == root)
		{
			break;
		}
		else
		{
			for (const auto& nextNode : forwardGraph[curNodeNum])
			{
				if (!visited[nextNode] && inDegree[nextNode] == 0)
				{
					visited[nextNode] = true;
					Q.push(node(curNodeArriv + 1, nextNode));
				}
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(visited, 0, sizeof(visited));
	memset(inDegree, 0, sizeof(inDegree));

	int N, K, s, e;
	std::cin >> N >> K;
	for (int i = 0; i < K; ++i)
	{
		std::cin >> s >> e;
		inDegree[e]++;
		forwardGraph[s].push_back(e);
		backwardGraph[e].push_back(s);
	}
	for (int i = 1; i <= N; ++i)
	{
		BFS(i);
	}
}
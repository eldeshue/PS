
#include <iostream>
#include <memory.h>
#include <string>
#include <vector>
#include <queue>

typedef std::pair<int, int> node;

struct compNode
{
	bool operator()(const node& n1, const node& n2)
	{
		return n1.second > n2.second;
	}
};

int N, M;
bool maze[100][100];
bool visited[10000];
unsigned int cost[10000];

int Dijkstra()
{
	std::priority_queue<node, std::vector<node>, compNode> PQ;
	memset(cost, -1, sizeof(cost));	// initialize with max
	memset(visited, 0, sizeof(visited));

	// setting initial value
	visited[0] = true;
	PQ.push(std::make_pair(0, 0));
	while (!PQ.empty())
	{
		int curCost = PQ.top().second;
		if (cost[PQ.top().first] < curCost)
		{
			PQ.pop();
			continue;
		}
		cost[PQ.top().first] = curCost;
		int curX = PQ.top().first / M;
		int curY = PQ.top().first % M;
		PQ.pop();

		int nextIndex;
		int u = curX - 1;
		int d = curX + 1;
		int l = curY - 1;
		int r = curY + 1;
		// up
		nextIndex = u * M + curY;
		if (u >= 0 && !visited[nextIndex])
		{
			visited[nextIndex] = true;
			if (maze[u][curY])
			{
				PQ.push(std::make_pair(nextIndex, curCost + 1));
			}
			else
			{
				PQ.push(std::make_pair(nextIndex, curCost));
			}
		}
		// left
		nextIndex = curX * M + l;
		if (l >= 0 && !visited[nextIndex])
		{
			visited[nextIndex] = true;
			if (maze[curX][l])
			{
				PQ.push(std::make_pair(nextIndex, curCost + 1));
			}
			else
			{
				PQ.push(std::make_pair(nextIndex, curCost));
			}
		}
		// down
		nextIndex = d * M + curY;
		if (d < N && !visited[nextIndex])
		{
			visited[nextIndex] = true;
			if (maze[d][curY])
			{
				PQ.push(std::make_pair(nextIndex, curCost + 1));
			}
			else
			{
				PQ.push(std::make_pair(nextIndex, curCost));
			}
		}
		// right
		nextIndex = curX * M + r;
		if (r < M && !visited[nextIndex])
		{
			visited[nextIndex] = true;
			if (maze[curX][r])
			{
				PQ.push(std::make_pair(nextIndex, curCost + 1));
			}
			else
			{
				PQ.push(std::make_pair(nextIndex, curCost));
			}
		}
	}
	return cost[N * M - 1];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(maze, 0, sizeof(maze));

	std::string temp;
	std::cin >> M >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> temp;
		for (int j = 0; j < M; ++j)
		{
			maze[i][j] = temp[j] - '0';
		}
	}
	std::cout << Dijkstra();
}
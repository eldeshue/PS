
#include <iostream>

int N, M, visitCnt = 0;
constexpr int way[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
int visited[50][50];

// dfs
void search(int curY, int curX, int curDir)
{
	int nextY = -1, nextX = -1, nextDir = curDir;
	// find next empty room
	// anti clock wise, + 4 - 1
	for (int i = 0; i < 4; i++)
	{
		nextDir = (curDir + 3 - i) % 4;
		nextY = curY + way[nextDir][1];
		nextX = curX + way[nextDir][0];
		if (visited[nextY][nextX] == 0)
		{
			visited[nextY][nextX] = 2;
			visitCnt++;
			return search(nextY, nextX, nextDir);
		}
	}
	// no more room to search, go backward
	nextY = curY - way[curDir][1];
	nextX = curX - way[curDir][0];
	if (visited[nextY][nextX] == 2)
			return search(nextY, nextX, curDir);
	// no way to go, return
	return ;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int startY, startX, startDir;
	std::cin >> N >> M >> startY >> startX >> startDir;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			std::cin >> visited[i][j];
		}
	}
	visited[startY][startX] = 2;
	visitCnt++;
	search(startY, startX, startDir);
	std::cout << visitCnt;
}
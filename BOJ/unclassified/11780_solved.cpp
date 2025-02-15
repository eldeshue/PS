// Floyd - Warshall and Tracing back.
#include <iostream>
#include <memory.h>

static const long long INF = 4000000000;
long long graph[101][101]; // adj matrix
int count[101][101]; // edge count, linear 하므로, node의 수는 edge + 1
int path[101][101]; // adj matrix

void printPath(int s, int e)	// 재귀적으로 접근 
{
	int mid = path[s][e];

	if (s == mid)	// base case, 말단을 start와 동일하게 유지
	{
		std::cout << s << " ";	// front만 출력하므로, 최후의 최후 end는 별도로 출력해줘야 함.
	}
	else	// 말단이 아님, 즉 두 노드 사이에는 mid노드가 존재함
	{
		printPath(s, mid);
		printPath(mid, e);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(count, 0, sizeof(count));

	int N, M, s, e, c;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			graph[i][j] = (i == j) ? 0 : INF;
			path[i][j] = i;
		}
	}
	for (int i = 1; i <= M; ++i)
	{
		std::cin >> s >> e >> c;
		if (c < graph[s][e])
		{
			graph[s][e] = c;	// 중복 에지가 있다면, 가장 작은 값으로 유지
			count[s][e] = 1;	// 연결되어 있음, 즉 에지가 존재함. 기본 1개
		}
	}
	// Floyd - Warshall algorithm
	for (int mid = 1; mid <= N; ++mid)
	{
		for (int st = 1; st <= N; ++st)
		{
			if (graph[st][mid] == INF) continue;	// preventing overflow
			for (int ed = 1; ed <= N; ++ed)
			{
				if (graph[mid][ed] == INF) continue;
				// update
				// 계속해서 사이에 끼워넣기, 갱신된 후에는 다시 끼워넣기
				// 일단 이해는 했는데, 굉장히 천재적인 발상이다. 발상의 원리가 이해 안된달까...
				if (graph[st][ed] > graph[st][mid] + graph[mid][ed])	// 기존의 값과 비교
				{
					graph[st][ed] = graph[st][mid] + graph[mid][ed]; // 덮어씀
					count[st][ed] = count[st][mid] + count[mid][ed]; // 에지의 개수 추가
					path[st][ed] = mid;	// 두 노드 사이의 
				}
			}
		}
	}
	//
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (graph[i][j] == INF)
			{
				std::cout << "0 ";
			}
			else
			{
				std::cout << graph[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
	for (int s = 1; s <= N; ++s)
	{
		for (int e = 1; e <= N; ++e)
		{
			if (count[s][e] == 0)
			{
				std::cout << "0\n";
			}
			else
			{
				std::cout << ++count[s][e] << " "; // 노드의 수 = 에지의 수 + 1
				printPath(s, e);
				std::cout << e << "\n";
			}
		}
	}
}
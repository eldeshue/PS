// Floyd - Warshall and Tracing back.
#include <iostream>
#include <memory.h>

static const long long INF = 4000000000;
long long graph[101][101]; // adj matrix
int count[101][101]; // edge count, linear �ϹǷ�, node�� ���� edge + 1
int path[101][101]; // adj matrix

void printPath(int s, int e)	// ��������� ���� 
{
	int mid = path[s][e];

	if (s == mid)	// base case, ������ start�� �����ϰ� ����
	{
		std::cout << s << " ";	// front�� ����ϹǷ�, ������ ���� end�� ������ �������� ��.
	}
	else	// ������ �ƴ�, �� �� ��� ���̿��� mid��尡 ������
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
			graph[s][e] = c;	// �ߺ� ������ �ִٸ�, ���� ���� ������ ����
			count[s][e] = 1;	// ����Ǿ� ����, �� ������ ������. �⺻ 1��
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
				// ����ؼ� ���̿� �����ֱ�, ���ŵ� �Ŀ��� �ٽ� �����ֱ�
				// �ϴ� ���ش� �ߴµ�, ������ õ������ �߻��̴�. �߻��� ������ ���� �ȵȴޱ�...
				if (graph[st][ed] > graph[st][mid] + graph[mid][ed])	// ������ ���� ��
				{
					graph[st][ed] = graph[st][mid] + graph[mid][ed]; // ���
					count[st][ed] = count[st][mid] + count[mid][ed]; // ������ ���� �߰�
					path[st][ed] = mid;	// �� ��� ������ 
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
				std::cout << ++count[s][e] << " "; // ����� �� = ������ �� + 1
				printPath(s, e);
				std::cout << e << "\n";
			}
		}
	}
}

/*
	boj 22967

	�׷����� ���ؼ� �ظ� ��������.

	DAG�� �־�����, �츮�� �� DAG�� ���ؼ� �� ���� edge�� �߰��Ͽ�
	�׷����� ������ �ּҷ� �ٿ��� �Ѵ�.

	�߰��� �� �ִ� ������ ���� N - 1���� �ִ��̴�. <- ���� �߿��� ��Ʈ.

	===========================================================

	�⺻���� ���̵��� ������ 2�� ����� ���̴�.
	������ ��� �ϳ��� �߽����� ���, �ٸ� ��� ��带 �����ϸ�
	�ִ� N - 1(��� �̹� �ϳ��� ����ϰ� �����Ƿ�, �ִ� N - 2)���� ������
	�׷����� ���� 2�� ���� �� �ִ�.

	�ٸ�, Ư���� ��쿡�� �׷����� ������ 1�� ���� �� �ִµ�,
	�̴� N�� 2, 3, 4�� ����̴�.

	�̴� ���� 1�� �׷����� ��������ؼ� ������ N(N - 1)/2�� �ʿ��ѵ�,
	�ִ� 2(N - 1)���� ������ ���� �� �����Ƿ�, N�� 4 ���϶�� ������ 1�� ���� �� �ִ�.

	�� ��츦 ����ó�� ���ָ� �ȴ�.
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using Edge = std::pair<int, int>;

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<bool>> graph(N + 1, std::vector<bool>(N + 1, false));
	for (int i = 0; i < N - 1; ++i)
	{
		int u, v;
		std::cin >> u >> v;
		graph[u][v] = true;
		graph[v][u] = true;
	}

	// max edge count -> 2 * (N - 1)
	// if ( N * (N - 1) / 2 ) <= 2 ( N - 1 ) -> R = 1
	// else R = 2

	// use 1 as root
	int K = 0, R = 0;
	std::vector<Edge> additional_edges;
	if (N <= 4)
	{
		R = 1;
		for (int i = 1; i < N; ++i) {
			for (int j = i + 1; j <= N; ++j) {
				if (!graph[i][j]) {
					++K;
					additional_edges.push_back(Edge(i, j));
				}
			}
		}
	}
	else
	{
		R = 2;
		for (int i = 2; i <= N; ++i)
		{
			if (!graph[1][i])
			{
				++K;
				additional_edges.push_back(Edge(1, i));
			}
		}
	}

	// print
	std::cout << K << '\n' << R << '\n';
	for (auto const [i, j] : additional_edges)
		std::cout << i << ' ' << j << '\n';
}
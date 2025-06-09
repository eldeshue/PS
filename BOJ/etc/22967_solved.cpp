
/*
	boj 22967

	그래프에 대해서 해를 구성하자.

	DAG가 주어지고, 우리는 이 DAG에 대해서 몇 개의 edge를 추가하여
	그래프의 지름을 최소로 줄여야 한다.

	추가할 수 있는 에지의 수는 N - 1개가 최대이다. <- 가장 중요한 힌트.

	===========================================================

	기본적인 아이디어는 지름을 2로 만드는 것이다.
	임의의 노드 하나를 중심으로 잡고, 다른 모든 노드를 연결하면
	최대 N - 1(사실 이미 하나는 사용하고 있으므로, 최대 N - 2)개의 에지로
	그래프를 지름 2로 만들 수 있다.

	다만, 특정한 경우에는 그래프의 지름을 1로 만들 수 있는데,
	이는 N이 2, 3, 4인 경우이다.

	이는 지름 1인 그래프를 만들기위해서 에지가 N(N - 1)/2개 필요한데,
	최대 2(N - 1)개의 에지를 가질 수 있으므로, N이 4 이하라면 지름을 1로 만들 수 있다.

	이 경우를 예외처리 해주면 된다.
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
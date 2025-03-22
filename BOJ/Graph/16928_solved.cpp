
#include <iostream>
#include <queue>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;
	std::vector<int> board(101, 0);
	std::vector<int> visited(101, -1);

	// input
	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		int x, y;
		std::cin >> x >> y;
		board[x] = y;
	}
	for (int i = 0; i < M; ++i)
	{
		int u, v;
		std::cin >> u >> v;
		board[u] = v;
	}

	// bfs, state space
	auto InRange = [](int const node) { return ((0 <= node) && (node <= 100)); };
	std::queue<pii> q;
	visited[1] = 0;
	q.push(std::make_pair(1, 0));
	while (!q.empty())
	{
		auto const [cur_node, cur_cnt] = q.front();
		q.pop();
		for (int offset = 1; offset <= 6; ++offset)
		{
			int next_node = cur_node + offset;
			if (InRange(next_node) && visited[next_node] == -1)
			{
				visited[next_node] = cur_cnt + 1;
				if (board[next_node])	// jump, ladder or snake
				{
					next_node = board[next_node];
					visited[next_node] = cur_cnt + 1;
				}
				q.push(std::make_pair(next_node, cur_cnt + 1));
			}
		}
	}
	std::cout << visited[100];
}
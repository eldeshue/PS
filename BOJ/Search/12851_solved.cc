
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	constexpr const int LIMIT = 100'000;
	int N, K;
	std::cin >> N >> K;

	// bfs
	int result = 0;
	std::vector<int> costs(LIMIT + 1, -1);
	std::vector<int> cnts(LIMIT + 1, 0);
	std::queue<pii> q;
	costs[N] = 0;
	cnts[N] = 1;
	q.push(std::make_pair(0, N));
	while (!q.empty())
	{
		auto const [curCost, curNode] = q.front();
		q.pop();

		// down
		int nextNode = curNode - 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& (costs[nextNode] == -1 || costs[nextNode] == curCost + 1))
		{
			costs[nextNode] = curCost + 1;
			++cnts[nextNode];
			q.push(std::make_pair(curCost + 1, nextNode));
		}

		// up
		nextNode = curNode + 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& (costs[nextNode] == -1 || costs[nextNode] == curCost + 1))
		{
			costs[nextNode] = curCost + 1;
			++cnts[nextNode];
			q.push(std::make_pair(curCost + 1, nextNode));
		}

		// shift
		nextNode = curNode << 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& (costs[nextNode] == -1 || costs[nextNode] == curCost + 1))
		{
			costs[nextNode] = curCost + 1;
			++cnts[nextNode];
			q.push(std::make_pair(curCost + 1, nextNode));
		}
	}

	// print
	std::cout << costs[K] << '\n' << cnts[K] << '\n';
}
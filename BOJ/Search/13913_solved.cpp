
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
	std::vector<int> parents(LIMIT + 1, -1);
	std::queue<pii> q;
	q.push(std::make_pair(0, N));
	while (!q.empty())
	{
		auto const [curCost, curNode] = q.front();
		q.pop();

		if (curNode == K)	// arrived
		{
			result = curCost;
			break;
		}

		// down
		int nextNode = curNode - 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& parents[nextNode] == -1)
		{
			parents[nextNode] = curNode;
			q.push(std::make_pair(curCost + 1, nextNode));
		}

		// up
		nextNode = curNode + 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& parents[nextNode] == -1)
		{
			parents[nextNode] = curNode;
			q.push(std::make_pair(curCost + 1, nextNode));
		}

		// shift
		nextNode = curNode << 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& parents[nextNode] == -1)
		{
			parents[nextNode] = curNode;
			q.push(std::make_pair(curCost + 1, nextNode));
		}
	}

	// print
	std::stack<int> st;
	st.push(K);
	while (st.top() != N) st.push(parents[st.top()]);

	std::cout << result << '\n';
	while (!st.empty())
	{
		std::cout << st.top() << ' ';
		st.pop();
	}
}

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

	constexpr const int LIMIT = 1000'000;
	int N;
	std::cin >> N;

	// bfs
	int result = 0;
	std::queue<pii> q;
	std::vector<int> parents(LIMIT + 1, -1);
	q.push(std::make_pair(0, N));
	while (!q.empty())
	{
		auto const [curCost, curNode] = q.front();
		q.pop();

		if (curNode == 1)
		{
			result = curCost;
			break;
		}

		int nextNode = curNode - 1;
		if (0 <= nextNode && nextNode <= LIMIT
			&& parents[nextNode] == -1)
		{
			parents[nextNode] = curNode;
			q.push(std::make_pair(curCost + 1, nextNode));
		}

		if ((curNode % 3) == 0)
		{
			nextNode = curNode / 3;
			if (0 <= nextNode && nextNode <= LIMIT
				&& parents[nextNode] == -1)
			{
				parents[nextNode] = curNode;
				q.push(std::make_pair(curCost + 1, nextNode));
			}
		}

		if ((curNode % 2) == 0)
		{
			nextNode = curNode / 2;
			if (0 <= nextNode && nextNode <= LIMIT
				&& parents[nextNode] == -1)
			{
				parents[nextNode] = curNode;
				q.push(std::make_pair(curCost + 1, nextNode));
			}
		}
	}

	std::stack<int> st;
	int curNode = 1;
	while (curNode != -1)
	{
		st.push(curNode);
		curNode = parents[curNode];
	}

	// print
	std::cout << result << '\n';
	while (!st.empty())
	{
		std::cout << st.top() << ' ';
		st.pop();
	}
}
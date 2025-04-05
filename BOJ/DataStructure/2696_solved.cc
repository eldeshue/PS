
#include <iostream>
#include <vector>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		std::priority_queue<int, std::vector<int>, std::less<int>> lPq;
		std::priority_queue<int, std::vector<int>, std::greater<int>> hPq;
		int M, n, mid;
		std::cin >> M >> mid;
		std::vector<int> result(1, mid);
		for (int i = 2; i <= M; ++i)
		{
			std::cin >> n;
			if (n < mid)
			{
				lPq.push(n);
			}
			else
			{
				hPq.push(n);
			}

			if (i & 1)	// balancing
			{
				if (hPq.size() > lPq.size())
				{
					lPq.push(mid);
					mid = hPq.top();
					hPq.pop();
				}
				else if (hPq.size() < lPq.size())
				{
					hPq.push(mid);
					mid = lPq.top();
					lPq.pop();
				}
				result.push_back(mid);
			}
		}

		// print
		std::cout << result.size();
		for (int i = 0; i < result.size(); ++i)
		{
			if ((i % 10) == 0)
			{
				std::cout << '\n';
			}
			std::cout << result[i] << ' ';
		}
		std::cout << '\n';
	}
}

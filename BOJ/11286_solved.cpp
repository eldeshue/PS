
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

struct cmpAbs
{
	bool operator()(int m, int n)
	{
		if (std::abs(m) == std::abs(n))
		{
			return m > n;
		}
		else
		{
			return std::abs(m) > std::abs(n);
		}
	}
};


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::priority_queue<int, std::vector<int>, cmpAbs> pq;
	int N, input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		if (input == 0)
		{
			if (pq.size() == 0)
			{
				std::cout << 0 << "\n";
			}
			else
			{
				std::cout << pq.top() << "\n";
				pq.pop();
			}
		}
		else
		{
			pq.push(input);
		}
	}
}
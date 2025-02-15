
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> N >> K;
	std::vector<int> coins(N);
	for (int i = 0; i < N; ++i)
		std::cin >> coins[i];
	std::vector<int> cache(K + 1, 0);
	// dp
	cache[0] = 1;
	for (const int &c : coins)
	{
		for (int curVal = 0; curVal < K; ++curVal)
		{
			int nextVal = curVal + c;
			if (cache[curVal] != 0 && nextVal <= K)
			{
				cache[nextVal] += cache[curVal];
			}
		}
	}
	std::cout << cache[K];
}
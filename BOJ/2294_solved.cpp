
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
	for (int& c : coins)
		std::cin >> c;
	std::vector<int> cache(K + 1, 2e9);
	cache[0] = 0;
	for (int& c : coins)
	{
		for (int curVal = c; curVal <= K; ++curVal)
		{
			if (cache[curVal - c] != 2e9)
			{
				cache[curVal] = std::min(cache[curVal], cache[curVal - c] + 1);
			}
		}
	}
	if (cache[K] == 2e9)
		std::cout << -1;
	else
		std::cout << cache[K];
}
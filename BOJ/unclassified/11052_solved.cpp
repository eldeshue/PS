
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// max costs
	std::cin >> N;
	std::vector<int> costs(N + 1);
	std::vector<int> cache(N + 1, 0);	// cache[card num] = max cost
	for (int i = 1; i <= N; ++i)
		std::cin >> costs[i];

	for (int packSize = 1; packSize <= N; ++packSize)
	{
		const int packCost = costs[packSize];
		for (int cardNum = packSize; cardNum <= N; ++cardNum)
		{
			cache[cardNum] = std::max(cache[cardNum],
				cache[cardNum - packSize] + packCost);
		}
	}
	std::cout << cache[N];
}
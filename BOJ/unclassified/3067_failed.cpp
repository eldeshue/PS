
#include <iostream>
#include <memory.h>
#include <vector>

std::vector<int> coins;
int cache[10001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T, N, M, input;
	std::cin >> T;
	for (int i = 0; i < T; ++i)
	{
		memset(cache, 0, sizeof(cache));
		coins.clear();
		std::cin >> N;
		for (int j = 0; j < N; ++j)
		{
			std::cin >> input;
			coins.push_back(input);
			cache[input] = 1;
		}
		std::cin >> M;
		for (int val = 1; val <= M; ++val)
		{
			for (const auto& coin : coins)
			{
				int prev_val = val - coin;
				if (prev_val >= 0)
					cache[val] += cache[prev_val];
			}
		}
		std::cout << cache[M] << '\n';
	}
}

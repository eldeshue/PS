
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

#define INFINETE 3e9
using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::array<std::array<ll, 500>, 500> cache;

	int T, K;
	std::cin >> T;
	while (T--)
	{
		std::for_each(cache.begin(), cache.end(), [](std::array<ll, 500> &arr) -> void
					  { std::fill(arr.begin(), arr.end(), INFINETE); });
		std::cin >> K;
		std::vector<ll> sum(K);
		std::cin >> cache[0][0];
		sum[0] = cache[0][0];
		for (int i = 1; i < K; ++i)
		{
			std::cin >> cache[i][i];
			sum[i] = cache[i][i] + sum[i - 1];
		}
		// memoization
		std::function<ll(int, int)> dp = [&](int start, int end) -> ll
		{
			if (cache[start][end] == INFINETE) // cache miss
			{
				ll &curVal = cache[start][end];
				for (int mid = start; mid < end; ++mid)
					curVal = std::min(curVal, dp(start, mid) + dp(mid + 1, end));
				curVal += sum[end];
				if (start > 0)
					curVal -= sum[start - 1];
			}
			return cache[start][end];
		};
		std::cout << dp(0, K - 1) - sum[K - 1] << '\n';
	}
}

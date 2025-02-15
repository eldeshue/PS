
#include <iostream>
#include <functional>
#include <vector>

using ll = long long;
#define MAX_LEN 1000001
#define MOD 1000000009

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N, K;
	std::vector<std::vector<ll>> cache(MAX_LEN, std::vector<ll>(2, -1));
	std::cin >> N >> K;
	std::vector<ll> totalCount(N + 1, 1);
	// prepare total count
	for (int i = 1; i <= N; ++i)
		totalCount[i] = (totalCount[i - 1] * K) % MOD;
	// dp,
	std::function<ll(const ll, const ll)> memoize = [&](const ll n, const ll isPattern) -> ll
	{
		if (n < 0) // overlap exception handling
		{
			return 0;
		}
		else if (cache[n][isPattern] != -1) // cache hit
		{
			return cache[n][isPattern];
		}
		else if (n < 5) // base case
		{
			if (isPattern)
			{
				return cache[n][1] = 0;
			}
			else
			{
				return cache[n][0] = totalCount[n];
			}
		}
		else // cache miss
		{
			if (isPattern) // cache miss, is pattern
			{
				cache[n][1] = 0; // (K * memoize(n - 1, 1)) % MOD;
				// overlap handling, ABABCBC
				ll powOfK = 1;
				for (int i = 0; i < 5; ++i)
				{
					cache[n][1] = (cache[n][1] + 2 * powOfK * memoize(n - i - 5, 0)) % MOD;
					powOfK *= K;
				}
				powOfK = 1;
				for (int i = 0; i < 5; ++i)
				{
					cache[n][1] = (cache[n][1] - powOfK * memoize(n - i - 7, 0));
					powOfK *= K;
				}
				// ???
				return cache[n][1];
			}
			else // cache miss, no pattern
			{
				return cache[n][0] = totalCount[n] - memoize(n, 1);
			}
		}
	};
	std::cout << memoize(N, 0);
}

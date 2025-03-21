
#include <iostream>
#include <memory.h>

int cache[12];

int dp(int n)
{
	if (cache[n] != -1) // cache hit
		return cache[n];
	else	// cache miss
		return dp(n - 1) + dp(n - 2) + dp(n - 3);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));
	cache[1] = 1;
	cache[2] = 2;
	cache[3] = 4;

	int T, n;
	std::cin >> T;
	for (int i = 0; i < T; ++i)
	{
		std::cin >> n;
		std::cout << dp(n) << '\n';
	}
}

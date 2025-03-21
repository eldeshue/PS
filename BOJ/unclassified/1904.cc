
#include <iostream>
#include <memory.h>

int cache[1000001];

int dp(int n)
{
	if (n == 1)
		return cache[n] = 1;
	else if (n == 2)
		return cache[n] = 2;
	else if (cache[n] != 0)
		return cache[n];
	else
		return cache[n] = dp(n - 1) + dp(n - 2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	int N;
	std::cin >> N;
	std::cout << dp(N);
}


#include <iostream>
#include <memory.h>

int numColum;
int cache[100001];

int DP(int n)
{
	int& val = cache[n];
	if (val != 0) // cache hit
	{
		return val;
	}
	else // cache miss
	{
		return val = (2 * DP(n - 1) + DP(n - 2)) % 9901;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	memset(cache, 0, sizeof(cache));
	cache[0] = 1;
	cache[1] = 3;

	std::cin >> numColum;
	std::cout << DP(numColum);
}
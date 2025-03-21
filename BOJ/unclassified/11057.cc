
#include <iostream>
#include <memory.h>

int cache[1001][10];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	// init first step, the result number can start from 0
	for (int i = 0; i < 10; ++i)
		cache[1][i] = 1;
	int N;
	std::cin >> N;
	for (int step = 2; step <= N; ++step)	// step
	{
		for (int cur = 0; cur < 10; ++cur)	// cur number
		{
			for (int prev = 0; prev <= cur; ++prev)	// prev number
			{
				cache[step][cur] = (cache[step][cur] + cache[step -1][prev]) % 10007;
			}
		}
	}
	int result = 0;
	for (int i = 0; i < 10; ++i)
	{
		result = (result + cache[N][i]) % 10007;
	}
	std::cout << result;
}

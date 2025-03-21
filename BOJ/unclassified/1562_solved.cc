
#include <iostream>
#include <memory.h>

using uint = unsigned int;
constexpr uint divider = 1000000000;

uint cache[101][10][1 << 10];	// bit masking
								// 4 * 101 * 10 * 1024 = near 4MB

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	int N;
	std::cin >> N;
	// init, length == 1
	for (int num = 1; num < 10; ++num)
	{
		cache[1][num][1 << num] = 1;
	}
	// tabulation.
	for (int len = 1; len < N; ++len)
	{
		for (int status = 0; status < 1024; ++status)
		{
			cache[len + 1][1][status | (1 << 1)] += cache[len][0][status];
			cache[len + 1][1][status | (1 << 1)] %= divider;
			cache[len + 1][8][status | (1 << 8)] += cache[len][9][status];
			cache[len + 1][8][status | (1 << 8)] %= divider;
		}
		for (int last = 1; last < 9; ++last)
		{
			for (int status = 0; status < 1024; ++status)
			{
				cache[len + 1][last - 1][status | (1 << (last - 1))] += cache[len][last][status];
				cache[len + 1][last - 1][status | (1 << (last - 1))] %= divider;
				cache[len + 1][last + 1][status | (1 << (last + 1))] += cache[len][last][status];
				cache[len + 1][last + 1][status | (1 << (last + 1))] %= divider;
			}
		}
	}
	uint result = 0;
	for (int i = 0; i < 10; ++i)
	{
		result += cache[N][i][1023];
		result %= divider;
	}
	std::cout << '\n' << result;
}

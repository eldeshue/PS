/*
	BOJ 1176

	bitmasking dp
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using ll = long long;
ll nums[16];
ll cache[2][16][1 << 16];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::memset(cache, 0, sizeof(cache));

	int N, K;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
		std::cin >> nums[i];

	// cache init
	for (int i = 0; i < N; ++i)
	{
		cache[1][i][1 << i] = 1;
	}

	int cidx = 0, pidx = 1;
	for (int cnt = 2; cnt < N; ++cnt)
	{
		for (int i = 0; i < N; ++i)
		{
			int const cur = nums[i];
			for (int j = 0; j < N; ++j)
			{
				int const prev = nums[j];
				for (int stat = 0; stat < (1 << N); ++stat)
				{
					if (((1 << i) & stat) == 0 && std::abs(cur - prev) > K)
					{
						cache[cidx][i][(1 << i) | stat] += cache[pidx][j][stat];
					}
				}
			}
		}
		std::swap(cidx, pidx);
		std::memset(&cache[cidx], 0, sizeof(ll) * (16 * (1 << 16)));
	}

	long long result = 0;
	for (int i = 0; i < N; ++i)
	{
		int const cur = nums[i];
		for (int j = 0; j < N; ++j)
		{
			int const prev = nums[j];
			for (int stat = 0; stat < (1 << N); ++stat)
			{
				// do not overlap and gap must be bigger than K
				if (((1 << i) & stat) == 0 && std::abs(cur - prev) > K)
				{
					result += cache[pidx][j][stat];
				}
			}
		}
	}
	std::cout << result;
}

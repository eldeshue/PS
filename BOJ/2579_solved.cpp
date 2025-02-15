
#include <iostream>
#include <memory.h>

int N;
int stairs[301];
int cache[301][2];

void DP(int level, int cnt)
{
	if (level == N)
	{
		return;
	}
	int nextVal;
	if (cnt != 1)
	{
		nextVal = cache[level][cnt] + stairs[level + 1];
		if (cache[level + 1][cnt + 1] < nextVal)
		{
			cache[level + 1][cnt + 1] = nextVal;
			DP(level + 1, cnt + 1);
		}
	}
	if (level + 2 <= N)
	{
		nextVal = cache[level][cnt] + stairs[level + 2];
		if (cache[level + 2][0] < nextVal)
		{
			cache[level + 2][0] = nextVal;
			DP(level + 2, 0);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> stairs[i];
	}
	
	DP(0, -1);
	int result = 0;
	for (int i = 0; i < 2; ++i)
	{
		result = std::max(result, cache[N][i]);
	}
	std::cout << result;
}
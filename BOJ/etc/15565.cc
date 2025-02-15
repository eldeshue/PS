
#include <iostream>
#include <bitset>

std::bitset<1000000> dolls;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, winSize;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> winSize;
		dolls[i] = 1 & winSize;
	}
	winSize = K;
	int startCnt = 0;
	for (int i = 0; i < winSize; ++i)
		startCnt += dolls[i];
	while (winSize <= N)
	{
		int cnt = startCnt, start = 1, end = winSize;
		for (; end < N; ++start, ++end)
		{
			cnt += dolls[end];
			cnt -= dolls[start - 1];
			if (cnt >= K)
			{
				std::cout << winSize;
				return 0;
			}
		}
		startCnt += dolls[winSize];
		winSize++;
	}
	// no such window
	std::cout << -1;
	return 0;
}

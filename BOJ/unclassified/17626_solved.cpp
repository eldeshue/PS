
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<int> cache(50001, -1);
	cache[0] = 0;

	int N;
	std::cin >> N;
	// dp, tabulation
	for (int i = 224; i > 0; --i)
	{
		const int curVal = i * i;
		for (int j = 0; j < 4; ++j)	// 중복이 허용되는 조건이므로, 4번은 돌려봐야 함.
		{
			for (int sum = 50000; sum >= curVal; --sum)
			{
				if (cache[sum - curVal] != -1)
				{
					if (cache[sum] == -1)
						cache[sum] = cache[sum - curVal] + 1;
					else
						cache[sum] = std::min(cache[sum], cache[sum - curVal] + 1);
				}
			}
		}
	}
	/*
	for (int i = 0; i <= 50000; ++i)
	{
		if (cache[i] > 4)
			std::cout << i << " : " << cache[i] << '\n';
	}
	*/
	std::cout << cache[N];
}
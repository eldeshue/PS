
#include <iostream>
#include <memory.h>

int cache[15][15];

int getVal(int floor, int door)
{
	if (cache[floor][door] != -1)
	{
		return cache[floor][door];
	}
	else
	{
		return cache[floor][door] = getVal(floor - 1, door) + getVal(floor, door - 1);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int i = 1; i < 15; ++i)
	{
		cache[0][i] = i;
		cache[i][1] = 1;
		memset(cache[i] + 1, -1, 14 * sizeof(int));
	}

	int testNum, k, n;
	std::cin >> testNum;
	for (int i = 0; i < testNum; ++i)
	{
		std::cin >> k >> n;
		std::cout << getVal(k, n) << "\n";
	}
}
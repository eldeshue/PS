
#include <iostream>
#include <memory.h>

int cache[46];

int getVal(int n)
{
	if (cache[n] != -1)
	{
		return cache[n];
	}
	else
	{
		return cache[n] = getVal(n - 1) + getVal(n - 2);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	memset(cache + 2, -1, 44 * sizeof(int));
	cache[0] = 1;
	cache[1] = 1;

	int testNum, input;
	std::cin >> testNum;
	for (int i = 0; i < testNum; ++i)
	{
		std::cin >> input;
		std::cout << getVal(input) << "\n";
	}
}

#include <iostream>

int cache[46][2];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	cache[0][0] = 1;
	cache[0][1] = 0;
	cache[1][0] = 0;
	cache[1][1] = 1;

	for (int i = 2; i <= 45; ++i)
	{
		cache[i][0] = cache[i - 1][0] + cache[i - 2][0];
		cache[i][1] = cache[i - 1][1] + cache[i - 2][1];
	}

	int input;
	std::cin >> input;
	std::cout << cache[input][0] << " " << cache[input][1];
}

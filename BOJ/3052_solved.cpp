
#include <iostream>
#include <memory.h>

int rest[42];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(rest, 0, sizeof(rest));

	int num;
	for (int i = 0; i < 10; ++i)
	{
		std::cin >> num;
		rest[num % 42]++;
	}
	int result = 0;
	for (int i = 0; i < 42; ++i)
	{
		if (rest[i] != 0)
		{
			result++;
		}
	}
	std::cout << result;
}
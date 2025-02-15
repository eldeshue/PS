// failed, big number needed.
#include <iostream>
#include <memory.h>

unsigned long long int cache[491];

unsigned long long int getFibonacci(int n)
{
	if (cache[n] != -1)
	{
		return cache[n];
	}
	else
	{
		return cache[n] = getFibonacci(n - 1) + getFibonacci(n - 2);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	memset(cache + 2, -1, 489 * sizeof(int));
	cache[0] = 0;
	cache[1] = 1;

	int input = 0;
	while (true)
	{
		std::cin >> input;
		if (input == -1)
		{
			return 0;
		}
		std::cout <<"Hour " << input << ": " 
			<< getFibonacci(input) << " cow(s) affected\n";
	}
}
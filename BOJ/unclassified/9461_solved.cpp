
#include <iostream>
#include <memory.h>

// f(n) = f(n - 2) + f(n- 3)
long long cache[101];

long long padovan(int n)
{
	if (cache[n] != -1)
	{
		return cache[n];
	}
	else if (n <= 3)
	{
		return cache[n] = 1;
	}
	return cache[n] = padovan(n - 2) + padovan(n - 3);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int numTest, N;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		std::cin >> N;
		std::cout << padovan(N) << '\n';
	}
}
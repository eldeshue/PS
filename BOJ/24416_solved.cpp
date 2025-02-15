
#include <iostream>
#include <memory.h>

int N, RecurseCount = 0, DPCount = 0;
int cache[41];

int RecurseFib(int n)
{
	if (n == 1 || n == 2)
	{
		RecurseCount++;
		return 1;
	}
	else
	{
		return RecurseFib(n - 1) + RecurseFib(n - 2);
	}
}

int DPFib(int n)
{
	if (cache[n] != -1)
	{
		return cache[n];
	}
	else
	{
		DPCount++;
		return (cache[n] = DPFib(n - 1) + DPFib(n - 2));
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	std::cin >> N;
	RecurseFib(N);

	cache[1] = 1;
	cache[2] = 1;
	DPFib(N);

	std::cout << RecurseCount << " " << DPCount;
}
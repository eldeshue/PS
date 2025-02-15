
#include <iostream>

int permutate(int m, int n)
{
	int result = 1;
	for (int i = m; i > m - n; --i)
	{
		result *= i;
	}
	return result;
}

int factorial(int n)
{
	int result = 1;
	for (int i = 1; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> N >> K;
	std::cout << permutate(N, K) / factorial(K) << "\n";
}

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, coins[10], result = 0;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> coins[i];
	}
	for (int i = N - 1; i >= 0; --i)
	{
		if (K >= coins[i])
		{
			result += K / coins[i];
			K %= coins[i];
		}
	}
	std::cout << result;
}
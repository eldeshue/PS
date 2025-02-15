
#include <iostream>
#include <vector>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<std::vector<ll>> cache(N, std::vector<ll>(2, 0));
	cache[0][1] = 1;
	// dp
	for (int i = 1; i < N; ++i)
	{
		cache[i][0] = cache[i - 1][0] + cache[i - 1][1];
		cache[i][1] = cache[i - 1][0];
	}
	std::cout << cache[N - 1][0] + cache[N - 1][1];
}
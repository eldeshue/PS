
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
	std::vector<std::vector<ll>> cache(N + 1, std::vector<ll>(8, 0));
	cache[0][0] = 1;
	cache[1][1] = 1;
	cache[1][2] = 0;
	cache[1][4] = 1;
	cache[1][7] = 3;
	for (int i = 2; i <= N; ++i)
	{
		cache[i][0] = cache[i - 1][7];
		cache[i][1] = cache[i - 1][6];
		cache[i][2] = cache[i - 1][5];
		cache[i][3] = cache[i][0] + cache[i - 1][4];
		cache[i][4] = cache[i][1];
		cache[i][5] = cache[i - 1][2];
		cache[i][6] = cache[i][3];
		cache[i][7] = cache[i][1] + cache[i][4]
			+ cache[i - 1][0];
	}
	std::cout << cache[N][0];
}
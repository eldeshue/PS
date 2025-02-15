
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<int> wines(N);
	std::vector<std::vector<int>> cache(N, std::vector<int>(4, 0));
	for (int i = 0; i < N; ++i)
	{
		std::cin >> wines[i];
	}
	// tabulation
	// 0 : 00
	// 1 : 10
	// 2 : 01
	// 3 : 11
	cache[0][0] = 0;
	cache[0][1] = 0;
	cache[0][2] = wines[0];
	cache[0][3] = wines[0];
	for (int i = 1; i < N; ++i)
	{
		cache[i][0] = std::max(cache[i - 1][0], cache[i - 1][1]);
		cache[i][1] = std::max(cache[i - 1][2], cache[i - 1][3]);
		cache[i][2] = cache[i][0] + wines[i];
		cache[i][3] = cache[i - 1][2] + wines[i];
	}
	int result = 0;
	std::for_each(cache[N - 1].begin(), cache[N - 1].end(), [&](const int &v) -> void
				  { result = std::max(result, v); });
	std::cout << result;
}

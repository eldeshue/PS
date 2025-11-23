/*
	BOJ 20162

	6
	1 2 8 4 5 7
*/
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<int> num(N);
	for (auto& n : num)
		std::cin >> n;

	// dp
	std::vector<int> cache(N, 0);
	for (int i = 0; i < N; ++i)
	{
		int prev_val = 0;
		for (int j = 0; j < i; ++j)
		{
			if (num[j] < num[i])
			{
				prev_val = std::max(prev_val, cache[j]);
			}
		}
		cache[i] = prev_val + num[i];
	}

	// print result
	std::cout << std::accumulate(cache.begin(), cache.end(), 0,
		[](int const acc, auto const p) {
			return std::max(acc, p);
		});
}

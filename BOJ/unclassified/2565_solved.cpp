
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	// input
	int N;
	std::cin >> N;
	std::vector<pii> edges(N);
	for (int i = 0; i < N; ++i)
		std::cin >> edges[i].first >> edges[i].second;

	// sort by first, use second only
	// O(n log n)
	std::sort(edges.begin(), edges.end(), std::less<pii>());

	// solution : LIS of second
	// O(n log n)
	std::vector<int> cache(N + 1, 2e9);
	cache[0] = 0;
	int lenLis = 0;
	for (auto const [_, n] : edges)
	{
		auto curPos = std::lower_bound(cache.begin(), cache.end(), n);
		*curPos = std::min(*curPos, n);
		int const curLen = curPos - cache.begin();
		lenLis = std::max(lenLis, curLen);
	}

	// print result
	std::cout << N - lenLis;
}
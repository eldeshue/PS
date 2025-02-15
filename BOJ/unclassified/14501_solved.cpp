
#include <iostream>
#include <vector>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<pii> meetings(N);
	std::vector<int> cache(N + 1, 0);
	for (int i = 0; i < N; ++i)
		std::cin >> meetings[i].first >> meetings[i].second;
	for (int pos = N - 1; pos >= 0; --pos)
	{
		if (pos < N - 1)
			cache[pos] = cache[pos + 1];
		if (pos + meetings[pos].first <= N)
			cache[pos] = std::max(cache[pos],
				cache[pos + meetings[pos].first] + meetings[pos].second);
	}
	std::cout << cache[0];
}
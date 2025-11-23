/*
	BOJ 6076

	심플한 01배낭문제, 1차원 dp
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int C, H;
	std::cin >> C >> H;
	std::vector<int> costs(H);
	for (auto& c : costs)
		std::cin >> c;

	// dp, tabulation
	std::vector<bool> cache(C + 1, false);	// is reachable
	cache[0] = true;
	for (auto const c : costs)
	{
		for (int i = C - c; i >= 0; --i)
		{
			cache[i + c] = cache[i + c] || cache[i];
		}
	}

	for (int i = C; i >= 0; --i)
	{
		if (cache[i])
		{
			std::cout << i;
			break;
		}
	}
	return 0;
}


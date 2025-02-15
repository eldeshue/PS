
// Naive, failed.

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <memory.h>

using item = std::tuple<int, int, int>;
std::vector<item> items;
int cache[10000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int N, MW, v, c, k;
	std::cin >> N >> MW;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> v >> c >> k;
		items.push_back(std::make_tuple(v, c, k));
	}
	cache[0] = 0;
	for (int inum = 0; inum < items.size(); ++inum)
	{
		const int& cur_cap = std::get<0>(items[inum]);
		const int& cur_val = std::get<1>(items[inum]);
		const int& cur_ea = std::get<2>(items[inum]);
		for (int prev_weight = MW; prev_weight >= cur_cap; --prev_weight)
		{
			if (cache[prev_weight - cur_cap] != -1)
			{
				for (int cnt = 0; cnt < cur_ea; ++cnt)
				{
					if (prev_weight + cnt * cur_cap > MW) break;
					cache[prev_weight + cnt * cur_cap]
						= std::max(cache[prev_weight + cnt * cur_cap]
							, cache[prev_weight + (cnt - 1) * cur_cap] + cur_val);
				}
			}
		}
	}
	int result = 0;
	for (int i = 0; i <= MW; ++i)
	{
		result = std::max(result, cache[i]);
	}
	std::cout << result;
}
/*
	BOJ 30891

	단순 구현
*/
#include <iostream>
#include <vector>
#include <numeric>

using Point = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, R;
	std::cin >> N >> R;
	std::vector<Point> p(N);
	for (auto& [x, y] : p)
		std::cin >> x >> y;

	int max_cnt = 0;
	Point max_pos = {};
	for (int x = -100; x <= 100; ++x)
	{
		for (int y = -100; y <= 100; ++y)
		{
			int cur_cnt = std::accumulate(p.begin(), p.end(), 0,
				[&](int acc, Point const& pos) {
					int const dx = pos.first - x;
					int const dy = pos.second - y;
					return (acc + ((dx * dx + dy * dy) <= R * R));
				});
			if (cur_cnt > max_cnt)
			{
				max_cnt = cur_cnt;
				max_pos = { x, y };
			}
		}
	}

	std::cout << max_pos.first << ' ' << max_pos.second;
}


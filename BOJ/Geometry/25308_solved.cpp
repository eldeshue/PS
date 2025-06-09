#include <cmath>
#include <functional>
#include <iostream>
#include <numbers>
#include <vector>

using ll = double;
using Point = std::pair<ll, ll>;
#define X first
#define Y second

constexpr const Point pivot = { -1, -1 };

int ccw(const Point& v1, const Point& v2)
{
	ll product = v1.X * v2.Y - v1.Y * v2.X;
	if (product > 0)
		return 1;
	else if (product < 0)
		return -1;
	else
		return 0;
}

Point vec_sub(const Point& v1, const Point& v2)
{
	return std::make_pair(v1.X - v2.X, v1.Y - v2.Y);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	std::vector<int> input(8);
	for (auto& n : input)
		std::cin >> n;

	int result = 0;
	std::vector<int> lengths(8);
	std::vector<bool> is_used(8, false);
	std::vector<Point> points(10);
	std::function<void(int)> back_track = [&](int cur_pos) {
		if (cur_pos == 8)
		{
			// build points
			for (int i = 0; i < 8; ++i)
			{
				double angle = std::numbers::pi * i / 4.0;
				int len = lengths[i];
				points[i] = std::make_pair(len * cos(angle), len * sin(angle));
			}
			points[8] = points[0];
			points[9] = points[1];

			// check result
			bool is_all_ccw = true;
			for (int i = 0; i < 8; ++i)
			{
				if (ccw(vec_sub(points[i + 1], points[i]),
					vec_sub(points[i + 2], points[i + 1])) < 0)
				{
					is_all_ccw = false;
					break;
				}
			}
			result += is_all_ccw;
			return;
		}

		// back tracking
		for (int i = 0; i < 8; ++i)
		{
			if (!is_used[i])
			{
				is_used[i] = true;
				lengths[cur_pos] = input[i];
				back_track(cur_pos + 1);
				is_used[i] = false;
			}
		}
		};
	back_track(0);
	std::cout << result;
}
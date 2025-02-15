
#include <iostream>
#include <algorithm>
#include <vector>

using point = std::pair<int, int>;
std::vector<point> points;

struct comp
{
	bool operator()(const point& p1, const point& p2)
	{
		if (p1.second == p2.second)
			return p1.first < p2.first;
		return p1.second < p2.second;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, x, y;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> x >> y;
		points.push_back(std::make_pair(x, y));
	}
	std::sort(points.begin(), points.end(), comp());
	for (const auto& point : points)
	{
		std::cout << point.first << ' ' << point.second << '\n';
	}
}
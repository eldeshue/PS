// 내적을 이용한 정사각형 판단
#include <iostream>
#include <array>

using point = std::pair<long long, long long>;
std::array<point, 4> points;

long long dot(const point& v1, const point& v2)
{
	return v1.first * v2.first + v1.second * v2.second;
}

bool is_square()
{
	// vectorize
	for (int i = 1; i < 4; ++i)
	{
		points[i].first -= points[0].first;
		points[i].second -= points[0].second;
	}
	long long d1 = dot(points[1], points[2]);
	long long d2 = dot(points[2], points[3]);
	long long d3 = dot(points[1], points[3]);
	if (d1 == 0)
	{
		long long temp = dot(points[2], points[2]);
		if (d2 > 0 && temp == d2 && temp == d3)
			return true;
	}
	else if (d2 == 0)
	{
		long long temp = dot(points[2], points[2]);
		if (d1 > 0 && temp == d1 && temp == d3)
			return true;
	}
	else if (d3 == 0)
	{
		long long temp = dot(points[1], points[1]);
		if (d1 > 0 && temp == d1 && temp == d2)
			return true;
	}
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num_case;
	std::cin >> num_case;
	for (int i = 0; i < num_case; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cin >> points[j].first >> points[j].second;
		}
		if (is_square())
			std::cout << 1 << '\n';
		else
			std::cout << 0 << '\n';
	}
}
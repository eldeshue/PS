
#include <iostream>
#include <array>

using ll = long long;
using vec = std::pair<long long, long long>;

ll ccw(const vec& p1, const vec& p2, const vec& p3)
{
	ll x12 = p2.first - p1.first;
	ll y12 = p2.second - p1.second;
	ll x13 = p3.first - p1.first;
	ll y13 = p3.second - p1.second;
	ll result = x12 * y13 - y12 * x13;
	if (result > 0)	return 1;	// ccw
	else if	(result == 0) return 0;	// on line	
	else return -1;	// cw
}

bool is_cross(std::array<vec, 4>& two_line)
{
	ll divide12 = ccw(two_line[0], two_line[1], two_line[2]) 
		* ccw(two_line[0], two_line[1], two_line[3]);
	ll divide34 = ccw(two_line[2], two_line[3], two_line[0]) 
		* ccw(two_line[2], two_line[3], two_line[1]);
	if (divide12 == 0 && divide34 == 0)
	{
		if (two_line[0] > two_line[1]) std::swap(two_line[0], two_line[1]);
		if (two_line[2] > two_line[3]) std::swap(two_line[2], two_line[3]);
		return (two_line[0] <= two_line[3]) && (two_line[2] <= two_line[1]);
	}
	return (divide12 <= 0) && (divide34 <= 0);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::array<vec, 4> two_line;
	for (int i = 0; i < 4; ++i)
		std::cin >> two_line[i].first >> two_line[i].second;
	if (is_cross(two_line))
		std::cout << 1;
	else
		std::cout << 0;
}
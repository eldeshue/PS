
#include <iostream>
#include <tuple>

using Point = std::pair<long long, long long>;
using Line = std::pair<Point, Point>;
#define X first
#define Y second

int cross(const Point &v1, const Point &v2)
{
	long long product = v1.X * v2.Y - v1.Y * v2.X;
	if (product > 0)
		return 1;
	else if (product < 0)
		return -1;
	else
		return 0;
}

// 1 : cross one point
// 0 : does not cross
// -1 : cross multiple points, overlapped
int isCross(Line &l1, Line &l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	int v1 =
		cross(vec1, std::make_pair(l2.first.X - l1.second.X, l2.first.Y - l1.second.Y)) * cross(vec1, std::make_pair(l2.second.X - l1.second.X, l2.second.Y - l1.second.Y));

	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	int v2 =
		cross(vec2, std::make_pair(l1.first.X - l2.second.X, l1.first.Y - l2.second.Y)) * cross(vec2, std::make_pair(l1.second.X - l2.second.X, l1.second.Y - l2.second.Y));

	//
	long long tmp = vec1.X;
	vec1.X *= vec2.X;
	vec1.Y *= vec2.X;
	vec2.X *= tmp;
	vec2.Y *= tmp;

	// overlap???
	if (v1 == 0 && v2 == 0)
	{
		if (l1.first > l1.second)
			std::swap(l1.first, l1.second);
		if (l2.first > l2.second)
			std::swap(l2.first, l2.second);

		if (l2.first < l1.second && l1.first < l2.second && vec1 == vec2)
			return -1;
		else if (l2.first <= l1.second && l1.first <= l2.second)
			return 1;
		else
			return 0;
	}
	// not overlap
	if ((v1 <= 0) && (v2 <= 0))
		return 1;
	else
		return 0;
}

// coordinate of cross point
std::pair<double, double> calCrossCoordinate(const Line &l1, const Line &l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	if (l1.first == l2.second) // parallel
	{
		return std::make_pair(static_cast<double>(l1.first.X), static_cast<double>(l1.first.Y));
	}
	else if (l1.second == l2.first)
	{
		return std::make_pair(static_cast<double>(l1.second.X), static_cast<double>(l1.second.Y));
	}
	else
	{
		double a1 = -vec1.Y;
		double b1 = vec1.X;
		double c1 = vec1.X * l1.first.Y - vec1.Y * l1.first.X;
		double a2 = -vec2.Y;
		double b2 = vec2.X;
		double c2 = vec2.X * l2.first.Y - vec2.Y * l2.first.X;
		double det = a1 * b2 - a2 * b1;
		double x = (b2 * c1 - b1 * c2) / det;
		double y = (-a2 * c1 + a1 * c2) / det;
		return std::make_pair(x, y);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Line l1, l2;
	std::cin >> l1.first.X >> l1.first.Y >> l1.second.X >> l1.second.Y;
	std::cin >> l2.first.X >> l2.first.Y >> l2.second.X >> l2.second.Y;
	int numOfIntersect = isCross(l1, l2);
	if (numOfIntersect != 0)
	{
		std::cout << "1\n";
		if (numOfIntersect > 0)
		{
			double x, y;
			std::tie(x, y) = calCrossCoordinate(l1, l2);
			std::cout << std::fixed; // 출력 범위 소수점 아래로 고정
			std::cout.precision(16); // 소수점 아래 16자 까지 출력, fix가 없으면 유효숫자 16개
			std::cout << x << ' ' << y << '\n';
		}
	}
	else
	{
		std::cout << "0\n";
	}
}

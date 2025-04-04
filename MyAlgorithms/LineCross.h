
#ifndef LINE_CROSS_H
#define LINE_CROSS_H

#include <tuple>

using Point = std::pair<long long, long long>;
using Line = std::pair<Point, Point>;
#define X first
#define Y second

int ccw(const Point& v1, const Point& v2)
{
	long long crossProduct = v1.X * v2.Y - v1.Y * v2.X;
	if (crossProduct > 0)	// counter clock wise
		return 1;
	else if (crossProduct < 0)	// clock wise
		return -1;
	else
		return 0;	// parallel
}

/*
	return value

	1 : cross one point
	0 : does not cross
	-1 : cross multiple points, overlapped
 */
int isCross(Line& l1, Line& l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	int v1 =
		ccw(vec1, std::make_pair(l2.first.X - l1.second.X, l2.first.Y - l1.second.Y))
		* ccw(vec1, std::make_pair(l2.second.X - l1.second.X, l2.second.Y - l1.second.Y));

	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	int v2 =
		ccw(vec2, std::make_pair(l1.first.X - l2.second.X, l1.first.Y - l2.second.Y))
		* ccw(vec2, std::make_pair(l1.second.X - l2.second.X, l1.second.Y - l2.second.Y));

	// multiply vector
	long long tmp = vec1.X;
	vec1.X *= vec2.X;
	vec1.Y *= vec2.X;
	vec2.X *= tmp;
	vec2.Y *= tmp;

	if (v1 == 0 && v2 == 0)	// parallel
	{
		if (l1.first > l1.second) std::swap(l1.first, l1.second);
		if (l2.first > l2.second) std::swap(l2.first, l2.second);

		if (l2.first < l1.second && l1.first < l2.second && vec1 == vec2)	// parallel and cross, at multiple point
			return -1;
		else if (l2.first <= l1.second && l1.first <= l2.second)	// parallel and cross, at one point
			return 1;
		else	// parallel but does not cross
			return 0;
	}

	if ((v1 <= 0) && (v2 <= 0))
		return 1;
	else
		return 0;
}

// coordinate of cross point
std::pair<double, double> calCrossCoordinate(const Line& l1, const Line& l2)
{
	Point vec1 = std::make_pair(l1.first.X - l1.second.X, l1.first.Y - l1.second.Y);
	Point vec2 = std::make_pair(l2.first.X - l2.second.X, l2.first.Y - l2.second.Y);
	if (l1.first == l2.second)	// parallel
	{
		return std::make_pair(static_cast<long double>(l1.first.X), static_cast<long double>(l1.first.Y));
	}
	else if (l1.second == l2.first)
	{
		return std::make_pair(static_cast<long double>(l1.second.X), static_cast<long double>(l1.second.Y));
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

#endif

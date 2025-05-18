#include <iostream>
#include <tuple>
#include <vector>

using ll = long long;
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

int is_same_side(
	const Point& l1,
	const Point& l2,
	const Point& p1,
	const Point& p2)
{
	const Point line = std::make_pair(l1.X - l2.X, l1.Y - l2.Y);
	const Point s1 = std::make_pair(p1.X - l1.X, p1.Y - l1.Y);
	const Point s2 = std::make_pair(p2.X - l1.X, p2.Y - l1.Y);
	return (ccw(line, s1) * ccw(line, s2));
}

int in_triangle(
	const Point& p1,
	const Point& p2,
	const Point& t)
{
	const Point l1 = std::make_pair(p1.X - pivot.X, p1.Y - pivot.Y);
	const Point l2 = std::make_pair(p2.X - pivot.X, p2.Y - pivot.Y);
	int val = ccw(l1, l2);
	int first = is_same_side(pivot, p1, p2, t);
	int second = is_same_side(pivot, p2, p1, t);
	int third = is_same_side(p1, p2, pivot, t);
	bool between_angle = (first >= 0) && (second >= 0);

	if (between_angle)
	{
		if (val >= 0 && third >= 0)
		{
			// ccw, third include
			return 1;
		}
		else if (val < 0 && third > 0)
		{
			// cw, not include
			return -1;
		}
	}
	return 0;
}

/*
	모든 점이 1사분면에 있으므로, pivot(-1, -1)인 점을 하나 고정하고,
	이 점에서 다각형의 인접한 두 꼭짓 점,
	즉 다각형의 한 변을 이루는 두 점을 향해서 선분을 긋는다.

	주어진 점 target에 대한 내포 판정을 할 때,
	다각형을 이루는 점이 반시계 순으로 주어졌다면,
	1)
	만약 이 두 선분이 pivot을 기준으로 CCW이고
	해당 삼각형 위에 target이 존재한다면 cnt에 +1
	2)
	만약 이 두 선분이 pivot을 기준으로 CW이고
	해당 삼각형 위에 target이 존재한다면 cnt에 -1

	다각형의 모든 변에 대해서 위 작업을 수행한 후,
	cnt가 0이 아니면 다각형 내부에 target이 존재함이다.

	만약 cnt가 0이면 주어진 점들이 반시계가 아닌 탓일 수 있음.
	따라서 주어진 점들을 반대방향으로 읽으면서 위 알고리즘을 다시 수행함.
*/
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<Point> points(N);
	for (auto& [x, y] : points)
	{
		std::cin >> x >> y;
	}
	points.push_back(points[0]);

	// handle 3 query
	for (int i = 0; i < 3; ++i)
	{
		Point target;
		std::cin >> target.X >> target.Y;

		int cnt = 0;
		for (int i = 0; i < N; ++i)
		{
			cnt += in_triangle(points[i], points[i + 1], target);
		}

		// if the points are ordered in CW,
		// do it again in reverse order
		if (cnt == 0)
		{
			// for target vertex on the edge,
			// do it again, but reverse order
			// if the vertices are given in specific order,
			// dont' have to do it again.
			for (int i = N; i >= 1; --i)
			{
				cnt += in_triangle(points[i], points[i - 1], target);
			}
		}
		std::cout << (cnt != 0) << '\n';
	}
}

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <deque>

using ll = long long;
struct Point
{
	ll x, y;
	bool operator<(const Point &rhs)
	{
		if (y == rhs.y)
			return x < rhs.x;
		return y < rhs.y;
	}
};

ll dist(const Point &p1, const Point &p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

ll ccw(const Point &pivot, const Point &p1, const Point &p2)
{
	const ll dx1 = p1.x - pivot.x;
	const ll dy1 = p1.y - pivot.y;
	const ll dx2 = p2.x - pivot.x;
	const ll dy2 = p2.y - pivot.y;
	return (dx1 * dy2) - (dy1 * dx2);
}

// erase Points on the convex hull
std::vector<Point> grahamScan(std::vector<Point> coordinates)
{
	const int N = coordinates.size();
	std::deque<Point> st;
	std::vector<Point> result;

	// y축 기준 정렬
	std::sort(coordinates.begin(), coordinates.end());
	// 반시계방향 정렬
	auto ccwFixedPivot = std::bind(ccw, coordinates[0], std::placeholders::_1, std::placeholders::_2);
	auto distFromPivot = std::bind(dist, coordinates[0], std::placeholders::_1);
	auto ccwCompare = [&ccwFixedPivot, &distFromPivot](const auto &p1, const auto &p2)
	{
		const ll ccwResult = ccwFixedPivot(p1, p2);
		if (ccwResult != 0)
			return ccwResult > 0;
		return distFromPivot(p1) < distFromPivot(p2);
	};
	std::sort(coordinates.begin() + 1, coordinates.end(), ccwCompare);

	// sweeping
	st.insert(st.end(), coordinates.begin(), coordinates.begin() + 2);
	for (int i = 2; i < N; ++i)
	{
		const Point &curPoint = coordinates[i];
		while (st.size() >= 2)
		{
			const Point &prevPoint = st.back();
			const Point &pivot = st[st.size() - 2];
			if (ccw(pivot, prevPoint, curPoint) >= 0) // 한 직선 위에 여러 점이 가능한 convec-hull이면 등호 제외
				break;
			result.push_back(st.back());
			st.pop_back();
		}
		// push
		st.push_back(curPoint);
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input;
	int N, result = 0;
	ll px, py;
	std::cin >> N >> px >> py;
	std::vector<Point> coordinates(N + 1);
	for (int i = 0; i < N; ++i)
		std::cin >> coordinates[i].x >> coordinates[i].y;
	coordinates.back().x = px;
	coordinates.back().y = py;

	while (coordinates.size() > 3)
	{
		coordinates = grahamScan(coordinates);
		if (std::any_of(coordinates.begin(), coordinates.end(),
						[&](const Point &p)
						{ return (p.x == px) && (p.y == py); }))
			result++;
	}
	std::cout << result;
}

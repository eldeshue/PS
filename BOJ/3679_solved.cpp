
/*
	convex hull

	컨벡스 헐을 구하는 그라함 스캔 알고리즘 중
	주어진 점들을 반시계방향으로 정렬하는 부분에 대한 이해를 묻는 문제

	앞서 풀었던 4181번과 동일함.
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <deque>

using ll = long long;
struct Point
{
	ll x, y, i;
	bool operator<(const Point& rhs)
	{
		if (x == rhs.x)
			return y < rhs.y;
		return x < rhs.x;
	}
};

ll dist(const Point& p1, const Point& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

ll ccw(const Point& pivot, const Point& p1, const Point& p2)
{
	const ll dx1 = p1.x - pivot.x;
	const ll dy1 = p1.y - pivot.y;
	const ll dx2 = p2.x - pivot.x;
	const ll dy2 = p2.y - pivot.y;
	return (dx1 * dy2) - (dy1 * dx2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		// input;
		int N;
		std::cin >> N;
		std::vector<Point> coordinates(N);
		for (int i = 0; i < N; ++i)
		{
			std::cin >> coordinates[i].x >> coordinates[i].y;
			coordinates[i].i = i;
		}

		// x축 기준 정렬
		std::sort(coordinates.begin(), coordinates.end());
		// 반시계방향 정렬
		auto ccwFixedPivot = std::bind(ccw, coordinates[0], std::placeholders::_1, std::placeholders::_2);
		auto distFromPivot = std::bind(dist, coordinates[0], std::placeholders::_1);
		auto ccwCompare = [&ccwFixedPivot, &distFromPivot](const auto& p1, const auto& p2)
			{
				const ll ccwResult = ccwFixedPivot(p1, p2);
				if (ccwResult != 0)
					return ccwResult > 0;
				return distFromPivot(p1) < distFromPivot(p2);
			};
		std::sort(coordinates.begin() + 1, coordinates.end(), ccwCompare);

		// find turning point
		int pIdx = coordinates.size() - 2;
		for (; pIdx >= 0; --pIdx)
		{
			if (ccw(coordinates[0], coordinates.back(), coordinates[pIdx]) != 0)
				break;
		}

		// print result
		for (int i = 0; i <= pIdx; ++i)
			std::cout << coordinates[i].i << ' ';
		// reverse
		for (int i = coordinates.size() - 1; i > pIdx; --i)
			std::cout << coordinates[i].i << ' ';
		std::cout << '\n';
	}
}
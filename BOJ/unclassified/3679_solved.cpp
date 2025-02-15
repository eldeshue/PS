
/*
	convex hull

	������ ���� ���ϴ� �׶��� ��ĵ �˰��� ��
	�־��� ������ �ݽð�������� �����ϴ� �κп� ���� ���ظ� ���� ����

	�ռ� Ǯ���� 4181���� ������.
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

		// x�� ���� ����
		std::sort(coordinates.begin(), coordinates.end());
		// �ݽð���� ����
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
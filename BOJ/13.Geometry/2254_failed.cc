
/*

	boj 2254, 감옥 건설

	convec-hull의 응용문제.
	ordered set을 이용해서 convex-hull의 일부라고 판단되면 제거하기

	단 감옥을 중심으로 점들을 정렬해줘야 적용이 가능함

	구한 convex-hull의 내부에 pivot이 존재하는지를 알아야 함.

*/
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <set>

using point = std::pair<int, int>;
using ll = long long;

ll sqr_dist(const point &p1, const point &p2)
{
	return static_cast<ll>((p1.first - p2.first) * (p1.first - p2.first)) //
		   + static_cast<ll>((p1.second - p2.second) * (p1.second - p2.second));
}

ll ccw(const point &pcenter, const point &pleft, const point &pright)
{
	ll dxl = pleft.first - pcenter.first;
	ll dyl = pleft.second - pcenter.second;
	ll dxr = pright.first - pcenter.first;
	ll dyr = pright.second - pcenter.second;
	return (dxl * dyr) - (dyl * dxr);
}

point pivot;
struct comparator_ccw
{
	bool operator()(const point &p1, const point &p2)
	{
		ll dir = ccw(pivot, p1, p2);
		if (dir == 0)
			return sqr_dist(pivot, p1) < sqr_dist(pivot, p2);
		return (dir > 0);
	}
};

bool graham_scan(std::set<point, comparator_ccw> &points)
{
	std::deque<point> convex_hull;
	// set은 정렬되어있는데, 정렬의 방식 상, 트리의 가장 오른쪽 끝 원소는 무조건 convex-hull의 일부임
	point cur_point;
	if (points.size() <= 3)
		return false;
	for (const point &next_point : points)
	{
		while (convex_hull.size() > 1)
		{
			cur_point = convex_hull.back();
			convex_hull.pop_back();
			const point &prev_point = convex_hull.back();
			if (ccw(prev_point, cur_point, next_point) > 0)
			{
				convex_hull.push_back(cur_point);
				break;
			}
		}
		convex_hull.push_back(next_point);
	}
	// 예외 제거
	int size = convex_hull.size();
	while (size-- > 0)
	{
		cur_point = convex_hull.front();
		convex_hull.pop_front();
		if (ccw(convex_hull.back(), cur_point, convex_hull.front()) > 0)
		{
			convex_hull.push_back(cur_point);
		}
	}

	// delete convex-hull
	while (!convex_hull.empty())
	{
		points.erase(convex_hull.back());
		convex_hull.pop_back();
	}
	// is pivot in the set
	return (true);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::set<point, comparator_ccw> point_set;
	int N, x, y, result = 0;
	std::cin >> N >> x >> y;
	pivot = std::make_pair(x, y);
	point_set.insert(pivot);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> x >> y;
		point_set.insert(std::make_pair(x, y));
	}
	while (graham_scan(point_set))
	{
		result++;
	}
	std::cout << result;
}


/*
	BOJ 2261

	평면 위 점들 사이에서 최소 거리의 쌍을 찾는 문제.
	단순히 완전 탐색으로 풀기에는 점의 개수가 많음.

	모 회사 코테 1번 문제였는데, 지나가면서 보기만 하고, 풀질 않았음.
	당시 내 실력으로는 절대 못풀었을 것.

	그러나, 이 문제는 너무나도 well-known한 문제였으니,
	몰랐다는 것은 공부가 부족하다는 것이고,
	회사는 그딴 사람 원하지 않음.

	========================================================

	해당 문제의 풀이에는 두 가지 방법이 존재함. 하나는 분할 정복이고, 다른 하나는 sweeping임.

	두 풀이 모두 기하학적인 지식을 선험적으로 알고 있어야 떠올릴 수 있는 풀이임.

	요점은 이분 탐색의 대상이 되는 점들을 이진트리, set에 저장함.
	이 set에 들어있는 점들 중, x좌표 거리가 현재 최단 거리인 d보다 멀면 제거함.

	이 최적화를 통해서, 현재 점을 중심으로 y좌표 +-d 범위로 이분탐색을 걸면, 그 범위 안에 최단 거리 쌍 후보가 등장
	-> 이 후보들이 불과 6개 이하임이 수학적으로 증명되었음(WOW)
	근데, 이 기하학적 지식을 모르면 이분탐색 걸어서 얻은 범위가 N인지 어떻게 알지?
*/

// sweeping solution
// from : https://www.acmicpc.net/blog/view/25
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>

using P = std::pair<int, int>;

int const constexpr INT_MAX = std::numeric_limits<int>().max();
int const constexpr INT_MIN = std::numeric_limits<int>().lowest();

struct cmp_y_first
{
	bool operator()(P const& p1, P const& p2) const
	{
		if (p1.second == p2.second)
			return p1.first < p2.first;
		return p1.second < p2.second;
	}
};

int x_sq_dist(int const x1, int const x2)
{
	int dx = x1 - x2;
	return dx * dx;
}

int sq_dist(P const& p1, P const& p2)
{
	int dx = p1.first - p2.first;
	int dy = p1.second - p2.second;
	return dx * dx + dy * dy;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<P> points(N);
	for (auto& p : points)
		std::cin >> p.first >> p.second;

	// sort
	std::sort(points.begin(), points.end());

	// sweeping
	std::set<P, cmp_y_first> cndt;
	cndt.insert({ points[0], points[1] });
	int min_sq_dist = sq_dist(points[0], points[1]);
	P m_i = points[0], m_j = points[1];
	int erase_start = 0;
	for (int i = 2; i < N; ++i)	// loop of N, O(N)
	{
		auto const cur_p = points[i];

		// erase unseless candidate
		while (erase_start < i)	// from erase_start, total O(N), does not propagate
		{
			if (min_sq_dist < x_sq_dist(points[erase_start].first, cur_p.first))
			{
				cndt.erase(points[erase_start]);
				++erase_start;
			}
			else
			{
				break;
			}
		}

		int d = static_cast<int>(std::sqrt(static_cast<double>(min_sq_dist))) + 1;	// by add 1, range will be solid

		// find with range, binary search, O(log N)
		auto lp = P{ INT_MIN, cur_p.second - d };
		auto rp = P{ INT_MAX, cur_p.second + d };
		auto litr = cndt.lower_bound(lp);
		auto ritr = cndt.upper_bound(rp);

		// traverse range, update result
		// size of the range is proved to be less than 6~7, so O(1); -> WOW!!!!!
		// this only works with erasing candidate
		// erasing candidate is key condition
		for (auto itr = litr; itr != ritr; ++itr)
		{
			int temp = sq_dist(*itr, cur_p);
			if (temp < min_sq_dist)
			{
				min_sq_dist = temp;
				m_i = *itr;
				m_j = cur_p;
			}
		}

		// insert current point to the set, O(log N)
		cndt.insert(cur_p);
	}

	// print result
	// dist or points
	std::cout << min_sq_dist;
}

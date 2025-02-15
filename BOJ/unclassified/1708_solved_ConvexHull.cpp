
/*

	boj 1708, Convex Hull

	2차원 평면상에 존재하는 점들에서
	다른 모든 점을 포함하는, 볼록한 껍질을 이루는 부분집합을 찾는 알고리즘.

	문자 그대로 볼록 껍질, 볼록하다는 것은 껍질을 구성하는 선분들 전부가
	이웃하는 선분과 반시계ccw 관계에 있음을 이용함.

	알고리즘 자체의 정식 이름은 Graham Scan, sweeping으로 구현됨.

*/

/*

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using point = std::pair<int, int>;
using ll = long long;
point pivot;

// 오른손 기준으로 외적
ll ccw(const point& p1, const point& p2, const point& p3)
{
	ll dx2 = p2.first - p1.first;
	ll dy2 = p2.second - p1.second;
	ll dx3 = p3.first - p1.first;
	ll dy3 = p3.second - p1.second;
	return (dx2 * dy3) - (dy2 * dx3);
}

// pivot을 찾기 위한 단순한 정렬임
bool cmp_left_low(const point& p1, const point& p2)
{
	if (p1.second != p2.second) return p1.second < p2.second;	// y first
	return p1.first < p2.first;									// y second
}

// 반시계방향 정렬
// pivot을 기준으로 반시계방향 정렬
// 사실상 convex hull의 핵심이 되는 부분.
// 정렬 결과, 점들을 pivot을 기준으로 대략 반시계 방향으로, 같은 방향이라면 pivot에 가까운 순으로
bool cmp_sweep(const point& p1, const point& p2)
{
	ll dx1 = p1.first - pivot.first;
	ll dx2 = p2.first - pivot.first;
	ll dy1 = p1.second - pivot.second;
	ll dy2 = p2.second - pivot.second;
	if (dy1 * dx2 != dx1 * dy2) return dy1 * dx2 < dx1 * dy2;	// slope
	if (p1.second != p2.second) return p1.second < p2.second;	// y first, ascending
	return p1.first < p2.first;									// y second, ascending
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::stack<int> idx_stack;
	std::vector<point> point_vec;
	int N, min_idx = -1, min_y = 2147483647;
	std::cin >> N;
	point_vec.resize(N);
	for (int i = 0; i < N; ++i)
		std::cin >> point_vec[i].first >> point_vec[i].second;
	// to find pivot, sort
	std::sort(point_vec.begin(), point_vec.end(), cmp_left_low);
	pivot = point_vec[0];
	// to sweep, sort again
	std::sort(point_vec.begin() + 1, point_vec.end(), cmp_sweep);
	// sweep, Graham-Scan
	// 스택의 최상단 두 점과 하나의 점, 총 3개의 점을 가지고 hull의 일부인지 판단함.
	// 판단 대상은 스택 최상단에 있는 점임.
	// 세 점으로 ccw를 수행한 후, convex hull의 일부가 아니라면 두 번째 점을 폐기함
	idx_stack.push(0);		// 정렬의 결과, pivot은 무조건 hull의 일부임.
	idx_stack.push(1);		// 일단 하나 넣어봄
	int cur_idx, prev_idx;
	for (int i = 0; i < N; ++i)
	{
		std::cout << point_vec[i].first << ' ' << point_vec[i].second << '\n';
	}
	for (int i = 2; i < N; ++i)
	{
		while (idx_stack.size() >= 2)
		{
			cur_idx = idx_stack.top();
			point& cur_point = point_vec[cur_idx];
			idx_stack.pop();
			prev_idx = idx_stack.top();
			point& prev_point = point_vec[prev_idx];
			if (ccw(prev_point, cur_point, point_vec[i]) > 0)
			{
				idx_stack.push(cur_idx);
				break;
			}
		}
		idx_stack.push(i);
	}
	// 정렬의 결과, 마지막 점은 무조건 hull의 일부임, 따라서 체크할 필요가 없음.
	// 대단히 고급스러운 코드....
	std::cout << idx_stack.size() << '\n';
//	/*
	std::cout << "-------------------\n";
	while (!idx_stack.empty())
	{
		std::cout << point_vec[idx_stack.top()].first << ' ' 
			<< point_vec[idx_stack.top()].second << '\n';
		idx_stack.pop();
	}
}

*/
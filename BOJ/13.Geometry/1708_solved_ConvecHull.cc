
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using point = std::pair<int, int>;
using ll = long long;
point pivot;

ll ccw(const point &p1, const point &p2, const point &p3)
{
	ll dx2 = p2.first - p1.first;
	ll dy2 = p2.second - p1.second;
	ll dx3 = p3.first - p1.first;
	ll dy3 = p3.second - p1.second;
	return (dx2 * dy3) - (dy2 * dx3);
}

// get first point as lowest and leftest
bool cmp_left_low(const point &p1, const point &p2)
{
	if (p1.first == p2.first)
		return p1.second < p2.second;
	return p1.first < p2.first;
}

bool cmp_sweep(const point &p1, const point &p2)
{
	ll dx1 = p1.first - pivot.first;
	ll dy1 = p1.second - pivot.second;
	ll dx2 = p2.first - pivot.first;
	ll dy2 = p2.second - pivot.second;
	if (p1.first == p2.first)
		return p1.second < p2.second;
	return p1.first < p2.first;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::stack<int> idx_stack;	  // stack for convec-hull
	std::vector<point> point_vec; // vector to store whole points
	int N, min_idx = -1, min_y = 2147483647;

	// input
	std::cin >> N;
	point_vec.resize(N);
	for (int i = 0; i < N; ++i)
		std::cin >> point_vec[i].first >> point_vec[i].second;

	// sort to find the lowest left
	std::sort(point_vec.begin(), point_vec.end(), cmp_left_low);
	pivot = point_vec[0];
	// to sweep the space, sort again
	std::sort(point_vec.begin() + 1, point_vec.end(), cmp_sweep);

	// sweep, graham-scan
	// init stack,
	int cur_idx, prev_idx;
	idx_stack.push(0);
	idx_stack.push(1);
	// sweep
	for (int i = 2; i < N; ++i)
	{
		while (idx_stack.size() >= 2)
		{
			cur_idx = idx_stack.top();
			point &cur_point = point_vec[cur_idx];
			idx_stack.pop(); // 일단 pop
			prev_idx = idx_stack.top();
			point &prev_point = point_vec[prev_idx];
			if (ccw(prev_point, cur_point, point_vec[i]) > 0) // 만약 스택의 top에 해당하는 점이 볼록하지 않다면 pop
			{
				// 앞서 pop했는데 점이 convec-hull의 일부이므로 다시 집어넣음.
				idx_stack.push(cur_idx);
				break;
			}
		}
		idx_stack.push(i);
	}
	std::cout << idx_stack.size();
}


/*

	boj 1708, Convex Hull

	2���� ���� �����ϴ� ���鿡��
	�ٸ� ��� ���� �����ϴ�, ������ ������ �̷�� �κ������� ã�� �˰���.

	���� �״�� ���� ����, �����ϴٴ� ���� ������ �����ϴ� ���е� ���ΰ�
	�̿��ϴ� ���а� �ݽð�ccw ���迡 ������ �̿���.

	�˰��� ��ü�� ���� �̸��� Graham Scan, sweeping���� ������.

*/

/*

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using point = std::pair<int, int>;
using ll = long long;
point pivot;

// ������ �������� ����
ll ccw(const point& p1, const point& p2, const point& p3)
{
	ll dx2 = p2.first - p1.first;
	ll dy2 = p2.second - p1.second;
	ll dx3 = p3.first - p1.first;
	ll dy3 = p3.second - p1.second;
	return (dx2 * dy3) - (dy2 * dx3);
}

// pivot�� ã�� ���� �ܼ��� ������
bool cmp_left_low(const point& p1, const point& p2)
{
	if (p1.second != p2.second) return p1.second < p2.second;	// y first
	return p1.first < p2.first;									// y second
}

// �ݽð���� ����
// pivot�� �������� �ݽð���� ����
// ��ǻ� convex hull�� �ٽ��� �Ǵ� �κ�.
// ���� ���, ������ pivot�� �������� �뷫 �ݽð� ��������, ���� �����̶�� pivot�� ����� ������
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
	// ������ �ֻ�� �� ���� �ϳ��� ��, �� 3���� ���� ������ hull�� �Ϻ����� �Ǵ���.
	// �Ǵ� ����� ���� �ֻ�ܿ� �ִ� ����.
	// �� ������ ccw�� ������ ��, convex hull�� �Ϻΰ� �ƴ϶�� �� ��° ���� �����
	idx_stack.push(0);		// ������ ���, pivot�� ������ hull�� �Ϻ���.
	idx_stack.push(1);		// �ϴ� �ϳ� �־
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
	// ������ ���, ������ ���� ������ hull�� �Ϻ���, ���� üũ�� �ʿ䰡 ����.
	// ����� ��޽����� �ڵ�....
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
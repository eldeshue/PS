/*
	BOJ 5620

	2261번과 정확히 동일한 문제이지만,
	2261은 sweeping이고, 여기서는 divide & conquer로 풀었습니다.

	모 회사 코테 1번이었는데, well-known이라 나만 못풀은게 아닌지....
	속이 아주 쓰립니다...
*/
#include <iostream>
#include <vector>
#include <algorithm>

using P = std::pair<int, int>;

int get_x_dist(P const& p1, P const& p2)
{
	int const dx = p1.first - p2.first;
	return dx * dx;
}
int get_y_dist(P const& p1, P const& p2)
{
	int const dy = p1.second - p2.second;
	return dy * dy;
}
int get_dist(P const& p1, P const& p2)
{
	return get_x_dist(p1, p2) + get_y_dist(p1, p2);
}

int div_conquer(std::vector<P> const& vec, int start, int end)
{
	// base case
	int const size = end - start;
	if (size == 1)
	{
		return 2e9;
	}
	else if (size == 2)
	{
		return get_dist(vec[start], vec[start + 1]);
	}

	// not base case
	int const mid = (start + end) >> 1;

	// divide
	int min_dist = std::min(div_conquer(vec, start, mid), div_conquer(vec, mid, end));

	// conquer
	std::vector<P> cndt;
	for (int i = mid - 1; i >= start; --i)
	{
		if (min_dist <= get_x_dist(vec[mid], vec[i]))
			break;
		cndt.push_back(vec[i]);
	}
	for (int i = mid; i < end; ++i)
	{
		if (min_dist <= get_x_dist(vec[mid], vec[i]))
			break;
		cndt.push_back(vec[i]);
	}
	// sort, y first
	std::sort(cndt.begin(), cndt.end(),
		[](P const& p1, P const& p2) {
			if (p1.second == p2.second)
				return p1.first < p2.first;
			return p1.second < p2.second; });

	// looks like O(N^2), but it's actually O(N)
	for (int i = 0; i < cndt.size() - 1; ++i)
	{
		// because, size of inner-loop is always less than 6....
		// why???
		for (int j = i + 1; j < cndt.size(); ++j)
		{
			if (min_dist < get_y_dist(cndt[i], cndt[j]))
				break;
			min_dist = std::min(min_dist, get_dist(cndt[i], cndt[j]));
		}
	}

	return min_dist;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<P> points(N);
	for (auto& [x, y] : points)
		std::cin >> x >> y;

	std::sort(points.begin(), points.end());

	std::cout << div_conquer(points, 0, N);
}

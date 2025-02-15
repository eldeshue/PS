
#include <iostream>
#include <algorithm>
#include <vector>

using point = std::pair<int, int>; 
std::vector<point> point_vec;

// get y
bool sort_xy(const point& p1, const point& p2)
{
	if (p1.first == p2.first)
		return p1.second < p2.second;
	return p1.first < p2.first;
}

// get x
bool sort_yx(const point& p1, const point& p2)
{
	if (p1.second == p2.second)
		return p1.first < p2.first;
	return p1.second < p2.second;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, x, y;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> x >> y;
		point_vec.push_back(std::make_pair(x, y));
	}
	int total_len = 0;
	// 직교 다각형은 항상 쌍으로 이루어짐.
	// xy 순으로 정렬하면, 동일한 x값을 갖는 점들의 쌍이 구성됨.
	// 따라서 짝수번째 점과 홀수 번째 점의 y값의 차를 더해주면 됨.
	std::sort(point_vec.begin(), point_vec.end(), sort_xy);
	for (int i = 0; i < N / 2; ++i)
	{
			total_len += point_vec[2 * i + 1].second - point_vec[2 * i].second;
	}
	// 마찬가지 원리를 돌려서 생각함.
	// yx 순으로 정렬하면, 동일한 y값을 갖는 점들의 쌍이 구성됨.
	// 따라서 짝수번째 점과 홀수 번째 점의 x값의 차를 더해주면 됨.
	std::sort(point_vec.begin(), point_vec.end(), sort_yx);
	for (int i = 0; i < N / 2; ++i)
	{
			total_len += point_vec[2 * i + 1].first - point_vec[2 * i].first;
	}
	std::cout << total_len;
}
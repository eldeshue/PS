
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>

using tree = std::tuple<int, int, int>; // x, y, value
std::vector<tree> trees;				// tree 정보들
std::vector<int> index_buffer;			// trees의 인덱스들, 트리 대신 정렬됨

int pivot_x, pivot_y; // pivot 점의 좌표
int div_x, div_y;	  // 공간을 이분하는 div line의 방향벡터

int dot(const int &idx) // 공간을 이분하는 div 라인 위에서의 위치 정도
{
	const int x = std::get<0>(trees[idx]) - pivot_x;
	const int y = std::get<1>(trees[idx]) - pivot_y;

	return (div_x * x + div_y * y);
}

int cross(const int &idx) // 공간을 이분하는 div 라인의 위치 정도
{
	const int x = std::get<0>(trees[idx]) - pivot_x;
	const int y = std::get<1>(trees[idx]) - pivot_y;

	return (x * div_y - y * div_x);
}

bool cmp_index_cw(const int &idx1, const int &idx2)
{
	int priority1 = cross(idx1);
	int priority2 = cross(idx2);
	if (priority1 == priority2)
	{
		priority1 = dot(idx1);
		priority2 = dot(idx2);
		return (priority1 < priority2); // 내적 결과 오름차순
	}
	return (priority1 < priority2); // 외적 결과 오름차순
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, total_value = 0, min_gap = 6e7;
	// 입력
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int x, y, val;
		std::cin >> x >> y >> val;
		total_value += val;
		trees.push_back(std::make_tuple(x, y, val));
		index_buffer.push_back(i);
	}
	// 두 나무를 선택, 두 나무를 잇는 직선의 기울기를 공간을 이분하는 div line의 기울기로 삼는다
	for (int pivot_idx = 0; pivot_idx < N - 1; ++pivot_idx)
	{
		// pivot point, 두 점 중 기준
		pivot_x = std::get<0>(trees[pivot_idx]);
		pivot_y = std::get<1>(trees[pivot_idx]);
		for (int target_idx = pivot_idx + 1; target_idx < N; ++target_idx)
		{
			// div line의 기울기 획득
			div_x = std::get<0>(trees[target_idx]) - pivot_x;
			div_y = std::get<1>(trees[target_idx]) - pivot_y;

			// sorting idx_buffer with divding line
			std::sort(index_buffer.begin(), index_buffer.end(), cmp_index_cw);
			int sum = 0, cur_min_gap = total_value;
			for (int idx_idx = 0; idx_idx < N; ++idx_idx)
			{
				sum += std::get<2>(trees[index_buffer[idx_idx]]);
				int cur_gap = std::abs(total_value - sum * 2);
				if (cur_min_gap < cur_gap)
				{
					break;
				}
				cur_min_gap = cur_gap;
			}
			// get minimum gap value
			min_gap = std::min(min_gap, cur_min_gap);
		}
	}
	std::cout << min_gap;
}

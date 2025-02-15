
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <functional>

using tree = std::tuple<int, int, int>;
std::vector<tree> trees;	   // resources
std::vector<int> index_buffer; // will be sorted instead of trees
std::function<bool(const int &, const int &)> sort_method[2];

// equation of line
// dy/dx = (target_y - pivot_y) / (target_x - pivot_x)
// y = dy/dx * x + (...);
// dx * y - dy * x = (....) ;
int s_x, s_y, d_x, d_y;

int pos_on_sweep(const int &idx)
{
	const int &x = std::get<0>(trees[idx]);
	const int &y = std::get<1>(trees[idx]);

	return (d_x * y - d_y * x);
}

int dist_from_sweep(const int &idx) // cross product
{
	const int x = std::get<0>(trees[idx]) - s_x;
	const int y = std::get<1>(trees[idx]) - s_y;

	return (x * d_y - y * d_x);
}

bool cmp_index_ccw(const int &idx1, const int &idx2)
{
	int priority1 = pos_on_sweep(idx1);
	int priority2 = pos_on_sweep(idx2);
	if (priority1 == priority2)
	{
		priority1 = dist_from_sweep(idx1);
		priority2 = dist_from_sweep(idx2);
		return (priority1 > priority2);
	}
	return (priority1 < priority2);
}

bool cmp_index_cw(const int &idx1, const int &idx2)
{
	int priority1 = pos_on_sweep(idx1);
	int priority2 = pos_on_sweep(idx2);
	if (priority1 == priority2)
	{
		priority1 = dist_from_sweep(idx1);
		priority2 = dist_from_sweep(idx2);
		return (priority1 < priority2);
	}
	return (priority1 < priority2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	sort_method[0] = cmp_index_ccw;
	sort_method[1] = cmp_index_cw;

	int N, total_value = 0, min_gap = 6e7;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int x, y, val;
		std::cin >> x >> y >> val;
		total_value += val;
		trees.push_back(std::make_tuple(x, y, val));
		index_buffer.push_back(i);
	}
	for (int pivot_idx = 0; pivot_idx < N - 1; ++pivot_idx)
	{
		s_x = std::get<0>(trees[pivot_idx]);
		s_y = std::get<1>(trees[pivot_idx]);
		for (int target_idx = pivot_idx + 1; target_idx < N; ++target_idx)
		{
			// set delta value to define slope
			d_x = std::get<0>(trees[target_idx]) - s_x;
			d_y = std::get<1>(trees[target_idx]) - s_y;
			for (int sort_idx = 0; sort_idx < 2; ++sort_idx)
			{
				// sorting idx_buffer with sweeping line
				std::sort(index_buffer.begin(), index_buffer.end(), sort_method[sort_idx]);
				// sweeping
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
	}
	std::cout << min_gap;
}

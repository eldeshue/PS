/*
	BOJ
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (auto& n : nums)
		std::cin >> n;

	std::sort(nums.begin(), nums.end());

	int min_miss_cnt = 5;
	for (int i = 0; i < N; ++i)
	{
		// check consecutive 5
		int miss_cnt = 0;
		int collect_cnt = 1;
		for (int j = 0; j < 5; ++j)
		{
			int cur_pos = i + j;
			int nex_pos = i + j + 1;
			if (nex_pos == N)
			{
				miss_cnt += 5 - collect_cnt;
				break;
			}
			else
			{
				collect_cnt += nums[nex_pos] - nums[cur_pos];
				miss_cnt += nums[nex_pos] - nums[cur_pos] - 1;
			}
			if (collect_cnt >= 5)
			{
				break;
			}
		}
		min_miss_cnt = std::min(min_miss_cnt, miss_cnt);
	}
	std::cout << min_miss_cnt;
}

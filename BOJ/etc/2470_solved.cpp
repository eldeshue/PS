
#include <algorithm>
#include <iostream>
#include <vector>

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

	int minSum = 2e9, minL = 0, minR = N - 1;
	int lpos = 0, rpos = N - 1;
	while (lpos < rpos)
	{
		int const sum = nums[lpos] + nums[rpos];

		if (std::abs(sum) < minSum)
		{
			minL = lpos;
			minR = rpos;
			minSum = std::abs(sum);
		}

		if (sum == 0)
			break;
		else if (sum < 0)
			++lpos;
		else
			--rpos;
	}
	std::cout << nums[minL] << ' ' << nums[minR];
}
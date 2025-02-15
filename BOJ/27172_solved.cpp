
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<bool> isPlayable(1000001, false);
	std::vector<int> scores(1000001, 0);
	/*
		something like erasing sieve
	*/
	auto cnt_with_stride = [&](const int n)
		{
			const int Max = 1000000 / n;
			for (int i = 2; i <= Max; ++i)
			{
				if (isPlayable[i * n])
				{
					scores[n]++;
					scores[i * n]--;
				}
			}
		};
	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
		isPlayable[nums[i]] = true;
	}
	for (const int n : nums)
	{
		cnt_with_stride(n);
	}
	for (const int n : nums)
	{
		std::cout << scores[n] << ' ';
	}
}
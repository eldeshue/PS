
#include <iostream>
#include <vector>
#include <array>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (int &num : nums)
		std::cin >> num;

	std::array<int, 10> freq;
	std::fill(freq.begin(), freq.end(), 0);
	int cnt = 0, left = -1, right = -1, result = 0;
	while (right < N - 1)
	{
		if (++freq[nums[++right]] == 1)
			++cnt;
		while (cnt > 2)
		{
			// move left, decrease
			if (--freq[nums[++left]] == 0)
				--cnt;
		}
		result = std::max(result, right - left);
	//	std::cout << left << ' ' << right << ' ' << result << '\n';
	}
	std::cout << result;
}
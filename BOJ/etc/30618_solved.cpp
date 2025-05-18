
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
	int l = 0, r = N - 1;
	int val = 1;
	while (true)
	{
		nums[l++] = val++;
		if (val > N) break;
		nums[r--] = val++;
		if (val > N) break;
	}
	std::for_each(nums.begin(), nums.end(), [](int n) {std::cout << n << ' '; });
}

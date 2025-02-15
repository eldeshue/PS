
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

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
	std::unordered_map<int, int> freqOfDivisors;	// 해시맵 대신 배열을 쓰면 더 빠름
	for_each(nums.begin(), nums.end(), [&](const int n) {
			for (int i = 1; i <= std::sqrt(n); ++i)
			{
				if ((n % i) == 0)
				{
					freqOfDivisors[i]++;
					if (i != (n / i))
						freqOfDivisors[n / i]++;
				}
			}
		});
	std::cout << std::accumulate(freqOfDivisors.begin(), freqOfDivisors.end(), 0ULL,
		[](const long long acc, const std::pair<int, int> &entry) {
			if (entry.second == 1)
				return acc;
			return std::max(acc,
			static_cast<long long>(entry.first) * static_cast<long long>(entry.second));
		});
}
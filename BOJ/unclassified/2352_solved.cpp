
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, result = 0;
	std::cin >> N;
	std::vector<int> nums(N);
	for (int i = 0; i < N; ++i)
		std::cin >> nums[i];
	std::vector<int> minValPerLen(N + 1, 2e9);
	minValPerLen[0] = -1;
	for (int i = 0; i < N; ++i)
	{
		const int len = std::lower_bound(minValPerLen.begin(), minValPerLen.end(), nums[i]) - minValPerLen.begin();
		minValPerLen[len] = std::min(minValPerLen[len], nums[i]);
		result = std::max(result, len);
	}
	std::cout << result;
}
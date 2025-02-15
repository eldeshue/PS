
#include <iostream>
#include <numeric>
#include <vector>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<int> nums(N);
	std::iota(nums.begin(), nums.end(), 1);
	std::vector<pii> queries(M);
	for (auto &q : queries)
		std::cin >> q.first >> q.second;

	// closed range, both included
	auto reverseRange = [&nums](int left, int right)
	{
		while (left < right)
			std::swap(nums[left++], nums[right--]);
	};

	for (const auto &q : queries)
		reverseRange(q.first - 1, q.second - 1);

	for (const int n : nums)
		std::cout << n << ' ';
}

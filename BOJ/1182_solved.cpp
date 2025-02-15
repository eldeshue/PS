
#include <iostream>
#include <vector>
#include <functional>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, S;
	std::cin >> N >> S;
	std::vector<int> nums(N);
	for (int i = 0; i < N; ++i)
		std::cin >> nums[i];
	int sum = 0, result = 0;
	std::function<void(int)> search = [&](int idx) -> void
		{
			if (idx == N && sum == S)
				result++;
			if (idx == N)
				return;
			search(idx + 1);
			sum += nums[idx];
			search(idx + 1);
			sum -= nums[idx];
		};
	search(0);
	if (S == 0)
		result--;
	std::cout << result;
}
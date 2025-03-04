
#include <functional>
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	ll sum = 0, result = 0;
	int N;
	std::cin >> N;
	std::vector<ll>  nums(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
		sum += nums[i];
	}

	for (ll const n : nums)
	{
		result += (n * (sum - n));
	}
	std::cout << result / 2;
}
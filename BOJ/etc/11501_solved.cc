
// simple greedy
#include <iostream>
#include <array>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	long long result;
	int num_test, N, local_max;
	std::array<int, 1000000> arr;
	std::cin >> num_test;
	for (int t = 0; t < num_test; ++t)
	{
		result = 0, local_max = 0;
		std::cin >> N;
		for (int i = 0; i < N; ++i)
		{
			std::cin >> arr[i];
		}
		for (int i = N - 1; i >= 0; --i)
		{
			if (arr[i] > local_max)
			{
				local_max = arr[i];
			}
			else if (arr[i] < local_max)
			{
				result += local_max - arr[i];
			}
		}
		std::cout << result << '\n';
	}
}

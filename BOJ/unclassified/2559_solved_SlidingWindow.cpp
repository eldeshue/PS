
#include <iostream>
#include <array>

std::array<int, 100000> arr;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, sum = 0, result = -2147483648;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> arr[i];
	}
	for (int i = 0; i < K; ++i)
	{
		sum += arr[i];
	}
	result = sum;
	for (int i = 1; i < N - K + 1; ++i)	// sliding window
	{
		sum -= arr[i - 1];
		sum += arr[i + K - 1];
		result = std::max(result, sum);
	}
	std::cout << result;
}
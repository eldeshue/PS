
#include <iostream>
#include <array>

int N, L, sum = 0;
std::array<int, 200000> arr;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> L;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> arr[i];
	}
	for (int cnt = 1, i = N - 1; cnt < N; ++cnt, --i)
	{
		sum += arr[i];
		int left = (arr[i - 1] - L) * cnt, right = (arr[i - 1] + L) * cnt;
		if (left < sum && sum < right)
		{
			continue;
		}
		else
		{
			std::cout << "unstable";
			return 0;
		}
	}
	std::cout << "stable";
	return 0;
}

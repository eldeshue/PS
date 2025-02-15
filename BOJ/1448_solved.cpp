
#include <iostream>
#include <algorithm>
#include <array>

std::array<int, 1000000> arr;

bool is_triangle(int a, int b, int c)
{
	if (a < b + c)
		return true;
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> arr[i];
	}
	std::stable_sort(arr.begin(), arr.begin() + N, std::greater<>());
	for (int i = 0; i < N - 2; ++i)
	{
		if (is_triangle(arr[i], arr[i + 1], arr[i + 2]))
		{
			std::cout << arr[i] + arr[i + 1] + arr[i + 2];
			return 0;
		}
	}
	std::cout << -1;
	return 0;
}
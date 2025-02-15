
#include <iostream>
#include <array>

std::array<int, 50> arr;
int N, a, b;

void get_ab()
{
	a = (arr[2] - arr[1]) / (arr[1] - arr[0]);
	b = arr[1] - a * arr[0];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> arr[i];
	}
	// N < 3
	// fail, A
	if (N < 3)
	{
		if (arr[0] == arr[1])
		{
			std::cout << arr[0];
			return 0;
		}
		std::cout << 'A';
		return 0;
	}
	// N >= 3
	// good or B
	if (arr[0] == arr[1])
	{
		for (int i = 1; i < N; ++i)
		{
			if (arr[i] != arr[i - 1])
			{
				std::cout << 'B';
				return 0;
			}
		}
		std::cout << arr[0];
		return 0;
	}
	get_ab();
	for (int i = 3; i < N; ++i)
	{
		if (arr[i] != a * arr[i - 1] + b)
		{
			std::cout << 'B';
			return 0;
		}
	}
	std::cout << a * arr[N - 1] + b;
}
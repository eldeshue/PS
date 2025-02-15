
#include <iostream>
#include <algorithm>
#include <array>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, L;
	std::array<int, 1001> arr;
	std::cin >> N >> L;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> arr[i];
	}
	// greedy
	std::sort(arr.begin(), arr.begin() + N);
	L--;
	int last_pos = 0, cnt = 0;
	for (int i = 0; i < N; ++i)
	{
		if (last_pos < arr[i])
		{
			cnt++;
			last_pos = arr[i] + L;
		}
	}
	std::cout << cnt;
}
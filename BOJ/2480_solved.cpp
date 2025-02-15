#include <iostream>
#include <algorithm>
#include <array>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::array<int, 3> arr;
	std::cin >> arr[0] >> arr[1] >> arr[2];
	std::sort(arr.begin(), arr.end());
	int result;
	if (arr[0] == arr[2])
		result = 10000 + arr[0] * 1000;
	else if (arr[0] == arr[1] || arr[1] == arr[2])
		result = 1000 + arr[1] * 100;
	else
		result = arr[2] * 100;
	std::cout << result;
}
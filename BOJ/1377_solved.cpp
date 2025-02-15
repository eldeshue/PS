
#include <iostream>
#include <algorithm>
#include <array>

using pii = std::pair<int, int>;	// first : number, second : index

int N;
std::array<pii, 500001> arr;

bool comp_pair(const pii& p1, const pii& p2)
{
	return (p1.first < p2.first);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> arr[i].first;
		arr[i].second = i;
	}
	std::sort(arr.begin() + 1, arr.begin() + N + 1, comp_pair);
	int result = -1;
	for (int i = 1; i <= N; ++i)
	{
		//std::cout << arr[i].first << ' ';
		if (result < arr[i].second - i)
			result = arr[i].second - i;
	}
	std::cout << result + 1;
}
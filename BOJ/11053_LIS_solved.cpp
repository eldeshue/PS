
#include <iostream>
#include <algorithm>
#include <vector>

int N;
std::vector<int> buffer;
std::vector<int> cache;			// cache[length] = final value of the LIS

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	buffer.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}

	// LIS using upper bound
	cache.push_back(buffer[0]); // 초기값
	for (int i = 1; i < N; ++i)
	{
		if (buffer[i] > *cache.rbegin()) // append
		{
			cache.push_back(buffer[i]); // 지금까지 찾은 LIS들 중, 가장 긴 것의 final값보다 크다.
										// 즉 새로운 LIS가 등장한 부분임.
		}
		else // 기존의 LIS보다 작음, 따라서 기존의 LIS중에서 final value를 갱신함.
		{
			// update
			// find position to update by using lower_bound
			// lower_bound함수로 2진탐색하여 LIS의 final value를 갱신한다.
			// lower_bound함수는 인자로 전달된 값 이상의 값이 처음으로 존재하는 위치의 index를 반환함
			*(std::lower_bound(cache.begin(), cache.end(), buffer[i])) = buffer[i];
		}
	}
	std::cout << cache.size(); // 가장 긴 LIS의 길이를 반환함.
}
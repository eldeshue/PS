
/*
조합 속에서 각 숫자들이 몇 번 최대값으로, 몇 번 최솟값으로 등장하는지 계산하여 답을 구함.

주어진 숫자들을 모두 정렬하면, 해당 숫자가 최대/최소로 등장하는 빈도를 구할 수 있음.

위치 i에 대하여... 0 ~ N - 1
최대 : 2 ^ i - 1
최소 : 2 ^ (N - 1 - i) - 1

	솔루션 자체는 상당히 상식적인 부분,
	하지만 modulo연산 시 발생하는 다양한 연산상의 문제를 해결해야 해서 상당히 까다로운 문제였음.
*/
#include <iostream>
#include <algorithm>
#include <vector>

using ull = unsigned long long;
constexpr ull MOD = 1000000007;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<ull> nums(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
	}
	std::sort(nums.begin(), nums.end());
	// dp
	std::vector<ull> cache(N);
	ull cnt = 1;
	for (int i = 0; i < N; ++i)
	{
		cache[i] = cnt - 1;
		cnt = (cnt << 1) % MOD;
	}
	//
	ull result = 0;
	for (int i = nums.size() - 1; i >= 0; --i)
	{
		result = (result + (cache[i] - cache[nums.size() - 1 - i]) * nums[i]) % MOD;
	}
	std::cout << result;
}

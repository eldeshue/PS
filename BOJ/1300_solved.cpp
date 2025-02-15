
/*
	발상의 전환이 돋보이는 되게 좋은 문제.

	먼저 B의 K번째 원소라 함은
	행렬에서 해당 원소보다 작은 원소의 개수가 K - 1개 있음을 의미함.
	요 부분을 빠르게 catch하면 이분탐색으로 이어서 생각할 수 있음.

	그러나..... 나는 굉장히 고민을 많이 했는데,
	행렬을 구성하는 값들의 분포로 해결하려 했기 때문

	행렬이라는 대상에 대하여, 그 숫자의 배치에 얽메이지 말고,
	행렬을 구성하는 값들, 그 자체에 집중할 필요가 있음.

	다만, 해당 문제의 경우 key idea가 이분 탐색임을 알고 풀어서 이정도지
	사실 이분탐색이라는 키워드를 몰랐다면 대단히 어려운 문제가 맞음.

	골드 1도 좀 과소평가된 기분이 든다.
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using ll = long long;

bool isLessGreaterThanK(const ll N, const ll K, const ll num)
{
	ll cnt = 0;
	// 행렬의 각 row에 대해서 num보다 작은 숫자의 개수를 collect
	// 한 row에서 num 보다 작은 숫자의 개수는 둘 중 하나임.
	// 해당 row의 모든 성분이 num보다 작은 경우, N개
	// ex ) N = 5, row = 2, num = 20인 경우 -> min(5, 10) = 5개 (2, 4, 6, 8, 10)
	// 그 외의 경우는 row의 값으로 num을 나눠준 몫의 수 만큼 num보다 작음
	// ex ) N = 11, row = 9, num = 20인 경우 -> 9, 18의 두 개
	for (ll i = 1; i <= N; ++i)	
	{
		cnt += std::min(N, num / i);
	}
	return cnt >= K;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N, K;
	std::cin >> N >> K;
	// lower bound
	auto isOk = std::bind(isLessGreaterThanK, N, K, std::placeholders::_1);
	ll left = 1, right = N * N + 1;	// B[K] 는 K보다 항상 작기에 K로 써도 됨.
	while (left < right)
	{
		ll mid = (left + right) >> 1;
		if (isOk(mid))
			right = mid;
		else
			left = mid + 1;
	}
	std::cout << left;
}
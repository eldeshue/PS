/*
	습격자 초라기

	원형 메모리 dp, 주어진 공간을 덮는 최소 개수의 타일을 구하는 문제.
	문제는 그 공간이 원형이다.

	status에는 4가지 가능성이 존재함 11, 10, 01, 00
	1은 점유, 0은 미점유

	경계면은 어떻게 처리하지????
*/
#include <iostream>
#include <array>
#include <vector>

using Cache = std::array<int, 4>;
using pii = std::pair<int, int>;

Cache& dp(Cache& prev, Cache& cur)
{

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T, N, W;
	std::cin >> T;
	while (T--)
	{
		std::cin >> N >> W;
		std::vector<pii> wontagon(N);
		for (int i = 0; i < N; ++W)
			std::cin >> wontagon[i].first;
		for (int i = 0; i < N; ++W)
			std::cin >> wontagon[i].second;

		// dp, 4 times

	}
}


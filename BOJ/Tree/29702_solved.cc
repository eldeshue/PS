/*
	BOJ 29702

	로직은 쉬운데, 출력 형식에서 오버플로우 이슈를 내버리니, 문제가 심각합니다....
*/
#include <iostream>
#include <string>
#include <cmath>

using ll = long long;

std::string order_to_room(ll const order)	// O(1)
{
	// get floor num
	ll floor_num = 0;
	while (order >= (1LL << floor_num))
		floor_num++;

	// get floor order
	ll const floor_order = order - (1LL << (floor_num - 1)) + 1;

	// convert floor order to string
	std::string suffix = std::to_string(floor_order);

	// count additional 0
	std::string middle_zero(18 - suffix.size(), '0');

	// sum
	// 방 번호(최대 2자리) + 18자리라서 64비트 범위를 넘어버림
	// 문자열로 결합해줘야 문제가 없음.
	return std::to_string(floor_num) + middle_zero + suffix;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T; ll N;
	std::cin >> T;
	while (T--)	// O(T) 10000
	{
		std::cin >> N;
		while (N) // log N, 60
		{
			std::cout << order_to_room(N) << '\n';
			N >>= 1;
		}
	}
}


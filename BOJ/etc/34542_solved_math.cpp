/*
	BOJ 34542

	==============================

	각 move마다 거리를 2배로 늘려가며 이동할 때, 순번마다 가질 수 있는 최종 변위는 다음과 같다.

	1

	１　３

	１　３　５　７

	１　３　５　７　９　１１　１３　１５

	결론은 n번 이동에 대해서 2^n번 미만의 홀수 만큼의 변위를 갖는다

	그렇다면, 이러한　홀수들의　조합으로　주어진　차를　구할　수　있는가？

	=======================================

	－２　８　－＞　１０　－＞　１０１０　－＞　３회，　１　３　５　７　－＞　（３，　７），　（７，　３），　（５，５）　

	＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

	123 - 45 = 78

	1001110 -> ６회

	64개, 63까지의 홀수 가능

	78을 표현하기 위해서는 63까지

	(63, 15), (61, 13), ... (39, 39) -> 1 + 24
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int A, B;
	std::cin >> A >> B;

	int const d = std::abs(A - B);

	// diff check
	if (d & 1)
	{
		std::cout << -1;
		return 0;
	}

	// get min count
	int min_move = 0;
	for (int i = d >> 1; i > 0; i = i >> 1)
	{
		++min_move;
	}

	// pair count
	// odd numbers
	int count = 0;
	int i = d / 2;
	if (i & 1)
	{
		count++;
		i += 1;
	}
	count += ((1 << min_move) - i);

	std::cout << min_move << ' ' << count;
}

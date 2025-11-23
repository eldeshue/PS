/*
	BOJ 16104

	확장 기위바위보에서 그 우열 관계를 정의하는 문제

	가위바위보가 옳바른 게임으로 성립하기 위해서는 다음의 두 조건 만족 필요

	0. 요소(가위, 바위, 보, ...)의 수가 홀수개
	1. 자기 자신과는 무승부
	2. 남은 절반에 대해선 승리, 나머지는 패배

	-----

	따라서, 남은 절반에 대하여 N/2만큼은 승리, 나머진 패배, 연속적으로 정의
	N을 넘어가면 나머지 연산으로 circular하게 결정
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 1; j <= N / 2; ++j)
		{
			std::cout << i + 1 << ' ' << (i + j) % N + 1 << '\n';
		}
	}
}


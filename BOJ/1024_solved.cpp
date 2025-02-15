
/*
	
	boj 1024, 수열의 합

	문제를 등변 직각삼각형과 밑변을 공유하는 직사각형의 넓이의 합으로 이해.

	먼저 L * (L - 1) / 2를 구함. -> 등변 직각삼각형의 넓이
	N보다 작으면 실패, 
	N보다 크다면 이제 판별을 시작
	기본적으로 L만큼 늘리거나 L + 1만큼 늘릴 수 있음	

	L만큼 늘린다 -> 삼각형 확장 종료, 경사면을 제외한 나머지의 넓이가 직사각형임.
	L + 1만큼 늘린다 -> 삼각형 확장, 나머지가 직사각형이 안됨.

*/
#include <iostream>

int N, L;		// N : total sum, L : minimum length of the arr

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int start;
	std::cin >> N >> L;
	if ((L * (L - 1) / 2) > N)
	{
		std::cout << -1;
		return 0;
	}
	start = 0;
	N -= L * (L - 1) / 2;
	while (N > 0)
	{
		if (N % L == 0)
		{
			start = N / L;
			N = 0;
			break;
		}
		N -= L++;
	}
	if (L > 100 || N < 0)
	{
		std::cout << -1;
		return 0;
	}
	for (int i = 0; i < L; ++i)
	{
		std::cout << start + i << ' ';
	}
	return 0;
}

/*
	boj 1783, 병든 나이트

	가능한 맵의 크기가 대단히 크다, 따라서 완전 탐색이 아님.
	가능한 이동 방법인 4가지 모두를 사용할 수 있어야 함.
	
	한 번 갔던 곳을 다시 가면 안되는 법이 없음.
	하지만 한 번 갔던 곳을 다시 갈 수는 없음.

	두 칸씩 우측으로 이동하는 경우를 최소화 하면 됨.
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int R, C;			
	std::cin >> R >> C;
	if (R <= 1)	// 그냥 이동이 불가능
	{
		std::cout << R;
	}
	else if (R == 2)	// 1칸씩 이동이 불가능
	{
		if (C < 3)	// 이동이 불가능
		{
			std::cout << 1;
		}
		else if (C < 9)	// 두칸씩만 이동가능
		{
			std::cout << (C - 1) / 2 + 1;
		}
		else // 횟수 제한에 의해 고정
		{
			std::cout << 4;
		}
	}
	else // 한 칸씩 이동이 가능함
	{
		if (C < 5) // 4회 미만 이동, 무조건으로 1칸씩 이동
		{
			std::cout << C;
		}
		else if (C == 5) // 4회 이동의 예외처리, 2칸씩 1회 & 1칸씩 3회
		{
			std::cout << 4;
		}
		else // 2번의 2번, 그 외는 모두 1번씩 이동
		{
			std::cout << C - 2;
		}
	}
}
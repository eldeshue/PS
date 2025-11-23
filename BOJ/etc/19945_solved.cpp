/*
	BOJ 19945

	2진수 정수의 데이터를 어떻게 표현하는가를 다루는 간단한 문제.

	C/C++ 계열을 사용한다면 쉽다.
*/

#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	if (n == 0)
	{
		std::cout << 1;
		return 0;
	}
	else if (n < 0)
	{
		std::cout << 32;
		return 0;
	}
	for (int i = 0; i < 32; ++i)
	{
		if (n == 1)
		{
			std::cout << i + 1;
			return 0;
		}
		n >>= 1;
	}
}

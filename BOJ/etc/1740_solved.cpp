
/*
	BOJ 1740

	한 개 이상의 3의 거듭 제곱의 합으로 표현되는 수
	그 중 N번째로 작은 수를 구하라고 함.

	============================================
	N의 비트 표기를 생각하자.
	-> N은 각 base의 유무를 의미하는 일종의 마스크라 생각할 수 있음.
	-> N은 따라서 2의 거듭 제곱의 합으로 표현됨.
	-> N은 N번째 작은 수임.

	문제에서 원하는 바가 3의 거듭 제곱의 합이라 하였으니,
	입력으로 받은 N을 분해, 3의 거듭제곱의 합으로 재조합 하면 될 뿐이다.
*/
#include <iostream>
using ll = unsigned long long;
int main()
{
	ll N;
	std::cin >> N;
	ll result = 0;
	ll base = 1;
	for (int i = 0; i < 64; ++i)
	{
		if (N & (1ULL << i))
		{
			result += base;
		}
		base *= 3;
	}
	std::cout << result;
}

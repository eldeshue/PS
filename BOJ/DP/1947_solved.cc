
#include <iostream>

#define DIV 1000000000

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long N, ppA = 0, pA = 1, A;
	std::cin >> N;
	if (N == 1)
		std::cout << ppA;
	else if (N == 2)
		std::cout << pA;
	else
	{
		for (int i = 3; i <= N; ++i)
		{
			A = ((i - 1) * (ppA + pA)) % DIV;
			ppA = pA;
			pA = A;
		}
		std::cout << A;
	}
}


/*
	boj 13018

	n과 k가 주어짐.

	1~n으로 수열을 만들어야 하는데,
	수열 A[i]에 대하여 gcd(i, A[i]) > 1을 k개 만족해야 함.
	===================================================

	그 자신과 gcd하면 쉽게 1보다 크게 될 수 있음.
	따라서, n-k ~ n은 그 자신과 매칭하고,
	나머지 경우 1~n - k는 1 shift한다.
	n == k일 때 불가능함.
*/
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, k;
	std::cin >> n >> k;
	if (n == k)
	{
		std::cout << "Impossible";
		return 0;
	}

	std::vector<int> result(n, 0);
	result[0] = n - k;
	std::iota(result.begin() + 1, result.begin() + (n - k), 1);
	std::iota(result.begin() + n - k, result.begin() + n, n - k + 1);
	for (auto const i : result)
		std::cout << i << ' ';
}

/*
	boj 13018

	n�� k�� �־���.

	1~n���� ������ ������ �ϴµ�,
	���� A[i]�� ���Ͽ� gcd(i, A[i]) > 1�� k�� �����ؾ� ��.
	===================================================

	�� �ڽŰ� gcd�ϸ� ���� 1���� ũ�� �� �� ����.
	����, n-k ~ n�� �� �ڽŰ� ��Ī�ϰ�,
	������ ��� 1~n - k�� 1 shift�Ѵ�.
	n == k�� �� �Ұ�����.
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
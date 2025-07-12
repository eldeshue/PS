
/*
	BOJ 2482 ����ȯ

	N�� K�� �־���.

	N���� ���� 1~N �߿��� ���� �������� �ʰ� K���� �̾ƾ� ��.
	�� �������� ���ϱ�.

	====================================================
	�뷫���� ����� �˾Ҵµ�, �������� �䱸�ϴ� ȯ�̶�� ȯ���� ������.

	�� ���� ���� N���� ���� ��(����)�� ���Ͽ� ���� 1�� ������ ��츦 ��������� ��.
	�� �� �հ� �� �ڰ� ���ÿ� ���õǴ� ��츦 ��������� �ϴµ�....

	====================================================

	ex) N = 10, K = 5
	result = 2
	{1 3 5 7 9}, {2 4 6 8 10}

	ex) N = 10, K = 6
	result = 0
	N / K < 2�̹Ƿ�, ������ ������ �߻���.

	ex) N = 10, K = 1
	result = 10
	���� �̾Ƶ� �ߺ��� �߻����� ����.

	ex) N = 4, K = 2
	result = 2

	ex) N = 5, K = 2
	result = 5

	ex) N = 5, K = 1
	result = 5

	ex) N = 6, K = 2
	result = 9
*/
#include <iostream>
#include <vector>

using C = std::vector<std::vector<int>>;
constexpr const int MOD = 1000'000'003;

int memoize(C& cache, int n, int k)
{
	// base case
	if (k > (n + 1) / 2) return 0; // �������� �ʰ� k�� �� ��
	else if (k == 0) return 1;	// �ƹ��͵� ���� �ʴ� ����� ���� 1���� �ݵ�� ����
	else if (n == 0) return 0;	// ���� ���Ұ� 0�� -> �������� ����.
	else if (cache[n][k] != -1)
	{
		// cache hit
		return cache[n][k];
	}

	// cache miss
	return cache[n][k] = (
		memoize(cache, n - 1, k)	// n��° ���Ҹ� �������� ����.
		+ memoize(cache, n - 2, k - 1)// n��° ���Ҹ� ������.
		) % MOD;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> N >> K;
	C cache(N + 1, std::vector<int>(K + 1, -1));

	// 1�� ���Ҹ� ������ ���� 1�� ���Ҹ� �������� ���� ���
	std::cout << (memoize(cache, N - 1, K) + memoize(cache, N - 3, K - 1)) % MOD;
}
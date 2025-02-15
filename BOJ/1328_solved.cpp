
/*
	dp - memoization

	N���� ����, 1~N�� permutation
	���ʿ��� �ٶ� ������ ���� �����ʿ��� �ٶ� ������ ��
	���� �� ���´� 3���� ��(max, left, right)���� ǥ���ǰ�,
	�� ���¸��� ������ ��ġ, �� permutation�� ���� �˰�ʹ�.

	F(n, l, r) : ���� ������ �����ϴ� permutation�� ��

	base case : l �Ǵ� r�� ���� 0�� ��� 0

	��ȭ��, ���� ���¸� �����ϴ� ��� ���� +1�� �ϰ�, ���� 1�� ���� �߰��Ѵٰ� ��������
	���� ���� = (�� �ʿ� 1 �߰�) + (���� �ʿ� 1 �߰�) + (���� ���̿� 1 �߰�)
	F(n, l, r) = F(n - 1, l - 1, r) + f(n - 1, l, r - 1) + () * f(n - 1, l, r)

*/
#include <functional>
#include <iostream>
#include <vector>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	static constexpr ll DIV = 1000000007;
	int N, L, R;
	std::cin >> N >> L >> R;
	std::vector<std::vector<std::vector<ll>>> cache(N + 1,
		std::vector<std::vector<ll>>(N + 1,
			std::vector<ll>(N + 1, -1)));
	std::function<ll(int, int, int)> memoize
		= [&](int n, int l, int r) {
		// symmetricism, keep order n > l > r
		if (l < r)
			std::swap(l, r);

		if (n <= 0 || l <= 0 || r <= 0)	// base case, impossible
		{
			return 0LL;
		}
		else if ((n == 1) && (l == 1) && (r == 1))
		{
			return 1LL;
		}
		else if (cache[n][l][r] != -1)	// cache hit
		{
			return cache[n][l][r];
		}
		else // cache miss, erase largest
		{
			return cache[n][l][r] = (memoize(n - 1, l - 1, r) + memoize(n - 1, l, r - 1)
				+ memoize(n - 1, l, r) * std::max(0, n - 2)) % DIV;
		}
		};
	std::cout << memoize(N, L, R);
}
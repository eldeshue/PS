
/*
	dp - memoization

	N개의 정수, 1~N의 permutation
	왼쪽에서 바라본 빌딩의 수와 오른쪽에서 바라본 빌딩의 수
	따라서 한 상태는 3개의 값(max, left, right)으로 표현되고,
	각 상태마다 가능한 배치, 즉 permutation의 수를 알고싶다.

	F(n, l, r) : 상태 조건을 만족하는 permutation의 수

	base case : l 또는 r의 값이 0인 경우 0

	점화식, 현재 상태를 구성하는 모든 값에 +1을 하고, 높이 1인 블럭을 추가한다고 생각하자
	현재 상태 = (왼 쪽에 1 추가) + (오른 쪽에 1 추가) + (사이 사이에 1 추가)
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
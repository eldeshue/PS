
#include <iostream>
#include <array>

using ll = long long;
using MAT = std::array<std::array<ll, 2>, 2>;
constexpr int MOD = 1000000007;
constexpr MAT A = {1, 1, 1, 0};

MAT operator*(const MAT &m1, const MAT &m2)
{
	MAT result;
	result[0][0] = ((m1[0][0] * m2[0][0]) % MOD + (m1[0][1] * m2[1][0]) % MOD) % MOD;
	result[0][1] = ((m1[0][0] * m2[0][1]) % MOD + (m1[0][1] * m2[1][1]) % MOD) % MOD;
	result[1][0] = ((m1[1][0] * m2[0][0]) % MOD + (m1[1][1] * m2[1][0]) % MOD) % MOD;
	result[1][1] = ((m1[1][0] * m2[0][1]) % MOD + (m1[1][1] * m2[1][1]) % MOD) % MOD;
	return result;
}

MAT powerMatrix(ll n)
{
	if (n == 1)
	{
		return A;
	}
	else
	{
		MAT ret = powerMatrix(n >> 1);
		ret = ret * ret;
		if (n & 1)
		{
			ret = ret * A;
		}
		return ret;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N;
	std::cin >> N;
	if (N == 0)
		std::cout << 0;
	else if (N == 1)
		std::cout << 1;
	else
	{
		MAT result = powerMatrix(N - 1);
		std::cout << result[0][0];
	}
}

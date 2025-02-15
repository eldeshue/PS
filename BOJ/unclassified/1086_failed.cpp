
/*
	길이 50짜리 숫자에서 나머지를 추출할 수 있는가?
	-> 할 수 있음. 모듈로 연산은 (합, 차, 곱) 분배법칙이 가능하므로.
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using ll = long long;
using pii = std::pair<ll, ll>;
using Cache = std::vector<std::vector<ll>>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// modulo 연산은 분배법칙이 가능하다.
	auto modOfPoweredNum = [](const ll base, const ll pow, const ll div)
		{
			ll result = base % div;
			for (int i = 0; i < pow; ++i)
			{
				result *= 10LL;
				result %= div;
			}
			return result;
		};

	int N;
	ll K;
	std::cin >> N;
	std::vector<std::string> nums(N);
	for (auto &n : nums)
	{
		std::cin >> n;
	}
	std::cin >> K;
	auto modOfPowK = std::bind(modOfPoweredNum,
		std::placeholders::_1, std::placeholders::_2, K);
	Cache c(1 << N, std::vector<ll>(K, -1));

	// data transform
	std::vector<pii> shiftAndLeft(N);
	std::transform(nums.begin(), nums.end(), shiftAndLeft.begin(),
		[&](const std::string &num)
		{
			const ll S = num.size();
			ll result = 0;
			for (int i = 0; i < S; ++i)
				result = (result + modOfPowK(num[i] - '0', S - i - 1)) % K;
			return pii(modOfPowK(1, S), result % K);
		});

	/*
	// DP, tabulation failed
	// total, under 7.3728E+8
	for (int num = 0; num < N; ++num) // N, 15
	{
		for (int curMask = 0; curMask < (1 << N); ++curMask) // 1 << N, 32k
		{
			for (int curMod = 0; curMod < K; ++curMod) // K, 100
			{
				for (int idx = 0; idx < N; ++idx)	// N, 15
				{
					if (curMask & (1 << idx))
						continue;
					const int nextMask = curMask | (1 << idx);
					const int nextMod
						= (
							curMod * shiftAndLeft[idx].first // modulo 분배법칙은 곱셈에 대해서도 가능하다.
							+ shiftAndLeft[idx].second) % K;
					(*pNext)[nextMask][nextMod] += (*pCur)[curMask][curMod];
				}
			}
		}
		std::swap(pCur, pNext);
	}
	*/
	// memoization
	std::function<ll(const int, const int)> memoize = [&](const int mask, const int mod)
		{
			if (mask == 0 && mod == 0) // base case
			{
				return c[0][0] = 1;
			}
			else if (c[mask][mod] != -1) // cache hit
			{
				return c[mask][mod];
			}
			else // cache miss
			{
				ll sum = 0;
				for (int idx = 0; idx < N; ++idx)
				{
					if (mask & (1 << idx))
					{
						for (int prevMod = 0; prevMod < K; ++prevMod)
						{
							const int curMod = (prevMod * shiftAndLeft[idx].first // modulo 분배법칙은 곱셈에 대해서도 가능하다.
								+ shiftAndLeft[idx].second) % K;
							if (mod == curMod)
							{
								sum += memoize(mask - (1 << idx), prevMod);
							}
						}
					}
				}
				return c[mask][mod] = sum;
			}
		};

	// 기약분수화
	ll numerator = memoize((1 << N) - 1, 0);
	ll denominator = 0;
	for (int mod = 0; mod < K; ++mod)
	{
		denominator += memoize((1 << N) - 1, mod);
	}
	if (numerator == 0)
	{
		denominator = 1;
	}
	else
	{
		// use euclid algorithm
		const ll gcd = [](ll s, ll b) {
			while (s != 0)
			{
				b %= s;
				std::swap(s, b);
			}
			return b;
			}(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
	std::cout << numerator << '/' << denominator;
}

#include <iostream>
#include <vector>
#include <numeric>

using ll = long long;
constexpr ll DIV = 1e9 + 9;

enum STATUS
{
	A,
	AB,
	ABA,
	ABC,
	ABAB,
	ABCB,
	ETC
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N, K;
	std::cin >> N >> K; 

/*
	// how?????? 
	dp[0] = 1;
	for (int i = 1; i <= N; ++i) {
		dp[i] = dp[i - 1] * K;
		if (i >= 5)
			dp[i] -= dp[i - 5] * 2;
		if (i >= 7)
			dp[i] += dp[i - 7];
		dp[i] = (dp[i] + MOD) % MOD;
	}
	cout << (dp[N] + MOD) % MOD << endl;
*/


	// initial value
	std::vector<std::vector<ll>> cache(N + 1, std::vector<ll>(7, 0));
	cache[1][A] = 1;
	cache[1][ETC] = K - 1;

	// tabulation
	for (int n = 2; n <= N; ++n)
	{
		cache[n][A] = (
			cache[n - 1][A]			// AA -> A
			+ cache[n - 1][ABA]		// ABAA -> A
			+ cache[n - 1][ABC]		// ABCA -> A
			+ cache[n - 1][ABCB]	// ABCBA -> A
			+ cache[n - 1][ETC]		// rest
			) % DIV;

		cache[n][AB] = cache[n - 1][A];	// AB

		cache[n][ABA] = (cache[n - 1][AB]	// ABA
					+ cache[n - 1][ABAB]	// ABABA -> A
			) % DIV;

		cache[n][ABC] = cache[n - 1][AB];

		cache[n][ABAB] = cache[n - 1][ABA];

		cache[n][ABCB] = cache[n - 1][ABC];

		// no pattern
		// total - curSum - pattern
		cache[n][ETC] = (
			(cache[n - 1][A] * (K - 2))			// except AA, AB
			+ (cache[n - 1][AB] * (K - 2))		// except ABA, ABC
			+ (cache[n - 1][ABA] * (K - 2))		// except ABAB, ABAA -> A
			+ (cache[n - 1][ABC] * (K - 2))		// except ABCB, ABCA -> A
			+ (cache[n - 1][ABAB] * (K - 2))	// except ABABC(X), ABABA -> A
			+ (cache[n - 1][ABCB] * (K - 2))	// except ABCBC(X), ABCBA -> A
			+ (cache[n - 1][ETC] * (K - 1))		// except A
			) % DIV;
	}

	// print result
	std::cout << std::accumulate(cache[N].begin(), cache[N].end(), 0LL) % DIV;
}
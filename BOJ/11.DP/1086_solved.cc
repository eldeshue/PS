
#include <algorithm>
#include <bit>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using ll = long long;
using pii = std::pair<int, int>;

int main()
{
	// fast IO
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, K;
	std::cin >> N;
	std::vector<std::string> nums(N);
	for (auto &input : nums)
		std::cin >> input;
	std::cin >> K;

	// preprocessing
	// calculate mod of power of 10, shift
	std::vector<int> modOfShift(51, 1);
	modOfShift[1] = 10 % K;
	for (int i = 2; i <= 50; ++i)
		modOfShift[i] = (modOfShift[i - 1] * modOfShift[1]) % K; // distrubution of modulo
	// calculate mod of big int
	std::vector<pii> modAndShifts(N);
	std::transform(nums.begin(), nums.end(), modAndShifts.begin(), [&](const std::string &str)
				   {
					// modulo of string, modulo of shift
					int modSum = 0;
					for (int i = 0; i < str.size(); ++i)
					{
						modSum += ((str[str.size() - 1 - i] - '0') % K * modOfShift[i]) % K;
					}
					return std::make_pair(modSum % K, modOfShift[str.size()]); });

	// tabulation
	// num of str, bit mask, mod = count
	// 15 * 32K * 100 * 15 = 30 * 30 * 8 * 10^5 = 72 * 10^7
	std::vector<std::vector<ll>> cache(1 << 15, std::vector<ll>(K, 0));
	cache[0][0] = 1;
	for (int i = 0; i < N; ++i) // N : 1 ~ 15
	{
		for (u_int16_t curStat = 0; curStat < (1 << 15); ++curStat) // stat, 1 ~ 2^15
		{
			if (std::popcount(curStat) != i)
				continue;
			for (int curMod = 0; curMod < K; ++curMod) // K, 1 ~ 100
			{
				if (cache[curStat][curMod] == 0)
					continue;
				for (int j = 0; j < N; ++j) // N : 1 ~ 15
				{
					if ((curStat & (1 << j)) == 0) // except double checking
					{
						const int nextStat = curStat | (1 << j);
						const int nextMod = ((curMod * modAndShifts[j].second) % K + modAndShifts[j].first) % K;
						cache[nextStat][nextMod] += cache[curStat][curMod];
					}
				}
			}
		}
	}

	// collect result
	const int finalState = (1 << N) - 1;
	const ll totalCnt = std::accumulate(cache[finalState].begin(), cache[finalState].end(), 0LL);
	const ll correctCnt = cache[finalState][0];
	const ll gcdVal = std::gcd(totalCnt, correctCnt);
	std::cout << correctCnt / gcdVal << '/' << totalCnt / gcdVal;
}

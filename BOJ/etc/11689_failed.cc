
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	ll N;
	std::cin >> N;

	// prime decomposition
	// too slow, failed.
	const ll origin = N;
	std::vector<ll> prime;
	for (long long i = 2; N > 1; ++i)
	{
		if ((N % i) == 0)
		{
			prime.push_back(i);
			while ((N % i) == 0)
			{
				N /= i;
			}
		}
	}

	// calculate euler phi
	if (prime.empty())
		std::cout << N - 1;
	else
		std::cout << std::accumulate(prime.begin(), prime.end(), origin, [](const ll acc, const ll p)
									 { return (acc / p) * (p - 1); });
}

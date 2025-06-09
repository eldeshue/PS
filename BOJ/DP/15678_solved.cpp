
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	// input
	int N, D;
	std::cin >> N >> D;
	std::vector<ll> K(N);
	for (auto& k : K)
		std::cin >> k;

	// dp
	std::deque<int> dq;
	std::vector<ll> cache(N);
	for (int i = 0; i < N; ++i)
	{
		while (!dq.empty() && (i - dq.front()) > D)
		{
			dq.pop_front();
		}

		ll max_prev = 0;
		if (!dq.empty())
			max_prev = cache[dq.front()];
		cache[i] = max_prev + K[i];

		while (!dq.empty() && cache[dq.back()] <= cache[i])
		{
			dq.pop_back();
		}

		if (cache[i] >= 0)
			dq.push_back(i);
	}


	// print
	std::cout << std::accumulate(cache.begin(), cache.end(),
		std::numeric_limits<ll>::min(),
		[](ll const acc, ll const n) {
			return std::max(acc, n);
		});
}
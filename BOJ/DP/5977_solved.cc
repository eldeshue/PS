/*
	BOJ 5977

	dp에 monoton-deque를 이용한 최적화 문제.

	길이 N인 배열이 주어지고, 여기서 최대가 되도

	===============================================

	점화식, j번째 원소를 취하지 않음.
	cache[i] = prefix_sum[i] - prefix_sum[j] + cache[j - 1];
 */

#include <iostream>
#include <vector>
#include <deque>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	// input
	int N, K;
	std::cin >> N >> K;
	std::vector<ll> cows(N);
	std::vector<ll> prefix_sum(N);
	for (auto& c : cows)
		std::cin >> c;
	prefix_sum[0] = cows[0];
	for (int i = 1; i < N; ++i)	// prefix sum
		prefix_sum[i] = cows[i] + prefix_sum[i - 1];

	// dp with two-pointer
	std::vector<ll> cache(N, -1);
	auto get_cache_val = [&](int pos) -> ll {
		if (pos < 0)
			return 0;
		return cache[pos];
		};
	auto get_sum = [&](int idx) -> ll {
		return get_cache_val(idx - 1) - prefix_sum[idx];
		};

	std::deque<int> dq;
	for (int i = 0; i < N; ++i)
	{
		// keep local K status
		while (!dq.empty() && i - dq.front() > K) {
			dq.pop_front();
		}
		// keep monotonicity, pop back
		while (!dq.empty() && get_sum(dq.back()) <= get_sum(i)) {
			dq.pop_back();
		}
		// push back
		dq.push_back(i);

		// update cache
		cache[i] = prefix_sum[i] + get_sum(dq.front());

		// keep monotonicity and prefix sum
		if (i < K)
			cache[i] = std::max(cache[i], prefix_sum[i]);
	}

	// print
	std::cout << cache[N - 1];
}

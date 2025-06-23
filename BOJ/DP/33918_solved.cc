/*
	BOJ 33918

	덱을 활용한 dp. maximize result.

	문제의 점화식은 다음과 같음.
	cache : 시점 t의 최대 맛.
	b : 시점 t의 적정 온도.
	k : 시점 t의 실제 온도. k[0]는 자유임.

	cache[t] = cache[t - 1] + M - abs( b[t - 1] - k[t - 1] )

	다만, 시점 t의 실제 온도인 k[t]를 구하기 위해서는 이전 시점의 온도 k[t - 1]이 필요함.
	즉, 현재 dp를 수행하기 위해서 필요한 정보는 시점 t와 온도 k임.

	온도 k에 제한이 존재하는데,
	k[t] = k[t - 1] + C * n
	즉, C의 배수로만 온도가 올라감.

	이러한 온도의 제한까지 고려하면 점화식을 다음과 같음. 즉 k 또한 독립 변수가 되어야 함.
	- prev_k와 k 사이에는 C * n의 차이가 존재.
	- prev_k와 k 사이의 온도 차이는 최대 D를 넘을 수 없다. -> deque?


	cache[t][k] = cache[t - 1][ prev_k ] + d
	d = M - abs( b[t - 1] - prev_k )

	즉 naive하게 풀면 N * M * M이 나온다... 이 부분을 deque의 monotonicity로 해소해야 함.

	deque을 M개 만들어서 유지해야 하는가?
	즉 3차원 dp를 2차원 dp로 만든다? 최적화를 위한 deque을 M개 만들어서?

	================================================

	N <= 200, M <= 25000
	따라서 목표로 하는 시간 복잡도는 O(N * M)인 것으로 보이는데....

	=======================================================

	세그먼트 트리를 활용한 최적화는 조금 간단할 것으로 보임.
	현재 온도 K를 기준으로 +-D 범위로 range max query를 때려서 prev 값을 얻을 예정임
	C개의 segtree를 구성, t-1의 prev k에 대하여 segtree를 구성해두는 것을 고려
	-> N * M * logM

	seg tree 대신에 두 개의 deque을 사용하는게 어떠한지?
	현재 확인할 k보다 작으면 left dq, 현재 확인할 k보다 크면 right dq로 하고
	k를 C로 나눈 나머지에 따라서 여러 dq를 준비하면 가능할 것으로 생각됨

	k가 증가함에 따라서 l의 front는 pop, r의 front는 pop하여 l의 back으로,
*/

#include <iostream>
#include <vector>
#include <deque>
#include <numeric>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	// input
	int N, C;
	ll M, D;
	std::cin >> N >> M >> C >> D;
	std::vector<ll> b(N);
	for (ll& n : b)
		std::cin >> n;

	// dp, max value
	std::vector<std::vector<ll>> cache(N + 1, std::vector<ll>(M + 1, 0));
	std::vector<std::deque<ll>> dqs(C);	// holds temperature
	auto get_val = [&](int const t, ll const prev_k) {
		return cache[t][prev_k] + M - std::abs(b[t] - prev_k);
		};
	for (int t = 0; t < N; ++t)	// O(N)
	{
		for (auto& dq : dqs)
			dq.clear();
		for (int k = 1; k <= M; ++k)	// O(M)
		{
			auto& dq = dqs[k % C];

			// keep invariant 1, pop front until k - D
			while (!dq.empty() && D < k - dq.front())
			{
				dq.pop_front();
			}

			// keep invariant 2, push back until k + D
			int nk = k;
			if (!dq.empty())
				nk = dq.back() + C;
			for (; nk <= std::min(M, k + D); nk += C)
			{
				while (!dq.empty() && get_val(t, dq.back()) <= get_val(t, nk))
				{
					dq.pop_back();
				}
				dq.push_back(nk);
			}

			// calculate current cache
			cache[t + 1][k] = get_val(t, dq.front());
		}
	}

	// result
	std::cout << std::accumulate(cache[N].begin(), cache[N].end(), 0LL, [](ll acc, ll c) { return std::max(acc, c);});
}
/*
// naive solution
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	// input
	int N, M, C, D;
	std::cin >> N >> M >> C >> D;
	std::vector<ll> b(N);
	for (ll& n : b)
		std::cin >> n;

	// naive solution
	// dp, max value
	std::vector<std::vector<ll>> cache(N + 1, std::vector<ll>(M + 1, 0));
	for (int t = 1; t <= N; ++t)
	{
		// cur temperature -> start temperature???
		for (int k = 1; k <= M; ++k)
		{
			// will this loop be updated by deque???
			// prev temperature, k +- n * C within D
			// 덱을 이용하여 최적화를 수행하기에는 두 가지 문제가 존재함.
			// 하나는 온도가 C 단위로 증가하기에 불연속적이라는 점. 따라서 시작 온도를 기준으로 C가 차이가 날 수 밖에
			for (int n = 0; n * C <= D; ++n)
			{
				for (int p = -1; p <= 1; p += 2)
				{
					int const pk = k + p * n * C;
					if (1 <= pk && pk <= M)	// in range
					{
						cache[t][k] = std::max(cache[t][k], M + cache[t - 1][pk] - std::abs(b[t - 1] - pk));
					}
				}
			}
		}

	}

	// result
	std::cout << std::accumulate(cache[N].begin(), cache[N].end(), 0LL, [](ll acc, ll c) { return std::max(acc, c);});
}
*/

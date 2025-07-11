
/*
	BOJ 12456

	커피를 가치가 높은 것 부터 고려한다.

	만약 유통기한에 여유가 있다면 먹는다.

	유통기한에 여유가 없다면, 이미 먹은 것들 중에 유통기한이 넉넉한 것과 교체한다.

	이 이미 먹은 커피를 우선순위 큐로 관리한다. 언제 먹었는지를 기준으로 관리한다.

	유통기한이 임박한 물건부터 교체를 수행한다. 이미 유통기한이 지나서 재배치가 불가능한 커피는 우선순위 큐에서 제거한다.

	-> 우선순위 큐에서 제거한 커피가 후일 다시 필요해지면 어떻게 하려고 제거하는지? 정렬 기준이 value라서 미리 버릴 수 없다.
	-> fail.

	=================================================================

	유통기한 순으로 정렬해서 짧은 것 부터 고려한다.

	먼저 유통기한에 여유가 있다면, 일단 소비한다.

	또한 이미 소비한 커피 중 현재 고려하는 커피가 더 유익하다면 판단하면 교체한다.

	교체 대상이 될 커피를 찾기 위해서 우선순위 큐를 사용한다.

	우선순위 큐로 단위 만족도가 낮은 블럭의 min heap으로 유지하자.
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

using ll = long long;
using Coffee = std::tuple<ll, ll, ll>;	// c t s
using UsedCoffee = std::pair<ll, ll>; // s, c

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for (int i = 1; i <= T; ++i)
	{
		// input
		ll N, K;
		std::cin >> N >> K;
		std::vector<Coffee> input(N);
		for (auto& [c, t, s] : input)
			std::cin >> c >> t >> s;

		// sort by time domain, ascending order
		std::sort(input.begin(), input.end(), [](Coffee const& _1, Coffee const& _2) {
			auto const& [c1, t1, s1] = _1;
			auto const& [c2, t2, s2] = _2;

			if (t1 == t2)
			{
				if (c1 == c2)
				{
					return s1 > s2;
				}
				return c1 < c2;
			}
			return t1 < t2;
			});

		// solve
		std::priority_queue<UsedCoffee, std::vector<UsedCoffee>, std::greater<UsedCoffee>> pq;	// mean heap
		ll result = 0, cur_cap = 0;
		for (auto& [c, t, s] : input)
		{
			if (cur_cap == K)
				break;

			// simpel consume
			{
				// update
				ll gap = std::min(std::min(t - cur_cap, K - cur_cap), c);
				result += gap * s;
				c -= gap;
				cur_cap += gap;

				// push
				pq.push(std::make_pair(s, gap));
			}

			// replacement
			while (!pq.empty() && c > 0)
			{
				if (s <= pq.top().first)
					break;

				// pick prev coffee to replace
				auto [rs, rc] = pq.top();
				pq.pop();

				// update
				ll gap = std::min(rc, c);
				result += (s - rs) * gap;	// replace
				c -= gap;
				rc -= gap;

				// new UsedCoffee
				pq.push(std::make_pair(s, gap));

				// if there are a rest, put it again
				if (rc != 0)
					pq.push(std::make_pair(rs, rc));	// means c == 0
			}
		}

		// print
		std::cout << "Case #" << i << ": " << result << '\n';
	}
}

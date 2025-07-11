
/*
	BOJ 13975

	두 파일을 결합하는 비용이 두 파일의 크기의 합이다

	즉 다시 말하면, 최종 cost에서 특정 파일의 cost는 여러번 지불된다. 즉 최종 cost에 참여하는 횟수가 다르다.

	비용을 최소화 하기 위해서는 크기가 큰 파일을 최대한 드물게 결합해야 한다.

	우선순위 큐를 준비하고, 이 큐에 모든 파일, 임시 파일을 참여한 다음, 큐의 크기가 1이 될 때 까지 작은 것 둘을 결합, 다시 집어 넣는다.
*/

#include <iostream>
#include <vector>
#include <queue>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T, K;
	std::cin >> T;
	while (T--)
	{
		ll result = 0, n;

		// input
		std::cin >> K;
		std::priority_queue<ll, std::vector<ll>, std::greater<ll>> pq;
		for (int i = 0; i < K; ++i)
		{
			std::cin >> n;
			pq.push(n);
		}

		// solve
		while (pq.size() != 1)
		{
			n = 0;
			n += pq.top();
			pq.pop();
			n += pq.top();
			pq.pop();

			result += n;
			pq.push(n);
		}

		// print
		std::cout << result << '\n';
	}
}


#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using Delivery = std::tuple<int, int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, C, M;
	std::cin >> N >> C >> M;
	std::vector<Delivery> requests(M);
	for (auto& [start, end, cnt] : requests)
		std::cin >> start >> end >> cnt;

	// sort requests
	// O(N log N), quick sort
	// 문제의 목적은 배달 용량의 최대화, 즉 through put의 최대화다
	// 따라서 배달 완료를 먼저 생각해야 한다
	// 따라서 배달 완료 시점을 기준으로 먼저 정렬해야 한다
	std::sort(requests.begin(), requests.end(),
		[](Delivery const& d1, Delivery const& d2) {
			auto const& [s1, e1, c1] = d1;
			auto const& [s2, e2, c2] = d2;
			if (e1 == e2)
			{
				if (s1 == s2)
				{
					return c1 < c2;
				}
				return s1 < s2;
			}
			return e1 < e2;
		});

	// solution : greedy, look back from future
	// O(N * M)
	std::vector<int> carryStatus(N + 1, 0);
	int totalDeliveryWeight = 0;
	for (auto const& [start, end, cnt] : requests)	// M
	{
		// 운반하기로 결정한 양과 운반 가능한 용량을 비교하여, 가능한 용량을 구한다
		// 짐을 먼저 내린 후, 짐을 싣기 때문에 end는 포함하지 않는다
		int availableCapacity = C;
		for (int i = start; i < end; ++i)	// N
		{
			availableCapacity = std::min(availableCapacity, C - carryStatus[i]);
		}
		// 가능한 용량curCapacity와 배달 요청량cnt를 비교하여 실재 운반할 용량을 구한다
		int const curCarry = std::min(cnt, availableCapacity);
		// 운반하기로 결정한 양을 반영한다
		for (int i = start; i < end; ++i)	// N
		{
			carryStatus[i] += curCarry;
		}
		totalDeliveryWeight += curCarry;
	}

	// output
	std::cout << totalDeliveryWeight;
}
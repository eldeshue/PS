
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
	// ������ ������ ��� �뷮�� �ִ�ȭ, �� through put�� �ִ�ȭ��
	// ���� ��� �ϷḦ ���� �����ؾ� �Ѵ�
	// ���� ��� �Ϸ� ������ �������� ���� �����ؾ� �Ѵ�
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
		// ����ϱ�� ������ ��� ��� ������ �뷮�� ���Ͽ�, ������ �뷮�� ���Ѵ�
		// ���� ���� ���� ��, ���� �Ʊ� ������ end�� �������� �ʴ´�
		int availableCapacity = C;
		for (int i = start; i < end; ++i)	// N
		{
			availableCapacity = std::min(availableCapacity, C - carryStatus[i]);
		}
		// ������ �뷮curCapacity�� ��� ��û��cnt�� ���Ͽ� ���� ����� �뷮�� ���Ѵ�
		int const curCarry = std::min(cnt, availableCapacity);
		// ����ϱ�� ������ ���� �ݿ��Ѵ�
		for (int i = start; i < end; ++i)	// N
		{
			carryStatus[i] += curCarry;
		}
		totalDeliveryWeight += curCarry;
	}

	// output
	std::cout << totalDeliveryWeight;
}
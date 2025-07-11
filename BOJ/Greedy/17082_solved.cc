
/*
	BOJ 17082

	누적 쿼리라서 쿼리 순서 교체가 안됨.
	swap 쿼리를 처리하면 배열의 원소 상태가 변경됨. 즉 M개의 쿼리의 구성이 바뀌어야 할 수 있음.

	=======================================================

	목표는 쿼리를 다 처리하고 난 후에 얻는 값들 중 최댓값을 최소화 하는게 목표.
	일단 swap하는 것은 답에 영향을 미치지 않는다. 왜냐 하면 swap의 대상이 되려면 이미 답에 사용되었기 때문임.
	L > R이 되어버리면 바로 fail

	==================================================================

	이미 사용될 L과 R은 결정되어 있음.
	그래서 LR을 어떻게 조합해도 의미가 없음. 어차피 무조건 모든 쌍을 써야 함.
	따라서 L과 R을 각각 정렬하고 순서대로 1대1 대응하는 것이 가장 싸다. 이 방식이 가장 범위를 좁히는 길임.
	어차피 겹쳐있으면, 매칭 순서를 바꿔도 겹친 영역은 변함이 없다.
	M개의 쿼리 set이 확정됨.

	이후에는 swap query의 적용으로 인한 값의 update가 중요함

	=============================

	N, M, Q : 200K -> N log N
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using Query = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M, Q;
	std::cin >> N >> M >> Q;
	std::vector<int> nums(N), left(M), right(M);
	std::vector<Query> swap_queries(Q);	// swap query
	for (auto& n : nums)
		std::cin >> n;
	for (auto& l : left)
	{
		std::cin >> l;
		l--;
	}
	for (auto& r : right)
	{
		std::cin >> r;
		r--;
	}
	for (auto& [i, j] : swap_queries)
	{
		std::cin >> i >> j;
		i--;
		j--;
	}

	// handling query
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	std::vector<int> is_occupied(N, false);
	std::multiset<int> query_results;// can accelerate this with seg tree

	// pre-processing range queries
	int pos = -1;
	for (int i = 0; i < M; ++i)	// zip left and right
	{
		if (left[i] > right[i])
		{
			query_results.insert(1e9);
			continue;
		}
		pos = std::max(pos, left[i]);
		while (pos <= right[i])
		{
			is_occupied[pos] = true;
			query_results.insert(nums[pos]);
			pos++;
		}
	}

	// swap query
	for (auto [i, j] : swap_queries)
	{
		// swap
		if (is_occupied[i])
		{
			auto erase_target_itr = query_results.find(nums[i]);
			query_results.erase(erase_target_itr);
			query_results.insert(nums[j]);
		}
		if (is_occupied[j])
		{
			auto erase_target_itr = query_results.find(nums[j]);
			query_results.erase(erase_target_itr);
			query_results.insert(nums[i]);
		}
		std::swap(nums[i], nums[j]);

		// get result
		std::cout << *query_results.rbegin() << '\n';
	}
}

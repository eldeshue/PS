
/*
	BOJ 14908, 구두 수선공

	프로세스 스케줄링 시뮬레이션 문제.

	한 프로세스의 실행 시간 : T 한 프로세스의 대기 비용 : 시간 당 C

	대기 비용을 최소화 하는 스케줄을 구하시오.

	==========================================================

	누구를 먼저 스케줄링하냐에 따라서 전체적인 비용이 증가함.

	한 프로세스를 선택하면,
	나머지 모든 프로세스는 해당 프로세스의 t만큼 대기하고, 각 비용이 t*c 발생함.

	즉, 대기하는 것을 통해서 비용이 발생함.

	이게 문제가 특정 프로세스를 선택하면, 다른 모든 프로세스의 비용이 변화함.
	따라서, 선택으로 인해 발생하는 비용을 탐색하는 것에만 N^2이 필요함.
	따라서 모든 원소를 재배치하기에는 총 N^3이라 한다.

	최적화의 목표는 O(N N log N)임.

	==========================================================
	수행 시간이 길수록 미루고싶고, 대기 비용이 클수록 당기고싶음.

	어느 한 프로세스를 고르면, 다른 모든 프로세스는 공평하게 t만큼 기다리게 됨.
	따라서, total_cost를 구해두고, 이를 활용하면 어떨까?

	cost_of_picking_ith_elem = ith_time * (total_cost - ith_cost)
	여기서 total_cost는 변하는 값임. 따라서 정렬의 기준으로는 쓸 수 없음.

	이후 프로세스를 골랐다면, total_cost - picked_cost를 해서 빼주면 된다.

	이를 바탕으로 하여, 선택함으로 인해서 발생하는 대기비용이 가장 작은 경우를 먼저 치운다.
	여기서 대기 비용을 heuristic으로 삼지 않을 경우,
	이 선택되지 않은, 비용이 많이 발생하는 원소는 다음에 또 만나야 함.
	-> 즉, 미리 제거해야 다시 만나지 않는다.

	예상 비용은 N^2
	-> failed

	=============================================================
	solution : argument exchange

	0..N로 정렬된 배열에서, i와 i+1번째 원소의 순서를 바꾸면 비용적인 측면에서 어떻게 될까?
	i+2..N으로 인해서 발생하는 비용은 그대로일 것이다. 그들의 대기 시간과 그 비용은 고정이기 때문이다.

	따라서 i와 i+1을 교환하는 것으로 대기 비용이 줄어든다면, 교환하는게 greedy하다.

	이러한 교환을 인접한 모든 쌍에대해서 수행한다면, 최종적으로는 최적의 배치(정렬)을 얻을 수 있으리라.

	==========================================================================
	기본적으로 인접한 두 원소를 비교하여 swap 여부를 판단하는 방식, bubble-sort가 된다.

	다만, 문제는 이러한 비교를 인접한 모든 쌍에 대해서 반드시 수행해야 하는지가 궁금하다.
	따라서 bubble, quick, stable의 3종의 정렬을 모두 실험해본다.
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using ll = long long;
using Job = std::pair<ll, ll>;

bool argument_exchange(Job const& j1, Job const& j2)
{
	// t1 * c2 < t2 * c1
	// lhs means cost of current order
	// rhs means cost of swapped order
	return j1.first * j2.second <= j2.first * j1.second;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<Job> input(N);
	for (auto& [t, s] : input)
		std::cin >> t >> s;

	// bubble sort
	std::vector<int> result(N);
	std::iota(result.begin(), result.end(), 1);
	for (int last = N - 1; last > 0; --last)
	{
		for (int i = 0; i < last; ++i)
		{
			if (!argument_exchange(input[result[i] - 1], input[result[i + 1] - 1]))
			{
				std::swap(result[i], result[i + 1]);
			}
		}
	}

	// print
	for (auto const r : result)
		std::cout << r << ' ';
}

/*
// failed solution 2, vertical comparing
// 한 원소를 선택하지 않는 것으로 인해서 발생할,
// 해당 원소로 인해 미래에 지불할 비용 총 합을 기준으로 비교
// 해당 비용을 전부 지불할 수가 없음. 단순 예상에 불과함. -> failed
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	ll time_sum = 0;
	std::cin >> N;
	std::vector<TS> input(N);
	for (auto& [t, s] : input)
	{
		std::cin >> t >> s;
		time_sum += t;
	}

	// get total cost
	// greedy
	std::vector<bool> used(N, false);
	std::vector<int> result(N);
	for (auto& r : result)
	{
		int target_idx = -1;
		ll target_cost = -2e9;
		for (int i = 0; i < N; ++i)
		{
			if (!used[i])
			{
				ll ith_cost = input[i].second * (time_sum - input[i].first);
				if (ith_cost > target_cost)
				{
					target_cost = ith_cost;
					target_idx = i;
				}
			}
		}
		used[target_idx] = true;
		time_sum -= input[target_idx].first;
		r = target_idx + 1;
	}

	// print
	for (const auto n : result)
		std::cout << n << ' ';
}
*/

/*
// failed solution 1, horizontal comparing
// 한 원소를 선택하는 것으로 인해서 발생하는
// 다른 원소들의 대기 비용 총 합을 기준으로 비교했음
// 왜 최적해인진 증명 못함 -> failed
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	ll cost_sum = 0;
	std::cin >> N;
	std::vector<TS> input(N);
	for (auto& [t, s] : input)
	{
		std::cin >> t >> s;
		cost_sum += s;
	}

	// get total cost
	// greedy
	std::vector<bool> used(N, false);
	std::vector<int> result(N);
	for (auto& r : result)
	{
		int min_cost_idx = -1;
		ll min_cost = 2e9;
		for (int i = 0; i < N; ++i)
		{
			if (!used[i])
			{
				ll ith_cost = input[i].first * (cost_sum - input[i].second);
				if (ith_cost < min_cost)
				{
					min_cost = ith_cost;
					min_cost_idx = i;
				}
			}
		}
		used[min_cost_idx] = true;
		cost_sum -= input[min_cost_idx].second;
		r = min_cost_idx + 1;
	}

	// print
	for (const auto n : result)
		std::cout << n << ' ';
}
*/
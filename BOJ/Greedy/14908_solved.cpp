
/*
	BOJ 14908, ���� ������

	���μ��� �����ٸ� �ùķ��̼� ����.

	�� ���μ����� ���� �ð� : T �� ���μ����� ��� ��� : �ð� �� C

	��� ����� �ּ�ȭ �ϴ� �������� ���Ͻÿ�.

	==========================================================

	������ ���� �����ٸ��ϳĿ� ���� ��ü���� ����� ������.

	�� ���μ����� �����ϸ�,
	������ ��� ���μ����� �ش� ���μ����� t��ŭ ����ϰ�, �� ����� t*c �߻���.

	��, ����ϴ� ���� ���ؼ� ����� �߻���.

	�̰� ������ Ư�� ���μ����� �����ϸ�, �ٸ� ��� ���μ����� ����� ��ȭ��.
	����, �������� ���� �߻��ϴ� ����� Ž���ϴ� �Ϳ��� N^2�� �ʿ���.
	���� ��� ���Ҹ� ���ġ�ϱ⿡�� �� N^3�̶� �Ѵ�.

	����ȭ�� ��ǥ�� O(N N log N)��.

	==========================================================
	���� �ð��� ����� �̷��Ͱ�, ��� ����� Ŭ���� �������.

	��� �� ���μ����� ����, �ٸ� ��� ���μ����� �����ϰ� t��ŭ ��ٸ��� ��.
	����, total_cost�� ���صΰ�, �̸� Ȱ���ϸ� ���?

	cost_of_picking_ith_elem = ith_time * (total_cost - ith_cost)
	���⼭ total_cost�� ���ϴ� ����. ���� ������ �������δ� �� �� ����.

	���� ���μ����� ����ٸ�, total_cost - picked_cost�� �ؼ� ���ָ� �ȴ�.

	�̸� �������� �Ͽ�, ���������� ���ؼ� �߻��ϴ� ������� ���� ���� ��츦 ���� ġ���.
	���⼭ ��� ����� heuristic���� ���� ���� ���,
	�� ���õ��� ����, ����� ���� �߻��ϴ� ���Ҵ� ������ �� ������ ��.
	-> ��, �̸� �����ؾ� �ٽ� ������ �ʴ´�.

	���� ����� N^2
	-> failed

	=============================================================
	solution : argument exchange

	0..N�� ���ĵ� �迭����, i�� i+1��° ������ ������ �ٲٸ� ������� ���鿡�� ��� �ɱ�?
	i+2..N���� ���ؼ� �߻��ϴ� ����� �״���� ���̴�. �׵��� ��� �ð��� �� ����� �����̱� �����̴�.

	���� i�� i+1�� ��ȯ�ϴ� ������ ��� ����� �پ��ٸ�, ��ȯ�ϴ°� greedy�ϴ�.

	�̷��� ��ȯ�� ������ ��� �ֿ����ؼ� �����Ѵٸ�, ���������δ� ������ ��ġ(����)�� ���� �� ��������.

	==========================================================================
	�⺻������ ������ �� ���Ҹ� ���Ͽ� swap ���θ� �Ǵ��ϴ� ���, bubble-sort�� �ȴ�.

	�ٸ�, ������ �̷��� �񱳸� ������ ��� �ֿ� ���ؼ� �ݵ�� �����ؾ� �ϴ����� �ñ��ϴ�.
	���� bubble, quick, stable�� 3���� ������ ��� �����غ���.
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
// �� ���Ҹ� �������� �ʴ� ������ ���ؼ� �߻���,
// �ش� ���ҷ� ���� �̷��� ������ ��� �� ���� �������� ��
// �ش� ����� ���� ������ ���� ����. �ܼ� ���� �Ұ���. -> failed
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
// �� ���Ҹ� �����ϴ� ������ ���ؼ� �߻��ϴ�
// �ٸ� ���ҵ��� ��� ��� �� ���� �������� ������
// �� ���������� ���� ���� -> failed
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
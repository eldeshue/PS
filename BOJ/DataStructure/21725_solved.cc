
/*
	BOJ 21725

	N : 100K, M : 200K

	즉, 목표 시간 복잡도는 N 혹은 N log N

	==========================================================

	그룹 단위로 비용이 쌓인다.
	그룹 내에서는 비용을 평탄화 해야 한다.

	그룹에 비용이 쌓이긴 하는데, 사실은 특정 인원에게 비용이 쌓인다. 한 그룹 내에서 여러 사람에게 비용이 쌓인다.

	==============================================================

	naive하게 시뮬레이션 하듯이 비용을 주고받으면 N^2임.
	평탄화를 미리해서는 절대 목표를 만족할 수 없음.
	그렇다면, n번 이내에 평탄화가 안되는 경우는 무엇인가?
	N이하로 비용을 주고받을 수 있다는 것은 무슨 의미인가???

	======================================================

	case study

	병합 결과와 상관 없이, 모든 비용이 한 사람에게만 지워진다면 어떨까? -> O(N)임.

	비용을 지불한 사람이 뒤섞이면? 그러면 어떻게 되는가?

	즉, 각자 서로 다른 사람에게 돈을 줘도 되지만, 한 명은 단 한명에게만 돈을 지불하도록 구성해야 함.

	N번 이하이므로, N-2명은 1명에게 줄 수 있고, 1명은 2명에게 줄 수 있음. -> 무조건 O(N - 1) 가능함

	============================================================

	문제를 뒤집어서 생각하자. 받는 입장이 아닌, 주는 입장에서 계산하면 어떨까?

	그룹을 트리의 형태로 관리하여, 해당 그룹에 부과된 비용을 root에게 몰아서 지불하고, root는 자신의 그룹을 대표해서 비용을 지불하면, 지불 횟수를 감축할 수 있다.

	===========================================================

	돈을 내는 한 명을 root로 삼고, 해당 root에게 돈을 몰아준 다음, 이 root가 해당 그룹에 지불할 모든 돈을 대신 지불함.

	한 그룹에서 여러 명이 돈을 지불하게 되어도, 그 중 한 명에게 비용을 몰아준 다음, 이 친구가 대신 분배하면 문제가 해결 됨.

	따라서, 무조건 N번 이하로 분배를 해결할 수 있지 않은가?

	=========================================================

	union을 할 때 마다 ghost node를 subtree의 root로 삼아 그래프에 추가한다.

	이 ghost node가 자신의 subtree에 발생하는 어떤 비용 처리를 대신 수행하고, 자식 중 하나를 대표 노드로 만들어 비용을 일거에 처리하도록 만든다.

	즉, 누가 얼마를 지불했는지와 별개로 임의의 하나를 수금원으로 만들고, 이 수금원이 한 번에 해당 sub tree의 비용을 모조리 지불한다.

	이를 위해서 subtree의 leaf의 개수를 알 필요가 있음

	===========================================================

	트리에서 leaf는 실제 사람. 그 외 노드는 intermediate node

	모든 노드는 지불 비용과 수금 비용을 가지고 있음. 지불은 +, 수금은 -

	최종 비용 계산은 DFS 로 한 번에 해결할 수 있을 것으로 기대됨.

	=========================================
-
	4 6
	1 1 2
	1 1 3
	2 3 30
	1 1 4
	2 1 40
	2 4 40

	2
	2 1 30
	1 4 20
-
	4 5
	1 1 2
	1 3 4
	2 1 100
	2 3 100
	1 1 4

	3
	2 1 50
	4 3 50
-
	6 9
	1 1 2
	1 4 5
	2 1 100
	2 4 100
	1 2 3
	1 5 6
	2 3 600
	2 6 600
	1 3 6

	5
	2 1 250
	1 3 400
	5 4 250
	4 6 400
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>

#include <cassert>

using ll = long long;
using Query = std::tuple<int, int, ll>; // type, x, y or c
using Pay = std::tuple<int, int, ll>;	// from, to, cost

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N >> M;
	std::vector<Query> queries(M);
	for (auto& [t, x, y] : queries)
		std::cin >> t >> x >> y;

	// union find
	int const max_node_size = 2 * N + 1;
	std::vector<int> dset(max_node_size);
	std::fill(dset.begin() + 1, dset.begin() + N + 1, -1);	// [N+1..], ghost node
	int last_used_node = N;
	auto is_leaf = [N](int const node) -> bool {
		return node <= N;
		};
	std::function<int(int)> find = [&](int const node) -> int {
		if (dset[node] < 0)
		{
			return node;
		}
		return dset[node] = find(dset[node]);	// path compression
		};

	int root = 0;
	std::vector<ll> gsize(max_node_size, 1);
	std::vector<int> payer(max_node_size, 0);	// 지정된 한 명이 무조건 돈을 낸다
	std::vector<ll> gcost(max_node_size, 0);
	std::vector<std::vector<int>> graph(max_node_size);
	auto unite = [&](int n1, int n2) {
		n1 = find(n1);
		n2 = find(n2);

		if (is_leaf(n1))
			payer[n1] = n1;
		if (is_leaf(n2))
			payer[n2] = n2;

		if ((is_leaf(n1) && is_leaf(n2)) || (gcost[n1] != 0 || gcost[n2] != 0))	// no money spent
		{
			// new intermediate node
			// 해결해야 할 부채가 있으면 새로운 그룹으로...
			int n3 = ++last_used_node;
			gsize[n3] = gsize[n1] + gsize[n2];
			dset[n3] = -gsize[n3];

			dset[n1] = n3;
			graph[n3].push_back(n1);
			dset[n2] = n3;
			graph[n3].push_back(n2);

			payer[n3] = payer[n1];
			root = n3;
		}
		else	// gcost[n1] == 0 && gcost[n2] == 0
		{
			// union by size
			if (dset[n1] < dset[n2])
			{
				dset[n1] += dset[n2];
				dset[n2] = n1;

				graph[n1].push_back(n2);
				gsize[n1] += gsize[n2];

				root = n1;
			}
			else
			{
				dset[n2] += dset[n1];
				dset[n1] = n2;

				graph[n2].push_back(n1);
				gsize[n2] += gsize[n1];

				root = n2;
			}
		}
		};

	// handling query
	for (auto& [t, x, y] : queries)
	{
		if (t == 1)
		{
			unite(x, y);
		}
		else	// t == 2
		{
			// pay
			int const rx = find(x); // root of x

			// skip when size == 1
			if (x == rx)
				continue;

			gcost[rx] += y;	// root는 해당 금액을 분배해야 하고
			gcost[x] -= y;	// 실제 지불한 x는 해당 금액을 받아야 함.
		}
	}

	std::vector<Pay> result;
	auto pay = [&](int const payer, int const receiver, ll cost) {
		if (payer == receiver)
			return;
		result.push_back(Pay(payer, receiver, cost));
		};

	// dfs, collect pay record
	// from root, stack over flow???
	// add_collect : 추가적으로 걷어야 할 금액, 음수가 되면 지불해야 함
	std::function<ll(int, ll)> dfs = [&](int cur_node, ll add_collect) -> ll {
		if (is_leaf(cur_node))	// base case, paying my self means nothing
		{
			return add_collect + gcost[cur_node];
		}
		gcost[cur_node] += add_collect;	// amount of cost expected to collect
		int const pcur = payer[cur_node];
		ll const collect_per_person = gcost[cur_node] / gsize[cur_node];
		ll total_pay_back = 0;
		for (auto const child : graph[cur_node])
		{
			int const pchild = payer[child];
			ll const collect_amount = collect_per_person * gsize[child];

			ll const pay_back = dfs(child, collect_amount);	// collect

			if (pay_back > 0)	// collect from child to cur_node
			{
				pay(pchild, pcur, pay_back);
			}
			else if (pay_back < 0)
			{
				// pay from cur_node to child
				pay(pcur, pchild, -pay_back);
			}
			total_pay_back += pay_back;
		}
		return total_pay_back;
		};
	dfs(root, 0);

	// print, expect always success, N - 1 is upper bound
	assert(result.size() < N);
	std::cout << result.size() << '\n';
	for (auto const [from, to, cost] : result)
	{
		assert(cost > 0);
		assert(cost <= 2e13);
		std::cout << from << ' ' << to << ' ' << cost << '\n';
	}
}

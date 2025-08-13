
/*
	BOJ 28121 산책과 쿼리.

	갔던 경로를 되짚는 것은 무조건 짝수.
	따라서 짝수 개 경로는 무조건 탈 수 있음.

	홀수개 에지로 구성된 사이클이 있어야 함.
	홀수 사이클이 하나만 존재하면 무조건 가능.

	========================================================

	naive하게 생각하면, dfs 등으로 그래프를 순회하여 홀수사이클이 존재하는 연결요소를 counting하면 됨.
	문제는 update 쿼리가 있다는 것. 쿼리로 연결 요소가 업데이트 될 때 마다 dfs를 돌릴 수는 없음.

	===========================================================

	어느 하나라도 홀수 사이클이 있다면, 이 홀수 사이클이 있는 연결 요소와 결합되는 경우, 그 연결 요소의 모든 원소가 다 자유롭게 됨.

	===========================================================

	사이클이 만들어질 때, 해당 연결요소 내의 몇 번째 원소가 서로 결합했는지 아는게 중요함.

	사이클을 이루려면 두 번의 결합이 필요한데, 첫 결합에서 각 원소마다 연결 요소 내에서 자신의 번호를 알아야 함.
	-> 예를 들면 44번과 11번이 결합한다면, 이 사이클을 이루는 edge의 개수는 (44 - 11) + 1이 됨을 알 수 있음.

	또한, 이후의 결합에서 어느 한 쪽이 자유로이면우며, 연결 요소의 원소 전체가 자유로워짐.

	문제는 연결 요소를 병합하는 과정에서 자신의 번호가 몇 번인지 update가 필요하다는 점임.

	즉 A 연결 요소에서 4번과 B 연결 요소에서 5번이 결합했을 때, 이들의 객관적인 번호를 알 수 있는가?

	union할 때 offset도 함께 unite해야 하겠음.

	유니온 파인드를 사용하면 연결요소를 대표하는 하나의 노드를 얻게 되고, 이 노드에 offset을 두면 된다고 생각했음.

	결합하게 되는 두 노드의 offset을 고려한 위치 정보에 대하여 그 차이가 홀수면 짝수 사이클이 생성되고, 그 차이가 짝수인 경우 홀수 사이클이 생성됨.

	=======================================================================================

	번호를 업데이트 할 필요가 없음. 그냥 현재 특정 노드가 짝수번째인지 홀수번째인지 그 부분만 저장하면 됨.

	connected component의 root에 이 connected component의 offset을 저장함.
	pass compression을 통해서 이 offset을 업그레이드.

	==========================================================

	내 풀이의 경우, union 과정에서 발생하는 홀짝의 update를 path compression으로 평균 O(1)에 해결했는데,
	만약 small to large 방법으로 일일이 업데이트 해줬다면, O(log N)이 들었을 것임.

	=================================

	5 6
	1 2
	2 3
	2 4
	2 5
	1 3
	4 5

	0
	0
	0
	0
	5
	5

	==========================================

	6 6
	1 2
	2 3
	3 4
	3 5
	2 5
	5 6

	0
	0
	0
	0
	5
	6

	=========================================

	2025.07.19, 정말 힘들었다.
	- 홀수 offset을 전파하는 과정을 생각하기 어려웠다.
	- is_odd를 false로 초기화 하는 부분에서 벌인 에러가 해소하기 어려웠다.
	- small to large를 생각했으면 보다 빠르게 is_odd를 update했을 텐데, 이를 생각치 못했음.
	- 그러나 현재 180ms로 2등.
*/
#include <iostream>
#include <vector>
#include <functional>

using Query = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, Q;
	std::cin >> N >> Q;
	std::vector<Query> queries(Q);
	for (auto& [a, b] : queries)
		std::cin >> a >> b;

	// disjoint set
	// is_odd table
	std::vector<int> disjoint_set(N + 1, -1);
	std::vector<bool> is_odd(N + 1, false);	// 연결 요소의 root는 offset으로 false를 가져야 함. 의도치 않은 update 방지

	// update is_odd
	// O(1)
	auto update_is_odd = [&](int const parent, int const child, int const rc) {
		// change child
		// already propagated
		if (is_odd[parent] == is_odd[child])
		{
			is_odd[rc] = !is_odd[rc];
		}
		};

	// find : path compression
	// asymptotically O(1)
	std::function<int(int)> find = [&](int const node) -> int {
		// base case
		if (disjoint_set[node] < 0)
		{
			return node;
		}

		// during path compression, must update is_odd
		int const parent = disjoint_set[node];
		int const root = find(parent);

		// propagate lazy
		// accumulate offset from root
		is_odd[node] = (is_odd[node] != is_odd[parent]);

		return disjoint_set[node] = root;	// path compression
		};

	// unite : unite by size, bigger one goes to the parent
	// asymptotically O(1)
	auto unite = [&](int const n1, int const n2) {
		int const r1 = find(n1);
		int const r2 = find(n2);

		if (r1 == r2)
			return;
		if (disjoint_set[r1] < disjoint_set[r2])
		{
			// n1 is higher rank
			// n1 is parent of n2
			disjoint_set[r1] += disjoint_set[r2];
			disjoint_set[r2] = r1;
			update_is_odd(n1, n2, r2);
		}
		else
		{
			// n2 is higher rank
			// n2 is parent of n1
			disjoint_set[r2] += disjoint_set[r1];
			disjoint_set[r1] = r2;
			update_is_odd(n2, n1, r1);
		}
		};

	// processing queries
	int free_cnt = 0;
	std::vector<bool> is_free(N + 1, false);
	std::vector<int> result(Q);
	for (int i = 0; i < Q; ++i)	// O(Q)
	{
		auto [a, b] = queries[i];
		int ra = find(a);	// root of a, update odd of a
		int rb = find(b);
		if (ra == rb)
		{
			// cycle found
			// update result
			if (is_odd[a] == is_odd[b] && !is_free[ra])	// updated by find
			{
				is_free[ra] = true;
				free_cnt -= disjoint_set[ra];
			}
		}
		else
		{
			// cycle not found
			// but if there are already a cycle?
			if (is_free[ra] != is_free[rb])
			{
				if (is_free[rb])
					std::swap(ra, rb);

				// append free cc
				is_free[rb] = true;
				free_cnt -= disjoint_set[rb];
			}

			// unite cc
			unite(a, b);
		}

		// get result
		result[i] = free_cnt;
	}

	// print
	for (auto const r : result)
	{
		std::cout << r << '\n';
	}
}


/*
	BOJ 13306

	유니온 파인드에서 병합이 아닌 분리의 쿼리를 처리해야 한다.
	두 노드 사이에 경로가 존재하느냐라는 질문은 유니온 파인드에서 파인드를 통해 쉽게 풀 수 있다.

	문제는 경로 삭제 쿼리다. 경로가 삭제된 상태의 문제를 어떻게 풀 수 있는가?

	=================================================================================

	쿼리를 역순으로 풀면 되지 않을까? 에지를 삭제하는 쿼리만 있다고 했는데, 그래프 생성 과정에서 삭제할 에지는 먼저 다 반영하고,
	쿼리를 역순으로 처리해서 올라가면 될 것 같다.

	유니온 파인드는 그 구조 상 분리는 힘들다. 오프라인 쿼리가 가능하고, 간선 제거 쿼리가 N-1개 주어지므로, 최종적으로는 모든 서브트리의 크기가 1이 된다.
	따라서, 모두 분해된 상태에서 쿼리를 역순으로 처리하여 병합을 해나갈 수 있음.

	문제의 힌트는 간선을 제거하는 쿼리가 N-1개 주어지는 부분이었는데, N-1개를 다 잘라서 모든 서브트리의 크기가 1로 시작하기에 역순 처리를 생각할 수 있음.
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <variant>
#include <tuple>
#include <stack>

class UnionFind
{
private:
	int numGroup;
	mutable std::vector<int> parent;

public:
	UnionFind(int size) : parent(size, -1), numGroup(size) {};
	int getGroupNum() const { return numGroup; }
	int getMaxGroupSize() const
	{
		int result = 0;
		std::for_each(parent.begin(), parent.end(), [&](const int& val) -> void
			{if (val < 0) { result = std::max(result, std::abs(val)); } });
		return result;
	};
	int find(int node) const // pass compression, is it const?
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	bool isSameGroup(int node1, int node2) const // ???
	{
		node1 = find(node1);
		node2 = find(node2);
		return node1 == node2;
	}
	void unite(int node1, int node2) // unite by rank
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] >= parent[node2]) // node2's rank is higher
		{
			if (parent[node1] == parent[node2])	// same rank
			{
				parent[node1]--;	// rank increase
			}
			parent[node1] = node2;
		}
		else // node1's rank is higher than node2's rank
		{
			parent[node2] = node1;
		}
		numGroup--;
		return;
	}
};

using Q1 = int;
using Q2 = std::pair<int, int>;	// answer query
using Query = std::variant<Q1, Q2>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, Q;
	std::cin >> N >> Q;
	std::vector<int> parents(N + 1);
	for (int i = 2; i <= N; ++i)
		std::cin >> parents[i];
	std::vector<Query> queries(Q + (N - 1));
	for (int i = 0; i < Q + (N - 1); ++i)
	{
		int q, n1, n2;
		std::cin >> q;
		if (q == 0)
		{
			std::cin >> n1;
			queries[i] = Query(n1);
		}
		else
		{
			std::cin >> n1 >> n2;
			queries[i] = Query(std::make_pair(n1, n2));
		}
	}

	// reversing query
	UnionFind uf(N + 1);
	std::stack<bool> result;
	for (auto ritr = queries.rbegin(); ritr != queries.rend(); ++ritr)
	{
		Query q = *ritr;
		if (q.index() == 0)	// query1, merge with parent
		{
			int const node = std::get<Q1>(q);
			uf.unite(node, parents[node]);
		}
		else	// query2, is same tree?
		{
			auto const [n1, n2] = std::get<Q2>(q);
			result.push(uf.isSameGroup(n1, n2));
		}
	}

	// print result
	while (!result.empty())
	{
		if (result.top())
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
		result.pop();
	}
}

/*
	BOJ 17469

	union find + 역방향 오프라인 쿼리 + 작은 집합을 큰 집합으로 결합
*/
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

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

using Query = std::pair<int, int>;
using ColorSet = std::unordered_set<int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input, initialization
	int N, Q;
	std::cin >> N >> Q;
	std::vector<int> parents(N + 1, 0);
	for (int i = 2; i <= N; ++i)
		std::cin >> parents[i];
	std::vector<ColorSet*> color_sets(N + 1, nullptr);
	for (int i = 1; i <= N; ++i)
	{
		color_sets[i] = new std::unordered_set<int>;
		int c;
		std::cin >> c;
		color_sets[i]->insert(c);
	}
	std::vector<Query> queries(N + Q - 1);
	for (auto& [type, a] : queries)
		std::cin >> type >> a;

	// offline query, union find
	UnionFind uf(N + 1);
	std::vector<int> results(Q);
	int qidx = Q - 1;
	for (auto ritr = queries.rbegin(); ritr != queries.rend(); ++ritr)
	{
		auto [type, a] = *ritr;
		a = uf.find(a);	// O(1)에 수렴
		if (type == 1) // merge query
		{
			// unite, O(1)에 수렴
			int const parent_a = uf.find(parents[a]);
			uf.unite(a, parent_a);

			// merge sets
			int const dest = uf.find(a);	// 결합 후의 root
			int const source = (dest == a) ? parent_a : a;	// 상대편
			ColorSet*& d_set = color_sets[dest];
			ColorSet*& s_set = color_sets[source];
			if (d_set->size() < s_set->size())	// 작은 집합을 큰 집합으로 결합
				std::swap(d_set, s_set);
			d_set->insert(s_set->begin(), s_set->end());// 총 결합 비용 O(N log N)
			delete s_set;
			s_set = nullptr;
		}
		else
		{
			results[qidx--] = color_sets[a]->size();	//  O(1)
		}
	}

	// print
	for (auto const cnt : results)
	{
		std::cout << cnt << '\n';
	}
}
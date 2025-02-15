

#include <iostream>
#include <vector>

using namespace std;

/*
	O(N ^ 2)에 전터리를 수행하고, O(1)에 각 쿼리를 처리하는 풀이
	그래프를 dfs로 순회하면서 자식을 set에 저장하고, 이들을 재귀적으로 merge하여 자식의 set을 확장해간다

	자식에 대한 정보를 set으로 저장하므로, 각 쿼리를 O(1)에 처리할 수 있음.

	다만, 다수의 hash set을 사용하기에 복잡도는 좋아도, 실제 실행 성능이 상당히 떨어짐

	better solution -> floyd-warshall algorithm
	a에서 b를 향하는 경로가 있다 -> a는 b의 prerequisite이다.
	이를 이용해 O(N^3)으로 전처리하고, O(1)으로 쿼리를 처리할 수 있음.
	해시를 사용하지 않는 관계로 훠얼씬 빠르다.
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <functional>
#include <unordered_set>
class Solution
{
private:
	using ChildSet = unordered_set<int>;
public:
	// solution method
	vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
	{
		// build graph
		vector<vector<int>> graph(numCourses);
		for (auto const& e : prerequisites)
			graph[e[0]].push_back(e[1]);

		// dfs, init parent table, O(N ^ 2)
		vector<ChildSet> children(numCourses);
		function<ChildSet(int const)> dfs = [&](int const curNode) {
			if (graph[curNode].empty() || !children[curNode].empty()) // cache hit
			{
				return children[curNode];
			}
			// cache miss
			for (int const nextNode : graph[curNode])
			{
				children[curNode].merge(dfs(nextNode));
				children[curNode].insert(nextNode);
			}
			return children[curNode];
			};
		for (int i = 0; i < numCourses; ++i)
			children[i] = dfs(i);

		// handling query, O(Q)
		vector<bool> result;
		transform(queries.begin(), queries.end(), back_inserter(result), [&](std::vector<int> const& q) {
			return (children[q[0]].find(q[1]) != children[q[0]].end());
			});
		return result;
	}
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}


#include <iostream>
#include <vector>
#include <string>

/*
	unsigned int를 기준으로 했을 때,
	일반적으로 and를 할 수록 cost는 감소하는 경향이 있음 -> 최대한 많은 경로를 거쳐야 함
	다만, 더 적은 cost가 필요할 뿐
	노드의 개수가 10^5, 쿼리의 개수가 10^5
	시점과 종점이 다양하게 주어지는 상태이므로, 플로이드 워셜을 고려할텐데
	n^3이라서 불가능함

	따라서, union find를 이용하여 해당 연결요소 내에 있는 모든 엣지를 다 경험하는 것을 목표로 구현
	따라서, 같은 연결 요소 내에서는 같은 cost가 나올 것
	연결 요소 단위의 cost, 즉 모든 edge의 누적을 수행할 필요가 있
*/

using namespace std;

#include <algorithm>
#include <functional>

class Solution
{
private:
public:
	vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query)
	{
		// builde disjoint set
		vector<int> disjointSet(n, -1);
		vector<uint> totalCost(n, -1);

		function<int(int const)> find = [&](int const node) {
			if (disjointSet[node] < 0)
				return node;
			else
				return disjointSet[node] = find(disjointSet[node]);
			};
		auto unite = [&](int const node1, int const node2, int const cost) {
			int const p1 = find(node1);
			int const p2 = find(node2);
			if (p1 == p2)
			{
				// same cc
				totalCost[p1] &= cost;
				return;
			}

			// union by rank
			if (disjointSet[p1] < disjointSet[p2])
			{
				// p1 is parent
				disjointSet[p1] += disjointSet[p2];
				disjointSet[p2] = p1;
				totalCost[p1] &= totalCost[p2] & cost;
			}
			else
			{
				// p2 is parent
				disjointSet[p2] += disjointSet[p1];
				disjointSet[p1] = p2;
				totalCost[p2] &= totalCost[p1] & cost;
			}
			};

		for (auto const& e : edges)
		{
			unite(e[0], e[1], e[2]);
		}

		// handle query
		vector<int> result;
		transform(query.begin(), query.end(), back_inserter(result), [&](auto const& q) {
			// same cc,
			int const n1 = find(q[0]);
			int const n2 = find(q[1]);
			if (n1 == n2)
				return static_cast<int>(totalCost[n1]);
			else
				// different cc
				return -1;
			});
		return result;
	}
};


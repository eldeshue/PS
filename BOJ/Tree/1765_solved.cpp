/*
	BOJ 1765

	1. 친구는 모두 다 함께 친구다.
	2. 적의 적은 모두 동료다.

	집합을 관리하는데, 친구와 적을 모두 관리해야 함.

	단순 f쿼리는 문제가 아님, 문제는 e쿼리임.

	e쿼리의 문제는 적을 가르켜 줄 뿐,
	union을 할 대상인 적의 적이누구인지 알려주지 않았음.
	따라서, 내 적이 누구인지 하나 기억할 필요가 있음.
	하나만 기억하면 되는 이유는, 어차피 모든 원수는 같은 group에 속할 것이기 때문임

	해당 문제의 결과는 여러 이분 그래프가 독립적으로 존재하는 구조가 될 것임

	원수의 원수가 친구가 된다는 것은, 원수들도 마찬가지.
	따라서 이분 그래프가 될 것으로 보임. 오직 친구와 적으로만 나뉘어진 그런....

	최대의 팀 수를 원한다고 했으므로, 굳이 결합할 이유가 없는 팀은 방치
*/
#include <algorithm>
#include <iostream>
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


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	UnionFind friends(N + 1);
	std::vector<int> enemies(N + 1, -1);
	for (int i = 0; i < M; ++i)
	{
		char c;
		int p, q;
		std::cin >> c >> p >> q;
		if (c == 'F')	// friends
		{
			friends.unite(p, q);
		}
		else if (c == 'E')	// enemies
		{
			if (enemies[p] == -1)
			{
				enemies[p] = q;
			}
			if (enemies[q] == -1)
			{
				enemies[q] = p;
			}
			// enemy of enemy is my friend
			friends.unite(p, enemies[q]);
			friends.unite(q, enemies[p]);
		}
	}
	std::cout << friends.getGroupNum() - 1;
}
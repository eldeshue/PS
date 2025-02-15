
#include <iostream>
#include <vector>

using ll = long long;
using Point = std::pair<ll, ll>;
using LineSeg = std::pair<Point, Point>;

// union-find
class UnionFind
{
private:
	int numGroup;
	mutable std::vector<int> parent;

public:
	UnionFind(int size) : parent(size, -1), numGroup(size){};
	int getGroupNum() const { return numGroup; }
	int getMaxGroupSize() const
	{
		int result = 0;
		std::for_each(parent.begin(), parent.end(), [&](const int &val) -> void
					  {if(val < 0){result = std::max(result, -val);} });
		return result;
	};
	int find(int node) const // pass compression
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	void unite(int node1, int node2) // unite by size
	{
		node1 = find(node1);
		node2 = find(node2);
		if (node1 == node2)
			return;
		if (parent[node1] > parent[node2]) // node2's size is bigger
		{
			parent[node2] += parent[node1];
			parent[node1] = node2;
		}
		else // node1's size is bigger or same
		{
			parent[node1] += parent[node2];
			parent[node2] = node1;
		}
		numGroup--;
		return;
	}
};

Point operator+(const Point &p1, const Point &p2)
{
	return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

Point operator-(const Point &p1, const Point &p2)
{
	return std::make_pair(p1.first - p2.first, p1.second - p2.second);
}

int operator*(const Point &p1, const Point &p2) // cross product
{
	return p1.first * p2.second - p1.second * p2.first;
}

// cross detection, ccw
bool isCross(LineSeg &l1, LineSeg &l2)
{
	auto &[p11, p12] = l1;
	auto &[p21, p22] = l2;
	Point v1 = p12 - p11;
	Point p21p11 = p21 - p11;
	Point p22p11 = p22 - p11;
	ll p21v1 = p21p11 * v1;
	ll p22v1 = p22p11 * v1;
	if (p21v1)
		p21v1 /= std::abs(p21v1);
	if (p22v1)
		p22v1 /= std::abs(p22v1);
	Point v2 = p22 - p21;
	Point p11p21 = p11 - p21;
	Point p12p21 = p12 - p21;
	ll p11v2 = p11p21 * v2;
	ll p12v2 = p12p21 * v2;
	if (p11v2)
		p11v2 /= std::abs(p11v2);
	if (p12v2)
		p12v2 /= std::abs(p12v2);
	ll result1 = p21v1 * p22v1;
	ll result2 = p11v2 * p12v2;
	if (result1 == 0 && result2 == 0) // parallel
	{
		if (l1.first > l1.second) // sort by order of x
			std::swap(l1.first, l1.second);
		if (l2.first > l2.second)
			std::swap(l2.first, l2.second);
		return ((l1.first <= l2.first && l2.first <= l1.second) // is overlap
				|| (l1.first <= l2.second && l2.second <= l1.second));
	}
	else
		return (result1 <= 0) && (result2 <= 0);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<LineSeg> lines(N, {{0, 0}, {0, 0}});
	for (auto &l : lines)
	{
		auto &[p1, p2] = l;
		std::cin >> p1.first >> p1.second >> p2.first >> p2.second;
	}
	UnionFind uf(N);
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			if (isCross(lines[i], lines[j]))
			{
				uf.unite(i, j);
			}
		}
	}
	std::cout << uf.getGroupNum() << '\n'
			  << uf.getMaxGroupSize() << '\n';
}

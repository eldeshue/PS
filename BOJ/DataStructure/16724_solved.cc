
/*
	Union Find
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using Point = std::pair<int, int>; // y x

Point getNextPoint(const Point &p, const char c)
{
	if (c == 'U')
		return std::make_pair(p.first - 1, p.second);
	else if (c == 'D')
		return std::make_pair(p.first + 1, p.second);
	else if (c == 'L')
		return std::make_pair(p.first, p.second - 1);
	else if (c == 'R')
		return std::make_pair(p.first, p.second + 1);
	else
		return p;
}

int find(std::vector<int> &table, int node)
{
	if (table[node] >= 0)
		return table[node] = find(table, table[node]); // path compression
	return node;
}

void unite(std::vector<int> &table, int node1, int node2)
{
	node1 = find(table, node1);
	node2 = find(table, node2);
	if (node1 == node2)
		return;
	// union by rank
	if (table[node1] < table[node2])
	{
		// subtree1 is big, 1 is parent
		table[node1] += table[node2];
		table[node2] = node1;
	}
	else
	{
		// subtree2 is big
		table[node2] += table[node1];
		table[node1] = node2;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input, parsing needed
	int R, C;
	std::cin >> R >> C;
	std::vector<std::vector<char>> board(R, std::vector<char>(C, -1));
	for (int r = 0; r < R; ++r)
		for (int c = 0; c < C; ++c)
			std::cin >> board[r][c];

	// union find
	std::vector<int> disjointSet(R * C, -1);
	for (int r = 0; r < R; ++r)
	{
		for (int c = 0; c < C; ++c)
		{
			const Point nextPoint = getNextPoint(std::make_pair(r, c), board[r][c]);
			const int curPointIdx = C * r + c;
			const int nextPointIdx = C * nextPoint.first + nextPoint.second;
			unite(disjointSet, curPointIdx, nextPointIdx);
		}
	}

	// get number of node
	std::cout << std::count_if(disjointSet.begin(), disjointSet.end(), [](const int n)
							   { return (n < 0); });
}

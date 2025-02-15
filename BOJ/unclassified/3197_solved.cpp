
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using point = std::pair<int, int>;
constexpr char WATER = '.';
constexpr char ICE = 'X';
constexpr char SWAN = 'L';
constexpr char VISITED = 'O';
constexpr char MELTED = 'M';
constexpr int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

class UnionFind
{
private:
	int numGroup;

public:
	mutable std::vector<int> parent;
	UnionFind(int size) : parent(size, -1), numGroup(size) {};
	int getGroupNum() const { return numGroup; }
	int getMaxGroupSize() const
	{
		int result = 0;
		std::for_each(parent.begin(), parent.end(), [&](const int& val) -> void
			{if (val < 0) { result = std::max(result, std::abs(val)); } });
		return result;
	};
	int find(int node) // pass compression, is it const?
	{
		if (parent[node] < 0)
			return node;
		return (parent[node] = find(parent[node]));
	}
	bool isSameGroup(int node1, int node2) // ???
	{
		node1 = find(node1);
		node2 = find(node2);
		return node1 == node2;
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


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int s1 = -1, s2 = -1, H, W;
	std::cin >> H >> W;
	std::vector<std::string> board(H);
	std::queue<point> q1, q2;
	UnionFind uf(H * W);
	for (int i = 0; i < H; ++i)
		std::cin >> board[i];
	// 
	auto bfsUnite = [&](int sR, int sC) -> void
		{
			const int startIdx = sR * W + sC;

			board[sR][sC] = VISITED;
			q2.push(std::make_pair(sR, sC));
			while (!q2.empty())
			{
				const auto& [cR, cC] = q2.front();
				for (int i = 0; i < 4; ++i)
				{
					const int nR = cR + dir[i][0];
					const int nC = cC + dir[i][1];
					if (0 <= nR && nR < H 
						&& 0 <= nC && nC < W
						&& board[nR][nC] != VISITED)
					{
						if (board[nR][nC] == ICE)
							q1.push(std::make_pair(nR, nC));
						else
							q2.push(std::make_pair(nR, nC));
						uf.parent[nR * W + nC] = startIdx;
						board[nR][nC] = VISITED;
					}
				}
				q2.pop();
			}
		};
	for (int r = 0; r < H; ++r)
	{
		for (int c = 0; c < W; ++c)
		{
			if (board[r][c] == SWAN)
			{
				if (s1 == -1)
					s1 = r * W + c;
				else
					s2 = r * W + c;
				bfsUnite(r, c);
			}
		}
	}
	// 
	for (int r = 0; r < H; ++r)
	{
		for (int c = 0; c < W; ++c)
		{
			if (board[r][c] == WATER)
			{
				bfsUnite(r, c);
			}
		}
	}
	// bfs, ice melt
	int time = 0;
	std::queue<point> *pCurQ = &q1, *pNextQ = &q2;
	while (!uf.isSameGroup(s1, s2))
	{
		// unite
		while (!pCurQ->empty())
		{
			const auto& [cR, cC] = pCurQ->front();
			const int curPointIdx = cR * W + cC;
			board[cR][cC] = VISITED;
			for (int i = 0; i < 4; ++i)
			{
				const int nR = cR + dir[i][0];
				const int nC = cC + dir[i][1];
				if (0 <= nR && nR < H
					&& 0 <= nC && nC < W )
				{
					if (board[nR][nC] == VISITED)
						uf.unite(curPointIdx, nR * W + nC);
					if (board[nR][nC] == ICE)
					{
						board[nR][nC] = MELTED;
						pNextQ->push(std::make_pair(nR, nC));
					}
				}
			}
			pCurQ->pop();
		}
		time++;
		std::swap(pCurQ, pNextQ);
	}
	std::cout << time;
}
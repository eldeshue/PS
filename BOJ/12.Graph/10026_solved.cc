
/*
	그래프 탐색, 연결요소 식별

	정방형 맵이 주어짐. 각각의 노드는 색으로 구분되며, 4방으로 인접하고, 같은 색이면 노드가 연결되었다고 함.
	문제는 주어진 맵에서 연결 관계를 파악하고, 연결요소의 개수를 구하는 것.

	단, 처음에는 3가지 색(R,G,B)을 식별하고, 그 다음에는 두 가지 색(RG, B)을 식별해야 함.

	문제의 구성 자체는 상당히 평이했고, 그냥 구현만 하면 되는 문제임.
	그러나 과정을 잘 관찰하면 중복되는 구석이 상당히 많아서, 이 부분을 어떻게 묶어내는지가 중요한 부분.
	즉 구현의 깔끔함을 평가하는 문제였다고 보임.

	개선된 구현을 위해서 함수형 프로그래밍을 적극 도입함.
	각 색을 식별하는 과정을 별도의 함수객체로 수행함.

	함수형 프로그래밍의 장점을 크게 느낀 문제였음.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>

constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N;
	std::vector<std::string> map(N);
	for (int i = 0; i < N; ++i)
		std::cin >> map[i];
	M = map[0].size();

	using ColorId = std::function<bool(char)>; // color Identifier, will be passed to identify color

	auto inRange = [&](int r, int c) -> bool
	{ return (0 <= r) && (r < N) && (0 <= c) && (c < M); };

	auto isRed = [](char color) -> bool
	{ return color == 'R'; };
	auto isGreen = [](char color) -> bool
	{ return color == 'G'; };
	auto isBlue = [](char color) -> bool
	{ return color == 'B'; };

	auto isRedGreen = [](char color) -> bool
	{ return color == 'R' || color == 'G'; };

	// visit connected component, color identification needed to identify cc
	auto bfs = [&map, &inRange](int sR, int sC, std::vector<std::vector<bool>> &visit, ColorId cid) -> void
	{
		std::queue<std::pair<int, int>> q;

		visit[sR][sC] = true;
		q.push(std::make_pair(sR, sC));
		while (!q.empty())
		{
			auto &[cR, cC] = q.front();
			for (int i = 0; i < 4; ++i)
			{
				int nR = cR + dir[i][0];
				int nC = cC + dir[i][1];
				if (inRange(nR, nC) && !visit[nR][nC] && cid(map[nR][nC]))
				{
					visit[nR][nC] = true;
					q.push(std::make_pair(nR, nC));
				}
			}
			q.pop();
		}
	};

	// count number of connected component
	auto countCC = [&N, &M, &bfs, &map](ColorId cR, ColorId cG, ColorId cB) -> int
	{
		std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
		int numCC = 0;

		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if (!visited[r][c])
				{
					numCC++;
					// select color
					if (cR(map[r][c]))
						bfs(r, c, visited, cR);
					else if (cG(map[r][c]))
						bfs(r, c, visited, cG);
					else
						bfs(r, c, visited, cB);
				}
			}
		}
		return numCC;
	};
	std::cout << countCC(isRed, isGreen, isBlue) << ' ' << countCC(isRedGreen, isRedGreen, isBlue);
}

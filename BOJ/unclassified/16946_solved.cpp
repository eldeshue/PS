
/*
	입력받은 맵 전체를 대상으로 bfs를 수행해서 이동 가능한 노드를 모두 칠함.
	그 결과 맵에서 하나의 연결요소는 하나의 색으로 칠할 수 있고,
	그 연결요소의 크기를 미리 구할 수 있음.

	이렇게 맵을 다 칠하면 이후 벽 노드를 부수고 그 이동가능 노드의 수를 얻을 때
	미리 구한 연결요소들을 이용함.
	인접한 연결요소의 크기를 더하는 것으로 문제의 답을 구할 수 있음.
	단, 인접한 연결요소가 중복일 수 있으므로, 이를 주의해야 함.
*/
#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_set>

constexpr int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> map(N, std::vector<int>(M));
	std::vector<std::vector<int>> colorMap(N, std::vector<int>(M, -1));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			char temp;
			std::cin >> temp;
			map[r][c] = temp - '0';
		}
	}

	auto inRange = [&](int y, int x)-> bool {
		return (0 <= y && y < N) && (0 <= x && x < M);
		};

	// paint map
	int curColor = 0;
	std::vector<int> colorCnt;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			if (map[r][c] == 0 && colorMap[r][c] == -1)
			{
				colorCnt.push_back([&]() -> int
					{
						// dfs, paint, count 
						std::queue<std::pair<int, int>> q;
						int cnt = 1;

						q.push(std::make_pair(r, c));
						colorMap[r][c] = curColor;
						while (!q.empty())
						{
							auto &[cR, cC] = q.front();
							for (int d = 0; d < 4; ++d)
							{
								int nR = cR + dir[d][0];
								int nC = cC + dir[d][1];
								if (inRange(nR, nC)
									&& map[nR][nC] == 0
									&& colorMap[nR][nC] == -1)
								{
									colorMap[nR][nC] = curColor;
									q.push(std::make_pair(nR, nC));
									cnt++;
								}
							}
							q.pop();
						}
						return cnt;
					}());
				curColor++;
			}
		}
	}
	// count result, print
	std::unordered_set<int> visited;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			int cnt = 0;
			if (map[r][c] == 1)
			{
				cnt = 1;
				for (int d = 0; d < 4; ++d)
				{
					// get cnt using adjacent color
					// use hash set, skip double count
					int color = [&]()->int
						{
							int nextR = r + dir[d][0];
							int nextC = c + dir[d][1];
							if (inRange(nextR, nextC))
							{
								return colorMap[nextR][nextC];
							}
							else
							{
								return -1;
							}
						}();
					if (color != -1 && visited.find(color) == visited.end())
					{
						visited.insert(color);
						cnt += colorCnt[color];
					}
				}
				visited.clear();
			}
			std::cout << cnt % 10;
		}
		std::cout << '\n';
	}
}
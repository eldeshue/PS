
/*
	�Է¹��� �� ��ü�� ������� bfs�� �����ؼ� �̵� ������ ��带 ��� ĥ��.
	�� ��� �ʿ��� �ϳ��� �����Ҵ� �ϳ��� ������ ĥ�� �� �ְ�,
	�� �������� ũ�⸦ �̸� ���� �� ����.

	�̷��� ���� �� ĥ�ϸ� ���� �� ��带 �μ��� �� �̵����� ����� ���� ���� ��
	�̸� ���� �����ҵ��� �̿���.
	������ �������� ũ�⸦ ���ϴ� ������ ������ ���� ���� �� ����.
	��, ������ �����Ұ� �ߺ��� �� �����Ƿ�, �̸� �����ؾ� ��.
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
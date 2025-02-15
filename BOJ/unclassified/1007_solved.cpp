
#include <iostream>
#include <cmath>
#include <memory.h>

typedef std::pair<int, int> point;

int numTest, numPoint;
double minVal;
point P[20];
bool visited[20];

double calVal()
{
	long long sx = 0, sy = 0, ex = 0, ey = 0;
	for (int i = 0; i < numPoint; ++i)
	{
		if (visited[i])
		{
			sx += P[i].first;
			sy += P[i].second;
		}
		else
		{
			ex += P[i].first;
			ey += P[i].second;
		}
	}

	return std::sqrt(std::pow(ex - sx, 2) + std::pow(ey - sy, 2));
}

void dfs(int cnt, int curNode)
{
	if (cnt == numPoint / 2)
	{
		minVal = std::min(minVal, calVal());
		return;
	}
	else
	{
		for (int next = curNode + 1; next < numPoint; ++next)
		{
			visited[next] = true;
			dfs(cnt + 1, next);
			visited[next] = false;
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cout.precision(6);
	std::cout << std::fixed;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		memset(P, 0, sizeof(P));
		memset(visited, 0, sizeof(visited));
		std::cin >> numPoint;
		for (int j = 0; j < numPoint; ++j)
		{
			std::cin >> P[j].first >> P[j].second;
		}

		minVal = 2e9;
		for (int start = 0; start < numPoint / 2; ++start)
		{
			visited[start] = true;
			dfs(1, start);
			visited[start] = false;
		}
		std::cout << minVal << "\n";
	}
}
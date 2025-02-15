
#include <iostream>
#include <memory.h>
#include <vector>
#include <bitset>
#include <cmath>

typedef std::pair<int, int> point;
typedef std::bitset<20> mask;

double minVal;
int numTest, numPoint;
int P[20][2];

double calNorm(const int x, const int y)
{
	return std::sqrt((long long)x * (long long)x + (long long)y * (long long)y);
}

void DFS(int accumX, int accumY, int curPoint, mask isMatched)
{
	if (curPoint == numPoint)	// end
	{
		minVal = std::min(minVal, calNorm(accumX, accumY));
		return;
	}
	else if (isMatched[curPoint])	// already matched, move next
	{
		return DFS(accumX, accumY, curPoint + 1, isMatched);
	}
	else
	{
		isMatched[curPoint] = true;
		int curX = P[curPoint][0];
		int curY = P[curPoint][1];

		for (int matchPoint = 0; matchPoint < numPoint; ++matchPoint)
		{
			if (!isMatched[matchPoint])
			{
				mask updateMatch = isMatched;
				updateMatch[matchPoint] = true;
				int matchX = P[matchPoint][0] - curX;
				int matchY = P[matchPoint][1] - curY;
				DFS(accumX + matchX, accumY + matchY, curPoint + 1, updateMatch);
				DFS(accumX - matchX, accumY - matchY, curPoint + 1, updateMatch);
			}
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

		std::cin >> numPoint;
		for (int j = 0; j < numPoint; ++j)
		{
			std::cin >> P[j][0] >> P[j][1];
		}

		// brute force
		minVal = 2e9;
		DFS(0, 0, 0, 0);
		// 오차 고려 출력
		std::cout << minVal << "\n";
	}
}
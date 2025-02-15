
#include <iostream>
#include <cmath>
#include <memory.h>

int numName, width;
int names[1000];
int cache[1001][1001]; // 목표값 = f( 현재 길이, 현재 이름 )

int DP( int curLength, int curPos)
{
	// base case
	if (curPos == numName)
	{
		return 0;
	}

	int& tgt = cache[curLength][curPos];
	// cache hit
	if (tgt != -1)
	{
		return tgt;
	}
	// cache miss
	else
	{
		int nextLength = curLength + 1 + names[curPos];
		int stay = 2e9;
		// 열바꿈, 열을 바꾸면 무조건 처음에 하나를 쓴다.
		int go = std::pow(width - curLength, 2) + DP( names[curPos], curPos + 1);
		
		if (nextLength <= width)
		{	// 열 안바꿈
			stay = DP( nextLength, curPos + 1);
		}

		return tgt = std::min(go, stay);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	for (int i = 0; i < 1001; ++i)
	{
		memset(cache[i], -1, sizeof(cache[i]));
	}

	std::cin >> numName >> width;
	for (int i = 0; i < numName; ++i)
	{
		std::cin >> names[i];
	}

	if (numName == 0)
	{
		std::cout << 0;
	}
	else
	{
		std::cout << DP(names[0], 1); // 첫 move직후 시작함.
	}
}

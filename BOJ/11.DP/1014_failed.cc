
/*
	bitmasking + DP

	status : 현재 row의 상태 및 maximum number of people

	number of current status + prev row max number of people
	f(n) = g(stat) + f(n - 1)

	현재 row의 stat은 prev row의 stat과 관련이 있음. 이 stat은 홀짝으로 row마다 두 가지 가능성 odd와 even이 존재함.

	odd와 even으로 나눈게 패착임. 그렇게 나눠지지 않을 수 있음. fail한 접근.
*/
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using Stat = std::bitset<10>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int numTest, maxRow, maxCol;
	std::string input;
	std::cin >> numTest;
	while (numTest--)
	{
		std::cin >> maxRow >> maxCol;
		std::vector<Stat> map(maxRow);
		std::vector<int> cache1(1 << maxCol, -1);
		std::vector<int> cache2(1 << maxCol, -1);
		std::vector<int> &prevCache = cache1;
		std::vector<int> &curCache = cache2;
		// init
		for (int i = 0; i < maxRow; ++i)
		{
			std::cin >> input;
			int curStat = 0;
			for (int j = 0; j < maxCol; ++j)
			{
				if (input[j] == 'x')
					curStat |= 1 << j;
			}
			map[i] = curStat;
		}

		// init prevCache
		for (int s = 0; s < (1 << maxCol); ++s)
		{
			// (s & (s >> 1)) == 0 : 인접한 자리 점유 x
			// map과 &를 통해서 착석 금지를 준수 했는지 확인하기
			if ((s & (s >> 1)) == 0 && (static_cast<Stat>(s) & map[0]) == 0)
			{
				prevCache[s] = static_cast<Stat>(s).count();
			}
		}
		// dp, -1 means impossible
		for (int r = 1; r < maxRow; ++r)
		{
			fill(curCache.begin(), curCache.end(), -1);
			for (int curS = 0; curS < (1 << maxCol); ++curS)
			{
				if ((curS & (curS >> 1)) == 0 && (static_cast<Stat>(curS) & map[r]) == 0)
				{
					// get maximum previous value + current status count
					for (int prevS = 0; prevS < (1 << maxCol); ++prevS)
					{
						if (prevCache[prevS] != -1 && !(prevS & (curS << 1) || prevS & (curS >> 1)))
							curCache[curS] = std::max(curCache[curS],
													  prevCache[prevS] + static_cast<int>(static_cast<Stat>(curS).count()));
					}
				}
			}
			std::swap(curCache, prevCache);
		}
		// result;
		int result = 0;
		for (int i = 0; i < (1 << maxCol); ++i)
		{
			result = std::max(result, prevCache[i]);
		}
		std::cout << result << '\n';
	}
}

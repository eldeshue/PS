// 컴비네이션, 즉 조합 계산 문제임.
// 다만, 이를 DP 이용하여 보다 수 회의 테스트에 대해서 
// 캐싱의 효과를 보도록 구성함.
#include <iostream>
#include <memory.h>

int cache[31][31];	// cache[east site][west site] = (east)C(west)
int numTest, N, M;	

int combination(int east, int west)	// DP
{
	if (cache[east][west] != -1) // cache hit
	{
		return cache[east][west];
	}
	else // cache miss, memo
	{
		return cache[east][west] = combination(east, west - 1) * (east - west + 1) / west;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int i = 0; i < 31; ++i)
	{
		memset(cache[i] + 2, -1, 29 * sizeof(int));
		cache[i][1] = i;
	}

	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		std::cin >> N >> M;
		std::cout << combination(M, N) << "\n";
	}
}
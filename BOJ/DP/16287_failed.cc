
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	// input
	int W, N;
	std::cin >> W >> N;
	std::vector<int> A(N + 1);
	std::vector<std::vector<bool>> cache(3, std::vector<bool>(W + 1, false));
	for (int i = 0; i < N; ++i)
		std::cin >> A[i];
	// simple dp, tabulation
	// W : 8 * 10^5, N : 5 * 10^3
	// O( W * N ) = 4 * 10^9 -> fail. TLE
	for (const int curVal : A)
	{
		if (curVal < W)
		{
			// find result
			if (cache[2][W - curVal])
			{
				std::cout << "YES";
				return 0;
			}
			// update
			for (int cnt = 2; cnt > 0; --cnt)
			{
				for (int prevVal = 0; prevVal < W; ++prevVal)
				{
					const int nextVal = prevVal + curVal;
					if (nextVal < W && cache[cnt - 1][prevVal])
					{
						cache[cnt][nextVal] = true;
					}
				}
			}
			// add
			cache[0][curVal] = true;
		}
	}
	std::cout << "NO";
}

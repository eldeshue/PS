
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <limits>
#include <functional>
class Solution
{
public:
	// solution method
	int stoneGameII(vector<int>& piles)
	{
		const int N = piles.size();
		vector<vector<int>> cache(N, vector<int>(N, 0));
		vector<int> suffixSum(piles);

		// 완전탐색을 dp로 최적화
		// 내 최선의 선택이 곧 상대에겐 최악의 선택임.
		// 
		// suffix sum
		for (int i = N - 2; i >= 0; --i)
			suffixSum[i] += suffixSum[i + 1];

		// dp, get maximum sum based on current status
		function<int(int, int)> dp = [&](int curPos, int curM)->int
			{
				if (curPos + 2 * curM >= N)	// base case, take all the rest
					return suffixSum[curPos];
				else if (cache[curPos][curM] != 0)	// cache hit
					return cache[curPos][curM];
				else
				{
					// to maximize my choice, minimize opponent's choice
					int opponentSum = numeric_limits<int>().max();

					for (int i = 1; i <= 2 * curM; ++i)
					{
						// minimize opponent sum
						// calling dp means changing turn
						opponentSum = std::min(opponentSum,
							dp(curPos + i, std::max(i, curM)));
					}
					// maximize my sum
					return cache[curPos][curM] = suffixSum[curPos] - opponentSum;
				}
			};
		return dp(0, 1);
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}


#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <tuple>
#include <queue>
#include <vector>
class Solution
{
public:
	// solution method, status space search
	using Stat = tuple<int, int, int>;
	int minSteps(int n)
	{
		/*
		// solution 1 , 상태공간 탐색
		queue<Stat> q;
		int result = 2e9;

		if (n == 1)
			return 0;
		q.push(make_tuple(1, 0, 0));
		while (!q.empty())
		{
			const auto& [sum, copied, moveCnt] = q.front();

			// copy
			if (sum > copied)
				q.push(make_tuple(sum, sum, moveCnt + 1));
			// paste
			if (copied > 0)
			{
				int nextSum = sum + copied;
				if (nextSum == n)
					result = std::min(result, moveCnt + 1);
				else if (nextSum < n)
					q.push(make_tuple(nextSum, copied, moveCnt + 1));
			}
			q.pop();
		}
		return result;
		*/
		// solution 2, 소인수 분해
		int result = 0, div = 2;

		while (n != 1)
		{
			if ((n % div) == 0)
			{
				n /= div;
				result += div;
			}
			else
				div++;
		}
		return result;
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
	std::cout << test.minSteps(7);
}


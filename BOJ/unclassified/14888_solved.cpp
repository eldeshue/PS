
#include <iostream>
#include <vector>
#include <array>
#include <functional>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<ll> nums(N);
	for (int i = 0; i < N; ++i)
		std::cin >> nums[i];
	std::array<int, 4> oprtCnt;
	for (int i = 0; i < 4; ++i)
		std::cin >> oprtCnt[i];
	// functors
	std::array<std::function<ll(const ll&, const ll&)>, 4> oprt;
	oprt[0] = [](const ll& n1, const ll& n2) -> ll {return n1 + n2; };
	oprt[1] = [](const ll& n1, const ll& n2) -> ll {return n1 - n2; };
	oprt[2] = [](const ll& n1, const ll& n2) -> ll {return n1 * n2; };
	oprt[3] = [](const ll& n1, const ll& n2) -> ll {return n1 / n2; };
	// back tracking
	ll minSum = 2e9, maxSum = -2e9;
	std::function<void(int, ll)> solve = [&](int curIdx, ll curSum) -> void
	{
		if (curIdx == N)
		{
			maxSum = std::max(maxSum, curSum);
			minSum = std::min(minSum, curSum);
		}
		else
		{
			for (int i = 0; i < 4; ++i)
			{
				if (oprtCnt[i])
				{
					oprtCnt[i]--;
					solve(curIdx + 1, oprt[i](curSum, nums[curIdx]));
					oprtCnt[i]++;
				}
			}
		}
	};
	solve(1, nums[0]);
		std::cout << maxSum << '\n' << minSum;
}
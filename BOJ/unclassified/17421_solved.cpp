
/*
	monoton stack

	빗물 문제의 강화판, 고이는 빗물의 양에 더해서 고인 웅덩이의 개수까지 추적하는 문제.
	물 웅덩이의 너비를 계산하는 과정에서 웅덩이의 영역을 stack에 저장하고,
	물이 추가적으로 차오르는 과정에서 웅덩이의 영역을 병합해 나가면 됨
*/
#include <iostream>
#include <stack>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using ll = long long;

	// input
	int N, K;
	std::cin >> N >> K;
	std::vector<int> depths(N + 2, 0);
	for (int i = 1; i <= N; ++i)
		std::cin >> depths[i];

	// solve : monoton stack
	// ascending order
	using Pond = std::pair<int, int>;	// start, end, depth
	std::stack<Pond> ponds;
	using Status = std::pair<int, int>;	// end, depth
	std::stack<Status> monoStack;
	ll water = 0;
	for (int curPos = 0; curPos <= N + 1; ++curPos)
	{
		int const curDepth = depths[curPos];
		// check result, new pond found
		if (!monoStack.empty() && monoStack.top().second < curDepth
			&& ponds.size() == (K - 1))
		{
			std::cout << water;
			return 0;
		}
		// keep stack monotonous
		while (monoStack.size() >= 2 && monoStack.top().second > curDepth)
		{
			// calculate water
			// get floor
			ll const floorDepth = monoStack.top().second;
			monoStack.pop();
			// get left wall
			ll const leftWallPos = monoStack.top().first;
			int const leftWallDepth = monoStack.top().second;
			// accumulate water
			water += (curPos - 1 - leftWallPos) * (floorDepth - std::max(leftWallDepth, curDepth));

			// handling ponds
			// calculate new pond
			Pond newPond = { leftWallPos, curPos - 1 };

			// combine previous pond
			// to track number of pond, use stack to save it's range
			while (!ponds.empty()
				&& ponds.top().first < newPond.second	// intersection
				&& ponds.top().second > newPond.first)
			{
				ponds.pop();
			}

			// save new pond
			ponds.push(newPond);
		}
		// save status
		if (!monoStack.empty() && monoStack.top().second == curDepth)
		{
			// same depth, enhance
			monoStack.top().first = curPos;
		}
		else // monoStack.top().second < curDepth
		{
			monoStack.push(std::make_pair(curPos, curDepth));
		}
	}

	// result not found
	std::cout << -1;
}
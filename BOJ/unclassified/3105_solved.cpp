
#include <iostream>
#include <limits>
#include <vector>
#include <stack> // monoton stack
using ll = long long;
using pll = std::pair<ll, ll>;
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	ll pairCnt = 0;
	std::cin >> N;
	std::vector<ll> nums(N);
	std::stack<pll> st;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
	}
	for (auto itr = nums.begin(); itr != nums.end(); ++itr)
	{
		const int& curVal = *itr;
		while (!st.empty() && curVal > st.top().first)
		{
			pairCnt += st.top().second;
			st.pop();
		}
		if (st.empty() || curVal < st.top().first)
		{
			if (!st.empty())	// adjacent
				pairCnt++;
			st.push(std::make_pair(curVal, 1));
		}
		else if (curVal == st.top().first)	// same
		{
			if (st.size() > 1)	// adjacent
				pairCnt++;
			pairCnt += st.top().second;
			st.top().second++;
		}
	}
	std::cout << pairCnt;
}
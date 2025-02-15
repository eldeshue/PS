
#include <iostream>
#include <stack>
#include <vector>

using HG = std::pair<int, int>; // histogram x, y

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while (true)
	{
		// set up
		int N;
		long long result = 0;
		std::cin >> N;
		if (N == 0)
			break;
		std::vector<int> input(N + 1, 0);
		for (int i = 0; i < N; ++i)
			std::cin >> input[i];
		std::stack<HG> st;
		st.push(std::make_pair(-1, 0));
		// solve
		for (int i = 0; i <= N; ++i)
		{
			while (st.size() > 1 && st.top().second >= input[i])
			{
				HG curBlock = st.top();
				st.pop();
				result = std::max(result, static_cast<long long>(curBlock.second) * static_cast<long long>(i - st.top().first - 1));
			}
			st.push(std::make_pair(i, input[i]));
		}
		std::cout << result << '\n';
	}
}

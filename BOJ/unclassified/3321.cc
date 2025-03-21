

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using HG = std::pair<int, int>; // histogram x, y

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char input;
	int N, M;
	long long result = 0;
	std::cin >> N >> M;
	std::vector<int> histogram(M, 0);
	std::vector<std::string> board(N);
	for (int r = 0; r < N; ++r)
	{
		std::cin >> board[r];
	}
	// solve, O(N ^ 2)
	for (int r = 0; r < N; ++r)
	{
		// update histogram
		for (int c = 0; c < M; ++c)
		{
			if (board[r][c] == '1')
				histogram[c]++;
			else
				histogram[c] = 0;
		}
		// histogram 정렬
		std::vector<int> stat = histogram;
		std::sort(stat.begin(), stat.end());
		stat.push_back(0);
		// solve
		std::stack<HG> st;
		st.push(std::make_pair(-1, 0));
		// solve
		for (int i = 0; i <= M; ++i)
		{
			while (st.size() > 1 && st.top().second >= stat[i])
			{
				HG curBlock = st.top();
				st.pop();
				result = std::max(result,
					static_cast<long long>(curBlock.second)
					* static_cast<long long>(i - st.top().first - 1));
			}
			st.push(std::make_pair(i, stat[i]));
		}
	}
	std::cout << result;
}

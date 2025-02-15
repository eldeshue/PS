
#include <iostream>
#include <stack>
#include <vector>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int H, W;
	std::cin >> H >> W;
	std::vector<int> landScape(W);
	for (auto& h : landScape)
		std::cin >> h;

	int result = 0;
	std::stack<pii> st;
	st.push(std::make_pair(0, landScape[0]));
	for (int rPos = 1; rPos < W; ++rPos)
	{
		int const rHeight = landScape[rPos];
		// stack pop
		while (2 <= st.size() && st.top().second < rHeight)
		{
			int const botHeight = st.top().second;
			st.pop();
			int const lPos = st.top().first;
			int const gap = std::min(rHeight, st.top().second) - botHeight;
			// accumulate
			result += gap * (rPos - lPos - 1);
		}
		while (!st.empty() && st.top().second <= rHeight)
			st.pop();
		st.push(std::make_pair(rPos, rHeight));
	}
	std::cout << result;
}

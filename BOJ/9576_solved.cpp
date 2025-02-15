
#include <iostream>
#include <vector>
#include <algorithm>

using Range = std::pair<int, int>;

struct sortRange
{
	bool operator()(const Range& r1, const Range& r2)
	{
		if (r1.second == r2.second)
			return r1.first < r2.first;
		return r1.second < r2.second;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T, N, M;
	std::cin >> T;
	while (T--)
	{
		std::cin >> N >> M;
		std::vector<Range> people(M, { 0, 0 });
		std::vector<bool> used(N + 1, false);
		for (int i = 0; i < M; ++i)
		{
			std::cin >> people[i].first >> people[i].second;
		}
		sort(people.begin(), people.end(), sortRange());
		int resultCnt = 0;
		for (int curP = 0; curP < M; ++curP)
		{
			for (int bookNum = people[curP].first;
					bookNum <= people[curP].second; ++bookNum)
			{
				if (used[bookNum] == false)
				{
					used[bookNum] = true;
					resultCnt++;
					break;
				}
			}
		}
		std::cout << resultCnt << '\n';
	}
}
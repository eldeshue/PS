
#include <iostream>
#include <vector>
#include <algorithm>

using Range = std::pair<int, int>;

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
		std::vector<Range> people(M, {0, 0});
		for (int i = 0; i < M; ++i)
		{
			std::cin >> people[i].first >> people[i].second;
		}
		sort(people.begin(), people.end());
		int resultCnt = 0, curBookNum = 1;
		for (int curP = 0; curP < M; ++curP)
		{
			if (curBookNum < people[curP].first)
			{
				curBookNum = people[curP].first;
			}
			else if (curBookNum > people[curP].second)
			{
				continue;
			}

			resultCnt++;
			curBookNum++;
		}
		std::cout << resultCnt << '\n';
	}
}

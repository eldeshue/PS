/*
	BOJ 19598
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using Conf = std::pair<int, int>;

struct cmp_end_first
{
	bool operator()(Conf const& c1, Conf const& c2)
	{
		if (c1.second == c2.second)
			return c1.first > c2.first;
		return c1.second > c2.second;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<Conf> cnfs(N);
	for (auto& [s, e] : cnfs)
		std::cin >> s >> e;

	std::sort(cnfs.begin(), cnfs.end());

	int result = 0;
	std::priority_queue<Conf, std::vector<Conf>, cmp_end_first> pq;
	for (auto const [cur_s, cur_e] : cnfs)
	{
		// pop pq
		while (!pq.empty() && pq.top().second <= cur_s)
			pq.pop();

		pq.push(Conf(cur_s, cur_e));

		result = std::max(result, static_cast<int>(pq.size()));
	}

	std::cout << result;
}

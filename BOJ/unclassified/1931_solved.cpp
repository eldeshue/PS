
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

int N;
std::vector<std::pair<int, int>> conf;

struct comp
{
	bool operator() (const std::pair<int, int> p1, const std::pair<int, int> p2)
	{
		if (p1.second == p2.second)
		{
			return p1.first < p2.first;
		}
		else
		{
			return p1.second < p2.second;
		}
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int s, e;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> s >> e;
		conf.push_back(std::make_pair(s, e));
	}

	std::sort(conf.begin(), conf.end(), comp());
	int count = 0;
	int lastConfStart = 0, lastConfEnd = 0;

	for (int i = 0; i < N; ++i)
	{
		if (conf[i].first >= lastConfEnd) // new, not overlapped
		{
			count++;
			lastConfStart = conf[i].first;
			lastConfEnd = conf[i].second;
		}
	}

	std::cout << count;
}
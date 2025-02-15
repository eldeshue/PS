
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

typedef struct shortCut
{
	int start;
	int end;
	int distance;
	shortCut(int s, int e, int d) : start(s), end(e), distance(d) {}
} shortCut;

struct cmp
{
	bool operator() (shortCut& s1, shortCut& s2)
	{
		if (s1.end == s2.end)
		{
			return s1.start < s2.start;
		}
		else
		{
			return s1.end > s2.end;
		}
	}
};

int numShortCut, Goal;
std::vector<shortCut> vec;
int cache[10000]; // cache[pos] = distance

int DP(int pos)	// return minimum length, recursively
{
	int& curDistance = cache[pos];
	if (pos == 0)
	{
		return 0;
	}
	else if (curDistance != 0) // cache hit
	{
		return curDistance;
	}
	else // cache miss
	{
		curDistance = pos;
		for (const auto& elem : vec)
		{
			if (elem.end <= pos)
			{
				curDistance = std::min(curDistance, (pos - elem.end) + elem.distance + DP(elem.start));
			}
		}

		return curDistance;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int s, e, d;
	std::cin >> numShortCut >> Goal;
	for (int i = 0; i < numShortCut; ++i)
	{
		std::cin >> s >> e >> d;
		vec.push_back(shortCut(s, e, d));
	}
	std::sort(vec.begin(), vec.end(), cmp());
	memset(cache, 0, sizeof(cache));

	std::cout << DP(Goal);
}

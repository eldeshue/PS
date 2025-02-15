
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N;
	// kind of sweeping
	// search, back tracking
	std::vector<pii> aVec(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> aVec[i].first;
		aVec[i].second = i;
	}
	std::cin >> M;
	std::vector<pii> bVec(M);
	for (int i = 0; i < M; ++i)
	{
		std::cin >> bVec[i].first;
		bVec[i].second = i;
	}
	auto cmp = [](const pii &p1, const pii &p2) -> bool
	{ if (p1.first == p2.first) {return p1.second < p2.second;} return p1.first > p2.first; };
	std::sort(aVec.begin(), aVec.end(), cmp);
	std::sort(bVec.begin(), bVec.end(), cmp);
	// search, two pointer
	std::vector<int> result;
	int aLastPos = -1, bLastPos = -1, aPos = 0, bPos = 0;
	while (aPos < N && bPos < M)
	{
		while (aPos < N && (aVec[aPos].first > bVec[bPos].first || aLastPos > aVec[aPos].second))
		{
			aPos++;
		}
		while (bPos < M && (bVec[bPos].first > aVec[aPos].first || bLastPos > bVec[bPos].second))
		{
			bPos++;
		}
		if (aPos < N && bPos < M && aVec[aPos].first == bVec[bPos].first)
		{
			if (aVec[aPos].second > aLastPos && bVec[bPos].second > bLastPos)
			{
				result.push_back(aVec[aPos].first);
				aLastPos = aVec[aPos].second;
				bLastPos = bVec[bPos].second;
				aPos++;
				bPos++;
			}
		}
	}
	//
	std::cout << result.size() << '\n';
	if (result.size() > 0)
	{
		for (const int &n : result)
		{
			std::cout << n << ' ';
		}
	}
}
